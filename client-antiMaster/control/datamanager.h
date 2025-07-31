#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QByteArray>
#include "communication.h"
#include "cards.h"

/*
 * 单例模式
 * 1. 懒汉模式：在需要用到单例对象时才创建，适用于可能不会用到单例对象的场景，可以节省资源，多线程情况下，可能会有多个线程同时创建单例，会出现线程安全问题
 * 解决方法 在getInatance中将单例定义为静态局部变量
 *
 * 2. 饿汉模式：提前创建，不会出现线程安全问题，适用与经常需要使用单例的场景
 */
//饿汉模式


class DataManager
{
public:
    enum RoomMode{Auto, Manual};
    enum GameMode{Single, Network};
    //屏蔽拷贝构造函数和拷贝赋值运算符可以设置为delete，也可以在private里面声名
    DataManager& operator=(const DataManager&) = delete;
    DataManager(const DataManager&) = delete;
    static DataManager *getInstance();
    //设置数据
    void setUserName(QByteArray name);
    void setIp(QByteArray ip);
    void setPort(QByteArray port);
    void setCommunication(Communication *comm);
    void setRoomName(QByteArray roomName);
    void setCards(Cards cs, Cards last);
    void setGameMode(GameMode mode);
    void setRoomMode(RoomMode mode);
    //获取数据
    QByteArray getUserName();
    QByteArray getIp();
    QByteArray getPort();
    QByteArray getRoomName();
    Communication* getCommunication();
    Cards getCards();
    Cards getLast3Cards();
    bool isNetworkMode();
    bool isManualRoom();

private:
    //如果不想写定义，直接=default，意味着这个构造函数和默认构造函数相同
    //默认构造函数是public的，如果不对其进行覆盖，则无法屏蔽默认构造函数，用户可以通过默认构造函数创建实例
    DataManager() = default;
    static DataManager *m_data;
    //QByteArray是对char* 的封装，一个字符占一个字节
    //QString是采用utf8(utf8属于Unicode字符集)的形式存储数据的，一个字符不止占一个字节（windows 2字节 linux 3字节)
    //QByteArray ->char*,用.data方法，char* ->QByteArray调用构造函数
    QByteArray m_userName;
    QByteArray m_ip = "123.207.59.41";
    QByteArray m_port = "7002";
    // QByteArray m_ip = "192.168.60.128";
    // QByteArray m_port = "6789";
    Communication *m_commun;
    QByteArray m_roomName;
    Cards m_cs;
    Cards m_last;
    GameMode m_mode;
    RoomMode m_roomMode;
};

#endif // DATAMANAGER_H
