//
// Created by 赵伟 on 2024/12/31.
//
#include "Room.h"
#include <iostream>
#include <string>


bool Room::initEnvironment()
{
    JsonParse json;
    auto info = json.getDatabaseInfo(JsonParse::Redis);
    std::string connStr = "tcp://" + info->ip + ":" + std::to_string(info->port);
    m_redis = new sw::redis::Redis(connStr);
    //测试连接
    if(m_redis->ping() == "PONG")
    {
//        std::cout << "成功连接了redis数据库" << std::endl;
        return true;
    }
    return false;
}

void Room::clear()
{
    //flushdb 参数为true代表异步，false代表同步，默认是false
    m_redis->flushdb();
}

void Room::saveRsaSecKey(std::string field, std::string value)
{
    m_redis->hset("RSA", field, value);
}

std::string Room::rsaSecKey(std::string field)
{
    auto value = m_redis->hget("RSA", field);
    if(value.has_value())
    {
        return value.value();
    }
    return std::string();
}

Room::~Room()
{
    if(m_redis)
    {
        delete m_redis;
    }
}

std::string Room::joinRoom(std::string userName)
{
    std::optional<std::string> room;
    do{
        //scard查询set元素个数
        if(m_redis->scard(TwoPlayer) > 0)
        {
            //srandmember 从set中随机取出一个元素
            room = m_redis->srandmember(TwoPlayer);
            break;
        }
        if(m_redis->scard(OnePlayer) > 0)
        {
            room = m_redis->srandmember(OnePlayer);
            break;
        }
        //添加新的房间
        room = getNewRoomName();
    }while(0);
    //加入某个房间
    bool flag = joinRoom(userName, room.value());

    return room.value();
}

std::string Room::getNewRoomName()
{
    //创建随机设备对象
    std::random_device rd;
    //创建随机数生成对象
    std::mt19937 gen(rd());
    //创建随机数分布对象->均匀分布
    std::uniform_int_distribution<int> dis(100000, 999999);
    int randNUm = dis(gen);
    return std::to_string(randNUm);
}

bool Room::joinRoom(std::string userName, std::string roomName)
{
    //zcard查看排序集合中元素个数, scard 查看普通集合中元素个数
    if(m_redis->zcard(roomName) >= 3)
    {
        return false;
    }
    //检查房间是否存在
    if(!m_redis->exists(roomName))
    {
        m_redis->sadd(OnePlayer, roomName);
    }
    //移动房间 1人间->2人间， 2人间->3人间
    else if(m_redis->sismember(OnePlayer, roomName))
    {
        m_redis->smove(OnePlayer, TwoPlayer, roomName);
    }
    else if(m_redis->sismember(TwoPlayer, roomName))
    {
        m_redis->smove(TwoPlayer, ThreePlayer, roomName);
    }
    else
    {
        assert(false);//异常情况直接退出
    }
    //将玩家添加到房间，使用的是sortedset
    m_redis->zadd(roomName, userName, 0);
    //将玩家存储起来 hashs ->通过玩家找到房间
    m_redis->hset("Players", userName, roomName);
    return true;

}

int Room::getPlayerCount(std::string roomName)
{
    int count = m_redis->zcard(roomName);
    return count;
}

void Room::updatePlayerScore(std::string roomName, std::string userName, int score)
{
    //更新->scoredset
    m_redis->zadd(roomName, userName, score);
}

std::string Room::whereAmI(std::string userName)
{
    auto value = m_redis->hget("Players", userName);
    if(value.has_value())
    {
        return value.value();
    }
    return std::string();

}

int Room::playerScore(std::string roomName, std::string userName)
{
    auto score = m_redis->zscore(roomName, userName);
    if(score.has_value())
    {
        return score.value();
    }
    return 0;
}

std::string Room::playersOrder(std::string roomName)
{
    std::string data;
    int index = 0;
    std::vector<std::pair<std::string, double>> output;
    //对房间中的玩家进行排序，降序排序 zrevrange
    m_redis->zrevrange(roomName, 0, -1, std::back_inserter(output));
    for(auto& it:output)
    {
        std::cout << "用户的分数:" << it.second << std::endl;
        data += it.first + "+" + std::to_string(++index) + "+" + std::to_string((int)it.second) + "#";
    }
    return data;
}

void Room::leaveRoom(std::string roomName, std::string userName)
{
    if(m_redis->sismember(ThreePlayer, roomName))
    {
        m_redis->smove(ThreePlayer, Invalid, roomName);
    }
    //从房间中删除玩家
    m_redis->zrem(roomName, userName);
    auto count = m_redis->zcard(roomName);
    if(count == 0)
    {
        //删除redis数据库中的房间
        m_redis->del(roomName);
        //删除invalid集合中的roomName
        m_redis->srem(Invalid, roomName);
        std::cout <<"最后一个玩家离开房间" << std::endl;
    }
    std::cout << "玩家离开房间" << std:: endl;
}

bool Room::searchRoom(std::string roomName)
{
    //搜索二人间
    bool flag = m_redis->sismember(TwoPlayer, roomName);
    //搜索一人间
    if(!flag)
    {
        flag = m_redis->sismember(OnePlayer, roomName);
    }
    return flag;
}
