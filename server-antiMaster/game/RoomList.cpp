//
// Created by 赵伟 on 2025/1/1.
//

#include "RoomList.h"
#include <iostream>

//RoomList* RoomList::roomList = new RoomList;
RoomList* RoomList::getInstance()
{
    static RoomList obj;
    return &obj;
//    return roomList;
}

void RoomList::addUser(std::string roomName, std::string userName, callback sendMessage)
{
    //lock对象析构时，会自动先解锁，在析构自己
    std::lock_guard<std::mutex> locker(m_mutex);
    //在当前map中搜索roomName
    if(m_roomMap.find(roomName) != m_roomMap.end())
    {
        //找到了
        auto &value = m_roomMap[roomName];
        value.insert(make_pair(userName, sendMessage));
    }
    {
        //没找到
        UserMap value = {{userName, sendMessage}};
        m_roomMap.insert(make_pair(roomName, value));
    }

}

UserMap RoomList::getPlayers(std::string roomName)
{
    std::lock_guard<std::mutex> locker(m_mutex);
    auto item = m_roomMap.find(roomName);
    if(m_roomMap.end() == item)
    {
        return UserMap();
    }
    UserMap user = item->second;
    return user;
}

UserMap RoomList::getPartners(std::string roomName, std::string userName)
{
    std::lock_guard<std::mutex> locker(m_mutex);
    auto players = getPlayers(roomName);
    if(players.size() > 1)
    {
        auto self = players.find(userName);
        if(self != players.end())
        {
            players.erase(self);
            return players;
        }
    }
    return UserMap();
}

void RoomList::removePlayer(std::string roomName, std::string userName)
{
    std::lock_guard<std::mutex> locker(m_mutex);
    //找房间
    auto item = m_roomMap.find(roomName);
    if(item != m_roomMap.end())
    {
        //找人
        auto players = item->second;
        auto it = players.find(userName);
        if(it != players.end() && players.size() > 1)
        {
            //此处有超级大bug，花了一天才找出来，直接erase(it)的话，删除的对象，不是it对应的对象，应该使用erase(it->first)
            m_roomMap[roomName].erase(it->first);
            std::cout << "roomList中删除玩家" << "roomName: " << roomName  << ", userName: " << userName << std::endl;
        }

        else if(it != players.end() && players.size() == 1)
        {
            std::cout << "roomList中删除房间" << "roomName: " << roomName  << std::endl;
            m_roomMap.erase(item);
        }
    }

}

void RoomList::removeRoom(std::string roomName)
{
    std::lock_guard<std::mutex> locker(m_mutex);
    //找房间
    auto item = m_roomMap.find(roomName);
    if(item != m_roomMap.end())
    {
        m_roomMap.erase(item);
    }

}
