//
// Created by 赵伟 on 2025/1/1.
//
#include<map>
#include<string>
#include<functional>
#include<mutex>
#ifndef SERVER_ANTIMASTER_ROOMLIST_H
#define SERVER_ANTIMASTER_ROOMLIST_H
//单例类 懒汉模式
//懒汉模式会出现线程安全问题 解决方法 1：双重检查锁  2：静态局部对象
using callback = std::function<void(std::string)>;
using UserMap = std::map<std::string, callback>;
class RoomList
{
public:
    RoomList(const RoomList&) = delete;
    RoomList& operator()(const RoomList&) = delete;
    static RoomList* getInstance();
    //添加用户
    void addUser(std::string roomName, std::string userName, callback sendMessage);
    //通过房间名字取出房间内的成员信息
    UserMap getPlayers(std::string roomName);
    //得到当前房间中除指定玩家外的其他玩家
    UserMap getPartners(std::string roomName, std::string userName);
    //删除指定房间中的玩家
    void removePlayer(std::string roomName, std::string userName);
    //删除房间内所有玩家
    void removeRoom(std::string roomName);

private:
//    static RoomList* roomList;
    RoomList() = default;
    std::map<std::string, UserMap> m_roomMap;  //共享资源，需要多线程访问
//    std::shared_ptr<std::map<std::string, UserMap>> m_roomMap = std::make_shared<std::map<std::string, UserMap>>();
    std::mutex m_mutex;
};


#endif //SERVER_ANTIMASTER_ROOMLIST_H
