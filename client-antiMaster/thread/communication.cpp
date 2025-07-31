#include "communication.h"
#include "datamanager.h"
#include <QThread>
#include <QDebug>
#include <QSharedPointer>
#include <QDateTime>
#include <qdatastream.h>
#include "rsacrypto.h"
#include "card.h"
#include "cards.h"
#include "taskqueue.h"
Communication::Communication(Message& msg, QObject *parent)
    : QObject{parent}, m_msgInfo(msg)
{
    setAutoDelete(true);
}

Communication::~Communication()
{
    if(m_aes != nullptr)
    {
        delete m_aes;
    }
}

void Communication::sendMessage(Message *msg, bool encrypt)
{
    qDebug() << msg->data1 << " " << msg->data2;
    Codec codec(msg);
    QByteArray data = codec.encodeMsg();
    qDebug() << data ;
    //加密数据
    if(encrypt)
    {
        data = m_aes->encrypt(data);
    }

    bool flag = m_socket->sendMsg(data);
}

void Communication::parseRecvMessage()
{
    //接受数据
    QByteArray data = m_socket->recvMsg(2);
    if(data.size() != 0)qDebug() << "接收到的数据" << data;
    if(data.isEmpty())return;

    //aes解密数据
    // if(m_aes != nullptr)
    // {
    //     data = m_aes->encrypt(data);
    // }
    //反序列化数据
    Codec codec(data);
    QSharedPointer<Message> ptr = codec.decodeMsg();
    qDebug() << (int)ptr->rescode << ", " << ptr->data2;
    switch(ptr->rescode)
    {
    case RespondCode::LoginOK:
        emit loginOK();
        qDebug() << "登录成功";
        break;
    case RespondCode::RegisterOK:
        emit registerOK();
        qDebug() << "注册成功";
        break;
    case RespondCode::RsaFenFa:
        handleRsaFenFa(ptr.get());
        break;
    case RespondCode::AesVerifyOk:
        //communitation是线程池中的一个任务类，在任务类中创建子对象时，不允许给子对象指定父对象
        m_aes = new AesCrypto(AesCrypto::AES_CBC_256, m_aesKey);
        sendMessage(&m_msgInfo);
        qDebug() << m_msgInfo.userName << m_msgInfo.reqcode;
        qDebug() << "Aes的密钥分发成功了...";
        break;
    case RespondCode::JoinRoomOK:
        qDebug() << "加入房间成功:" << ptr->roomName.data();
        DataManager::getInstance()->setRoomName(ptr->roomName);
        emit playerCount(ptr->data1.toInt());
        qDebug() << ptr->data1.data();
        break;
    case RespondCode::DealCards:
        parseCards(ptr->data1, ptr->data2);
        break;
    case RespondCode::StartGame:
        qDebug() << ptr->data1.data();
        emit startGame(ptr->data1);
        break;
    case RespondCode::OtherGrabLord:
    {
        Task t;
        t.bet = ptr->data1.toInt();
        TaskQueue::getInstance()->add(t);
        break;
    }
    case RespondCode::OtherPlayHand:
    {
        //data1:数量 data2:数据
        QDataStream stream(ptr->data2);
        Task t;
        for(int i = 0; i < ptr->data1.toInt(); ++i)
        {
            Card c;
            stream >> c;
            t.cs.add(c);
        }
        TaskQueue::getInstance()->add(t);
        break;
    }
    case RespondCode::SearchRoomOk:
    {
        bool flag = ptr->data1 == "true" ? true:false;
        emit roomExist(flag);
        break;
    }
    case RespondCode::OtherLeaveRoom:
    {
        int count = ptr->data1.toInt();
        emit somebodyLeave(count);
        break;
    }
    case RespondCode::Failed:
        qDebug() <<"error:" << ptr->data1;
        emit failedMsg(ptr->data1);
        break;
    default:break;
    }
}

void Communication::handleRsaFenFa(Message *msg)
{
    RsaCrypto rsa;
    rsa.parseStringToKey(msg->data1, RsaCrypto::PublicKey);
    //校验
    bool flag = rsa.verify(msg->data2, msg->data1);
    qDebug() << "正在校验";
    if(flag)
    {
        qDebug() << "校验成功";
    }
    //生成对称加密的密钥
    m_aesKey = generateAesKey(KeyLen::L32);
    Message resMsg;
    resMsg.reqcode = RequestCode::AesFenFa;
    resMsg.data1 = rsa.pubKeyEncrypt(m_aesKey);
    resMsg.data2 = QCryptographicHash::hash(m_aesKey, QCryptographicHash::Sha224).toHex();
    sendMessage(&resMsg, false);
}

QByteArray Communication::generateAesKey(KeyLen len)
{
    QByteArray time = QDateTime::currentDateTime().toString("yyyy.MM.dd-hh:mm:ss.zzz").toUtf8();
    //进行哈希计算
    QCryptographicHash hash(QCryptographicHash::Sha3_384);
    hash.addData(time);
    time = hash.result();
    time = time.left(len);
    return time;
}

void Communication::parseCards(QByteArray data1, QByteArray data2)
{
    //花色-点数#花色-点数
    //可以用bind绑定匿名函数
    auto func = std::bind([=](QByteArray msg){
        auto lst = msg.left(msg.length() - 1).split('#');
        Cards cs;
        for(const auto&item:lst)
        {
            auto sub = item.split('-');
            Card card(static_cast<Card::CardPoint>(sub.last().toInt()), static_cast<Card::CardSuit>(sub.first().toInt()));
            cs.add(card);
        }
        return cs;
    }, std::placeholders::_1);
    Cards cards = func(data1);
    Cards last = func(data2);
    //存储数据
    DataManager::getInstance()->setCards(cards, last);
}

void Communication::run()
{

    m_socket = new TcpSocket;
    //连接服务器
    DataManager *obj = DataManager::getInstance();
    bool flag = m_socket->connectToHost(obj->getIp(), obj->getPort().toInt());
    qDebug() << "=============通信的子线程id:" <<QThread::currentThread() << "connected ? " << flag;
    if(!flag)
    {
        //通知主线程连接失败了
        emit connectFailed();
        delete m_socket;
    }
    //连接成功了
    while(!m_stop)
    {
        //处理服务器回复的数据
        //首先得到非对称加密的公钥，发送加密之后的对称加密密钥给服务器,服务器回复接受密钥成功的消息，然后发送登录或者注册的请求
        parseRecvMessage();
    }
    m_socket->disconnect();
    delete m_socket;
}
