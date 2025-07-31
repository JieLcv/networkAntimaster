//
// Created by 赵伟 on 2024/12/31.
//

#ifndef SERVER_ANTIMASTER_ROOM_H
#define SERVER_ANTIMASTER_ROOM_H
#include <string>
#include "JsonParse.h"
#include <sw/redis++/redis++.h>

class Room
{
public:
    Room() = default;
    ~Room();


    //初始化-连接redis++
    bool initEnvironment();
    //清空数据
    void clear();
    //存储RSA密钥
    void saveRsaSecKey(std::string field, std::string value);
    //读密钥
    std::string rsaSecKey(std::string field);
    //加入房间
    std::string joinRoom(std::string userName);
    bool joinRoom(std::string userName, std::string roomName);
    //随机生成房间的名字
    std::string getNewRoomName();
    //得到房间内玩家的数量
    int getPlayerCount(std::string roomName);
    //存储玩家的分数
    void updatePlayerScore(std::string roomName, std::string userName, int score);
    //通过玩家名找房间
    std::string whereAmI(std::string userName);
    //查询玩家的分数
    int playerScore(std::string roomName, std::string userName);
    //得到抢地主的次序
    std::string playersOrder(std::string roomName);
    //离开房间
    void leaveRoom(std::string roomName, std::string userName);
    //搜索房间
    bool searchRoom(std::string roomName);
private:
    sw::redis::Redis* m_redis;
    const std::string OnePlayer = "OnePlayers";
    const std::string TwoPlayer = "TwoPlayers";
    const std::string ThreePlayer = "ThreePlayers";
    const std::string Invalid = "Invalid";

};


#endif //SERVER_ANTIMASTER_ROOM_H
