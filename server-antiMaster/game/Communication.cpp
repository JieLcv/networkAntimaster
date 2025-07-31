//
// Created by 赵伟 on 2024/12/27.
//

#include "Communication.h"
#include <netinet/in.h>
#include "Hash.h"
#include "Log.h"
void Communication::parseRequest(Buffer* buf)
{
    //读数据头
    std::string data = buf->data(sizeof(int));
    int length = *(int*)data.data();  //大端长度
    length = ntohl(length);
    //读数据块
    data = buf->data(length);
    if(m_aes)
    {
        data = m_aes->decrypt(data);
    }
    //数据的反序列化
    Codec codec(data);
    Message resMsg;
    sendCallback myfunc = sendMessage;
    shared_ptr<Message> ptr = codec.decodeMsg();
    Debug("接收到的数据：请求码：%d, data1:%s, data2:%s", ptr->reqcode, ptr->data1.data(), ptr->data2.data());
    switch(ptr->reqcode)
    {
        case RequestCode::AesFenFa:
            handleAesFenfa(ptr.get(), resMsg);
            break;
        case RequestCode::UserLogin:
            handleLogin(ptr.get(), resMsg);
            break;
        case RequestCode::Register:
            handleRegister(ptr.get(), resMsg);
            break;
        case RequestCode::AutoRoom:
        case RequestCode::ManualRoom:
            handleAddRoom(ptr.get(), resMsg);
            myfunc = std::bind(&Communication::readyForPlay, this, resMsg.roomName, std::placeholders::_1);
            break;
        case RequestCode::GrabLord:
            //通知其他玩家
            resMsg.data1 = ptr->data1;
            resMsg.rescode = RespondCode::OtherGrabLord;
            myfunc = std::bind(&Communication::notifyOtherPlayers, this, std::placeholders::_1, ptr->roomName, ptr->userName);
            break;
        case RequestCode::PlayAHand:
            resMsg.data1 = ptr->data1;
            resMsg.data2 = ptr->data2;
            resMsg.rescode = RespondCode::OtherPlayHand;
            myfunc = std::bind(&Communication::notifyOtherPlayers, this, std::placeholders::_1, ptr->roomName, ptr->userName);
            break;
        case RequestCode::GameOver:
            handleGameOver(ptr.get());
            myfunc = nullptr;
            break;
        case RequestCode::Continue:
            restartGame(ptr.get());
            myfunc = nullptr;
            break;
        case RequestCode::SearchRoom:
            handleSearchRoom(ptr.get(), resMsg);
            break;
        case RequestCode::LeaveRoom:
            handleLeaveRoom(ptr.get(), resMsg);
            myfunc = nullptr;
            break;
        case RequestCode::Goodbye:
            handleGoodBye(ptr.get());
            myfunc = nullptr;
            break;
        default:
            break;
    }
    if(myfunc != nullptr)
    {
        codec.reload(&resMsg);
        std::string msg = codec.encodeMsg();
        Debug("回复给客户端的数据: data1 = %s, data2 = %s, size = %lu, status: %d", resMsg.data1.data(), resMsg.data2.data(), msg.size(), resMsg.rescode);
//        if(m_aes && ptr->reqcode != RequestCode::AesFenFa)
//        {
//            msg = m_aes->encrypt(msg);
//            Debug("数据已对称加密");
//        }
        myfunc(msg);
    }
}


void Communication::handleAesFenfa(Message *reqMsg, Message& resMsg)
{
    RsaCrypto rsa;
    rsa.parseStringToKey(m_redis->rsaSecKey("PrivateKey"), RsaCrypto::PrivateKey);
    std::string aesKey = rsa.priKeyDecrypt(reqMsg->data1);
    Hash h(HashType::Sha224);
    h.addData(aesKey);
    std::string res = h.result();
    resMsg.rescode = RespondCode::AesVerifyOk;
    if(reqMsg->data2 != res)
    {
        Debug("密钥校验失败--aes");
        resMsg.rescode = RespondCode::Failed;
        resMsg.data1 = "Aes密钥的哈希校验失败了...";
    }
    else
    {
        Debug("密钥校验成功--aes");
        m_aes = new AesCrypto(AesCrypto::AES_CBC_256, aesKey);
    }
}

void Communication::setCallback(Communication::sendCallback func1, Communication::deleteCallback func2)
{
    sendMessage = func1;
    disconnect = func2;
}

void Communication::handleRegister(Message *reqMsg, Message &resMsg)
{
    //查询数据库
    //select 字段 from 数据库表 where 条件;
    Debug("正在注册");
    char sql[1024];
    sprintf(sql, "SELECT * FROM user WHERE name = '%s';", reqMsg->userName.data());
    bool flag = m_mysql->query(sql);
    Debug("flag = %d, sql = %s", flag, sql);
    if(flag && !m_mysql->next())
    {
        Debug("name=%s, passwd = %s, phone = %s", reqMsg->userName.data(), reqMsg->data1.data(), reqMsg->data2.data());
        m_mysql->transaction();
        sprintf(sql, "INSERT INTO user (name, passwd, phone, date) VALUES('%s', '%s', '%s', NOW())",
                reqMsg->userName.data(), reqMsg->data1.data(), reqMsg->data2.data());
        bool fl1 = m_mysql->update(sql);
        Debug("fl1 = %d, sql = %s", fl1, sql);
        sprintf(sql, "INSERT INTO information (name, score, status) VALUES('%s', 0, 0)",
                reqMsg->userName.data());
        bool fl2 = m_mysql->update(sql);
        Debug("fl2 = %d, sql = %s", fl2, sql);
        if(fl1 && fl2)
        {
            m_mysql->commit();
            resMsg.rescode = RespondCode::RegisterOK;
        }
        else
        {
            m_mysql->rollback();
            Debug("数据库插入失败");
            resMsg.rescode = RespondCode::Failed;
            resMsg.data1 = "数据库插入失败";
        }
    }
    else
    {
        Debug("用户名字已经存在，无法完成注册！");
        resMsg.rescode = RespondCode::Failed;
        resMsg.data1 = "用户名字已经存在，无法完成注册！";
    }

}

Communication::Communication()
{
    JsonParse json;
    std::shared_ptr<DBInfo> info = json.getDatabaseInfo(JsonParse::Mysql);
    m_mysql = new MySqlConn;
    bool flag = m_mysql->connect(info->user, info->dbname, info->passwd, info->ip, info->port);
    assert(flag);
    m_redis = new Room;
    flag = m_redis->initEnvironment();
    assert(flag);
    Debug("数据库连接成功");
}

void Communication::handleLogin(Message *reqMsg, Message &resMsg)
{
    Debug("正在登录");
    char sql[1024];
    sprintf(sql, "SELECT * FROM user WHERE name = '%s' AND passwd = '%s' AND (SELECT count(*) FROM information where name = '%s' AND status = 0);",
            reqMsg->userName.data(), reqMsg->data1.data(), reqMsg->userName.data());
    bool flag = m_mysql->query(sql);
    Debug("flag = %d, sql = %s", flag, sql);
    if(flag && m_mysql->next())
    {
        m_mysql->transaction();
        sprintf(sql, "UPDATE information SET status = 1 WHERE name = '%s'", reqMsg->userName.data());
        bool flag1 =  m_mysql->update(sql);
        Debug("flag1 = %d, sql = %s", flag1, sql);
        if(flag1)
        {
            m_mysql->commit();
            resMsg.rescode = RespondCode::LoginOK;
            return;
        }
        m_mysql->rollback();
        Debug("用户名或密码错误，或者当前用户已经登录了...");
        resMsg.rescode = RespondCode::Failed;
        resMsg.data1 = "用户名或密码错误，或者当前用户已经登录了...";
    }
    else
    {
        Debug("用户名或密码错误，或者当前用户已经登录了...");
        resMsg.rescode = RespondCode::Failed;
        resMsg.data1 = "用户名或密码错误，或者当前用户已经登录了...";
    }
}

Communication::~Communication()
{
    if(m_redis)
    {
        delete m_redis;
    }
    if(m_aes)
    {
        delete m_aes;
    }
    if(m_mysql)
    {
        delete m_mysql;
    }
}
//可能有bug
void Communication::handleAddRoom(Message *reqMsg, Message &resMsg)
{
    //如果当前玩家已经不是第一次(登录之后)加入房间
    //查询这个玩家上次加入的房间，然后把分数读出来
    std::string oldRoom = m_redis->whereAmI(reqMsg->userName);
    int score = m_redis->playerScore(oldRoom, reqMsg->userName);
    if(oldRoom != std::string())
    {
        std::cout << "删除旧房间" << std::endl;
        m_redis->leaveRoom(oldRoom, reqMsg->userName);
        RoomList::getInstance()->removePlayer(oldRoom, reqMsg->userName);
    }
    bool flag = true;
    std::string roomName;

    if(reqMsg->reqcode == RequestCode::AutoRoom)
    {
        roomName = m_redis->joinRoom(reqMsg->userName);
    }
    else
    {
        roomName = reqMsg->roomName;
        flag = m_redis->joinRoom(reqMsg->userName, roomName);
    }
    //判断是否已经加入到了某个房间中
    if(flag)
    {
        Debug("加入房间成功");
        //难点
        //用户每加入一次房间，就需要告诉房间中其他用户即客户端当前房间的人数，不然若房间中不同用户记录的房间人数不同，就无法开始游戏
        //每个玩家都对应一个Tcpconnection类对象中的channel中的文件描述符
        //但是不同子线程是独立的，问题的本质是访问共享资源，解决方案，使用单例模式，将玩家与tcpconnection关联
        //所以解决办法是利用Communication中的sendMessage,这个函数由可调用函数对象包装器对tcpConnection中的成员函数进行包装，内含文件描述符，可以与这个函数关联
        //第一次加载分数，在redis中更新分数，最后将分数同步到Mysql
        if(score == 0)
        {
            //查询mysql，并将其存储到redis中
            std::string sql = "select score from information where name = '" + reqMsg->userName + "'";
            bool fl = m_mysql->query(sql);
            assert(fl);

            m_mysql->next();
            score = std::stoi(m_mysql->value(0));
        }

        m_redis->updatePlayerScore(roomName, reqMsg->userName, score);
        //将房间和玩家的关系保存到单例对象中
        RoomList *roomList = RoomList::getInstance();
        roomList->addUser(roomName, reqMsg->userName, sendMessage);

        //给客户端回复数据
        std::cout << roomName << std::endl;
        resMsg.rescode = RespondCode::JoinRoomOK;
        resMsg.data1 = std::to_string(m_redis->getPlayerCount(roomName));
        resMsg.roomName = roomName;
    }
    else
    {
        resMsg.rescode = RespondCode::Failed;
        resMsg.data1 = "抱歉， 加入房间失败了， 人数已满!";
    }

}

void Communication::readyForPlay(std::string roomName, std::string data)
{
    //取出单例对象
    RoomList *instance = RoomList::getInstance();
    UserMap players = instance->getPlayers(roomName);
    Debug("发送玩家加入房间成功消息");
    for(auto item:players)
    {
        assert(item.second != nullptr);
        item.second(data);
        Debug("通知玩家加入房间成功");
    }
//    if(players.size() < 3)
//    {
//        //此处有bug, 当第三个人加入房间的时候，服务器直接给客户端发送开始游戏信号，第三个玩家并不知道房间的名字，而在客户端中向服务器发送消息，需要提供房间名字
//        for(auto item:players)
//        {
//            item.second(data);
//        }
//    }
    if(players.size() == 3)
    {
        startGame(roomName, players);
    }
}

void Communication::dealCards(UserMap players)
{
    Message msg;
    //洗牌
    initCards();
    std::string &all = msg.data1;
    for(int i = 0; i < 51 ;++i)
    {
        //取出一张牌
        auto card = takeOneCard();
        std::string sub = std::to_string(card.first) + "-" + std::to_string(card.second) + "#";
        all += sub;
    }
    //剩余的3张牌
    std::string &lastCard = msg.data2;
    for(const auto &item:m_cards)
    {
        std::string sub = std::to_string(item.first) + "-" + std::to_string(item.second) + "#";
        lastCard += sub;
    }
    msg.rescode = RespondCode::DealCards;
    Codec codec(&msg);
    //遍历当前房间中的所有玩家
    for(const auto& player:players)
    {
        player.second(codec.encodeMsg());
    }

}

void Communication::initCards()
{
    m_cards.clear();
    //花色
    for(int i = 1; i <= 4; ++i)
    {
        //点数
        for(int j = 1; j <= 13; ++j)
        {
            m_cards.insert(make_pair(i, j));
        }
    }
    m_cards.insert(make_pair(0, 14));
    m_cards.insert(make_pair(0, 15));

}

std::pair<int, int> Communication::takeOneCard()
{
    //生成随机数
    //创建随机设备对象
    std::random_device rd;
    //创建随机数生成对象
    std::mt19937 gen(rd());
    //创建随机数分布对象->均匀分布
    std::uniform_int_distribution<int> dis(0, m_cards.size() - 1);
    int randNum = dis(gen);
    auto it = m_cards.begin();
    //遍历map容器
    for(int i = 0; i < randNum; ++i, ++it);
    m_cards.erase(it);
    return *it;
}

void Communication::notifyOtherPlayers(std::string data, std::string roomName, std::string userName)
{
    //得到另外的两个玩家
    auto players = RoomList::getInstance()->getPartners(roomName, userName);
    for(const auto &item:players)
    {
        item.second(data);
    }

}

void Communication::restartGame(Message *reqMsg)
{
    //得到房间内的玩家
    auto players = RoomList::getInstance()->getPlayers(reqMsg->roomName);
    //判断房间人数
    if(players.size() == 3)
    {
        //清空当前房间内所有玩家的信息
        RoomList::getInstance()->removeRoom(reqMsg->roomName);
    }
    //将玩家添加到单例对象中
    RoomList::getInstance()->addUser(reqMsg->roomName, reqMsg->userName, sendMessage);
    players = RoomList::getInstance()->getPlayers(reqMsg->roomName);
    //发牌并开始游戏
    if(players.size() == 3)
    {
        startGame(reqMsg->roomName, players);
    }
}

void Communication::startGame(std::string roomName, UserMap players)
{
    //房间满了
    //发牌数据
    dealCards(players);
    //通知客户端可以开始游戏了
    Message msg;
    msg.rescode = RespondCode::StartGame;
    //data1:userName-次序-分数：次序的规则，谁分数高，谁先抢地主
    msg.data1 = m_redis->playersOrder(roomName);
    Debug("排序好的用户:%s", msg.data1.data());
    Codec codec(&msg);
    for(const auto& item:players)
    {
        item.second(codec.encodeMsg());
        Debug("通知玩家开始游戏");
    }
}

//导致客户端出现error消息框
void Communication::handleLeaveRoom(Message *reqMsg, Message &resMsg)
{
    m_redis->leaveRoom(reqMsg->roomName, reqMsg->userName);
    auto roomlist = RoomList::getInstance();
    roomlist->removePlayer(reqMsg->roomName, reqMsg->userName);
    std::cout  << "离开房间" << std::endl;
    resMsg.rescode = RespondCode::OtherLeaveRoom;
    auto players = RoomList::getInstance()->getPlayers(reqMsg->roomName);
    resMsg.data1 = std::to_string(players.size());
    int i = 0;
    for(auto item:players)
    {
        std::cout << item.first << "playersSize:" << players.size() << ": " << ++i << std::endl;
        Debug("回复给客户端的数据: data1 = %s, data2 = %s,  status: %d", resMsg.data1.data(), resMsg.data2.data(), resMsg.rescode);
        Codec codec(&resMsg);
        item.second(codec.encodeMsg());
    }
}

void Communication::handleGoodBye(Message *reqMsg)
{
    //修改玩家的登录状态
    Debug("用户退出");
    char sql[10240] = {0};
    sprintf(sql, "update information set status = 0 where name = '%s'", reqMsg->userName.data());
    m_mysql->update(sql);
    Debug("================================sql=%s, userName:%s", sql, reqMsg->userName.data());
    //和客户端断开连接
    disconnect();
}

void Communication::handleGameOver(Message *reqMsg)
{
    //更新分数也可以只更新redis，用户退出时再更新Mysql，这样可以减少对Mysql的操作，但是如果用户异常退出，那么mysql中的分数可能不会更新
    //redis
    int score = std::stoi(reqMsg->data1);
    m_redis->updatePlayerScore(reqMsg->roomName, reqMsg->userName, score);
    //mysql
    char sql[1024];
    sprintf(sql, "update information set score = %d where name = '%s'", score, reqMsg->userName.data());
    m_mysql->update(sql);
}

void Communication::handleSearchRoom(Message *reqMsg, Message& resMsg)
{
    bool flag = m_redis->searchRoom(reqMsg->roomName);
    resMsg.rescode = RespondCode::SearchRoomOk;
    resMsg.data1 = flag ? "true":"false";
}