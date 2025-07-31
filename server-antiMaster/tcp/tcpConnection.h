#pragma once
#include"eventLoop.h"
#include"channel.h"
#include"buffer.h"
#include"httpRequest.h"
#include"httpResponse.h"
#include "Codec.h"
#include "RsaCrypto.h"
#include "Communication.h"

using namespace std;
class TcpConnection
{
public:
	//初始化
	TcpConnection(int fd, struct EventLoop* evLoop);
	//资源释放
	~TcpConnection();
    //发送数据
    void addWriteTask(std::string data);
    //释放资源
    void addDeleteTask();
    //准备密钥
    void prepareSecretKey();
	static int processRead(void* arg);
	static int processWrite(void* arg);
	static int destroy(void* arg);
private:
	EventLoop* m_evLoop;
	Channel* m_channel;
	Buffer* m_readBuf;
	Buffer* m_writeBuf;
	string m_name;
    Communication *m_reply;
};
