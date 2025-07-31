#include "tcpConnection.h"
#include "httpRequest.h"
#include <fstream>
#include <sstream>
#include "Log.h"
#include "Room.h"


TcpConnection::TcpConnection(int fd, EventLoop* evLoop)
{
	m_evLoop = evLoop;
	m_readBuf = new Buffer(10240);
	m_writeBuf = new Buffer(10240);
    m_reply = new Communication;
    auto delFunc = std::bind(&TcpConnection::addDeleteTask, this);
    auto writeFunc = std::bind(&TcpConnection::addWriteTask, this, std::placeholders::_1);
    m_reply->setCallback(writeFunc, delFunc);
	m_name = "Connection-" + to_string(fd);
//    std::cout << "创建连接: " << m_name << endl;
    Debug("创建连接: %s", m_name.data());
    prepareSecretKey();
	m_channel = new Channel(fd, FDEvent::WriteEvent, processRead, processWrite, destroy, this);
	evLoop->addTask(m_channel, ElemType::ADD);
	Debug("和客户端建立连接， threadName:%s, connName:%s", evLoop->getThreadName().data(), m_name.data());
}

TcpConnection::~TcpConnection()
{
	if (m_readBuf && m_readBuf->readableSize() == 0 &&
		m_writeBuf && m_writeBuf->readableSize() == 0)
	{
		delete m_readBuf;
		delete m_writeBuf;
		m_evLoop->freeChannel(m_channel);
	}
	Debug("连接断开，释放资源， gameover, connName;%s",m_name.data());
}

int TcpConnection::processRead(void* arg)
{
	TcpConnection* conn = static_cast<struct TcpConnection*>(arg);

	//接受数据
	int socket = conn->m_channel->getSocket();
	int count = conn->m_readBuf->socketRead(socket);
	if (count > 0)
	{
        //解析斗地主数据
        conn->m_reply->parseRequest(conn->m_readBuf);
	}
	else if(count < 0)
	{
        //断开和客户端的连接
        conn->addDeleteTask();
        Debug("和客户端的连接已经断开了...");
	}
	return 0;
}

int TcpConnection::processWrite(void* arg)
{
	TcpConnection* conn = static_cast<struct TcpConnection*>(arg);
	//发送数据
	int count = conn->m_writeBuf->sendData(conn->m_channel->getSocket());
	if (count > 0)
	{
//		Debug("开始发送数据了(基于写事件发送....), count=%d", count);
		//判断数据是否全部发送出去了
		if (conn->m_writeBuf->readableSize() == 0)
		{
			//1.不在检测写事件，--修改channel中保存的事件
			conn->m_channel->setCurrentEvent(FDEvent::ReadEvent);
			//2.修改dispatcher检测的集合--添加任务节点
			conn->m_evLoop->addTask(conn->m_channel, ElemType::MODIFY);
//            std::cout << "数据发送完毕" << endl;
            Debug("数据发送完毕");
		}
	}
	return 0;
}

int TcpConnection::destroy(void* arg)
{
	TcpConnection* conn = static_cast<struct TcpConnection*>(arg);
	if (conn != nullptr)
	{
		delete conn;
	}
	return 0;
}

void TcpConnection::prepareSecretKey()
{
    Room redis;
    redis.initEnvironment();
    Debug("开始解析");
    //读公钥
    std::string pubKey = redis.rsaSecKey("PublicKey");
    //发送数据
    Message msg;
    msg.rescode = RespondCode::RsaFenFa;
    msg.data1 = pubKey;
    Debug("公钥读取完毕");
    RsaCrypto rsa;
    rsa.parseStringToKey(redis.rsaSecKey("PrivateKey"), RsaCrypto::PrivateKey);
    std::string data = rsa.sign(pubKey);
    msg.data2 = data;
    Debug("data:%s", data.data());
    Codec codec(&msg);
    data = codec.encodeMsg();
    //写数据
    m_writeBuf->appendPackage(data);

}

void TcpConnection::addWriteTask(std::string data)
{
    Debug("添加写任务");
    m_writeBuf->appendPackage(data);
#if 1 //通过事件进行发送
    //1.不在检测写事件，--修改channel中保存的事件
    m_channel->setCurrentEvent(FDEvent::WriteEvent);
    //2.修改dispatcher检测的集合--添加任务节点
    m_evLoop->addTask(m_channel, ElemType::MODIFY);
#else //直接发送
    m_writeBuf->sendData(m_channel->getSocket());
#endif
}

void TcpConnection::addDeleteTask()
{
    Debug("和客户端断开连接, connName = %s", m_name.data());
    m_evLoop->addTask(m_channel, ElemType::DELETE);

}
