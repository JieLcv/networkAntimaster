#ifndef TCPSOCKET_H
#define TCPSOCKET_H


#include <QObject>
#include <QByteArray>
#ifdef Q_OS_WIN
#include <winsock2.h>
#endif


class TcpSocket:public QObject
{
    Q_OBJECT
public:
    TcpSocket(QObject *parent = nullptr);
    TcpSocket(QByteArray ip, unsigned short port, QObject *parent = nullptr);
    ~TcpSocket();


    //连接服务器
    bool connectToHost(QByteArray ip, unsigned short port);
    //接受数据
    QByteArray recvMsg(int timeout = -1);  //阻塞时长单位:秒
    //io多路监听 select 跨平台,epoll和poll只能在linux使用
    //发送数据
    bool sendMsg(QByteArray msg, int timeout = -1);
    //断开连接
    void disconnect();
private:
    //监听读/写缓冲区是否可用
    bool readTimeout(int timout);
    bool writeTimeout(int timeout);
    //控制读写字节的数量，用于解决粘包问题
    int readn(char *buf, int count);
    int writen(const char *buf, int count);
//windows平台中的文件描述符为SOCKET类型，linux中为int类型
#ifdef Q_OS_WIN
    SOCKET m_socket;
#endif
#ifdef Q_OS_LINUX
    int m_socket;
#endif
};

#endif
