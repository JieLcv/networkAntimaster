#include <fstream>
#include "tcpServer.h"
#include <sstream>
#include "RsaCrypto.h"

TcpServer::TcpServer(unsigned short port, int threadNum)
{
	m_port = port;
	m_mainLoop = new EventLoop;
	m_threadNum = threadNum;
	m_threadPool = new ThreadPool(m_mainLoop, threadNum);
	setListen();
}

void TcpServer::setListen()
{
	// 1.创建监听的id，一个文件描述符操作两个缓冲区
	m_lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(m_lfd == -1)
	{
		perror("create lfd error");
		return;
	}
	// 2.设置端口复用
	//主动断开的一方需要等2msl时间，才能重新使用，若想立即使用，需要设置端口复用
	int opt = 1;
	int ret = setsockopt(m_lfd, SOL_SOCKET, SO_REUSEADDR, &(opt), sizeof(opt));
	if (ret == -1)
	{
		perror("setsockopt error");
		return;
	}
	// 3.绑定
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(m_port);
	addr.sin_addr.s_addr = INADDR_ANY;
	ret = bind(m_lfd, (struct sockaddr*)&addr, sizeof(addr));
	if (ret == -1)
	{
		perror("bind error");
		return;
	}
	// 4. 返回fd 最大128，超过128时，仍为128
	ret = listen(m_lfd, 128);
	if (ret == -1)
	{
		perror("listen error");
		return;
	}
}

void TcpServer::run()
{
    //生成非对称密钥对
    RsaCrypto *rsa = new RsaCrypto;
    saveRsaKey();
	//启动线程池
	Debug("线程池启动成功");
	m_threadPool->run();
	//添加检测的任务
	Channel* channel = new Channel(m_lfd, FDEvent::ReadEvent, acceptConnection, nullptr, nullptr, this);
	m_mainLoop->addTask(channel, ElemType::ADD);
	Debug("主线程添加任务成功， fd=%d", m_lfd);
	//启动反应堆模型
	m_mainLoop->run();
}

int TcpServer::acceptConnection(void* arg)
{
	TcpServer* server = static_cast<TcpServer*>(arg);
	//和客户端建立连接
	Debug("正在检测, lfd=%d\n", server->m_lfd);
	int cfd = accept(server->m_lfd, NULL, NULL);
	Debug("接受到cfd:%d", cfd);
	//从线程池中取出一个子线程的反应堆实例，去处理这个cfd
	EventLoop* evLoop = server->m_threadPool->takeWorkerEventLoop();
	//将cfd放到TcpConnection中处理
	new TcpConnection(cfd, evLoop);
	return 0;
}

void TcpServer::saveRsaKey()
{
    //生成密钥对
    RsaCrypto *rsa = new RsaCrypto;
    rsa->generateRsaKey(RsaCrypto::BITS_2K);
    delete rsa;
    //读磁盘文件
    //读公钥
    ifstream ifs("public.pem");
    stringstream sstr;
    sstr << ifs.rdbuf();
    string data = sstr.str();
    ifs.close();
    //创建redis对象
    Room redis;
    assert(redis.initEnvironment());
    redis.clear();
    redis.saveRsaSecKey("PublicKey", data);

    //私钥
    ifs.open("private.pem");
    sstr << ifs.rdbuf();
    data = sstr.str();
    ifs.close();
    redis.saveRsaSecKey("PrivateKey", data);
    unlink("public.pem");
    unlink("private.pem");

}
