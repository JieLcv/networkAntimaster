#include"eventLoop.h"
#include"epollDispatcher.h"
#include"pollDispatcher.h"
#include"selectDispatcher.h"

EventLoop::~EventLoop()
{
}

EventLoop::EventLoop():EventLoop(string())
{
	//委托构造函数,注意不要形成闭环
}

EventLoop::EventLoop(const string threadName)
{
	m_isQuit = true;
	m_threadID = this_thread::get_id();
	//c++11里面互斥锁可以直接用，不需要初始化
	m_threadName = threadName == string() ? "MainThread" : threadName;
	//dispatcher
	m_dispatcher = new EpollDispatcher(this);

	m_channelMap.clear();
	int ret = socketpair(AF_UNIX, SOCK_STREAM, 0, m_socketPair);
	if (ret == -1)
	{
		perror("sockpair error");
		exit(0);
	}
#if 0
	//指定规则：evLoop->socketPair[0]发送数据， evLoop->sockPair[1]接受数据
	Channel* channel = new Channel(m_socketPair[1], FDEvent::ReadEvent, readLocalMessage, nullptr, nullptr, this);
#else
	//绑定 - bind,可调用对象包装器本来不能绑定非静态成员函数，通过绑定器绑定后，就可以被可调用对象包装器包装了
	auto obj = bind(&EventLoop::readLocalMessage, this);
	Channel* channel = new Channel(m_socketPair[1], FDEvent::ReadEvent, obj, nullptr, nullptr, this);
#endif
	//channel添加到任务队列
	addTask(channel, ElemType::ADD);
}

int EventLoop::run()
{
	m_isQuit = false;
	//取出事件分发和检测模型
	//比较线程ID是否正常
	if (m_threadID != this_thread::get_id())
	{
		return -1;
	}
	//循环进行事件处理
	while (!m_isQuit)
	{
		m_dispatcher->dispatch(); //超时时长
		processTaskQ();
	}
	return 0;
}

int EventLoop::eventActivate(int fd, int event)
{
	if (fd < 0)return -1;
	//取出channel
	Channel* channel = m_channelMap[fd];
	assert(channel->getSocket() == fd);
	if (event & (int)FDEvent::ReadEvent && channel->readCallback)
	{
		channel->readCallback(const_cast<void*>(channel->getArg()));
	}
	if (event & (int)FDEvent::WriteEvent && channel->writeCallback)
	{
		channel->writeCallback(const_cast<void*>(channel->getArg()));
	}
	return 0;
}

int EventLoop::addTask(Channel* channel, ElemType type)
{
	//加锁，保护共享资源
	m_mutex.lock();
	//创建新节点
	ChannelElement* node = new ChannelElement;
	//Debug("正在添加任务");
	node->channel = channel;
	node->type = type;
	m_taskQ.push(node);
	//加锁后就写解锁，以防忘记解锁，造成死锁
	m_mutex.unlock();
	//处理节点
	/*细节：
	*	1.对于链表节点的添加：可能时当前线程也可能是其他线程（主线程）
	*		1）.修改fd事件，当前子线程发起，当前子线程处理
	*		2>.添加新的fd,添加任务节点的操作是由主线程发起的
	*   2.不能让主线程处理任务队列，需要由当前子线程处理
	*/
	if (m_threadID == this_thread::get_id())
	{
		//当前子线程
		processTaskQ();
	}
	else
	{
		//主线程 - 告诉子线程处理任务队列中的任务
		//1.子线程在工作 2.子线程被阻塞了：select， poll， epoll
		taskWakeup();
	}
	return 0;
}

int EventLoop::processTaskQ()
{

	while (!m_taskQ.empty())
	{
		m_mutex.lock();
		ChannelElement* node = m_taskQ.front();
		m_taskQ.pop();
		m_mutex.unlock();
		Channel* channel = node->channel;
		if (node->type == ElemType::ADD)
		{
			//添加
			add(channel);
		}
		else if (node->type == ElemType::DELETE)
		{
			//删除
			remove(channel);
		}
		else if (node->type == ElemType::MODIFY)
		{
			//修改
			modify(channel);
		}
		delete node;
	}

	return 0;
}

int EventLoop::add(Channel* channel)
{
	int fd = channel->getSocket();
	if (m_channelMap.find(fd) == m_channelMap.end())
	{
		m_channelMap.insert(make_pair(fd, channel));
		m_dispatcher->setChannel(channel);
		int ret = m_dispatcher->add();
		return ret;
	}
	return -1;
}

int EventLoop::remove(Channel* channel)
{
	int fd = channel->getSocket();
	if (m_channelMap.find(fd) == m_channelMap.end())
	{
		return -1;
	}
	m_dispatcher->setChannel(channel);
	int ret = m_dispatcher->remove();
	return ret;
}

int EventLoop::modify(Channel* channel)
{
	int fd = channel->getSocket();
	if (m_channelMap.find(fd) == m_channelMap.end())
	{
		return -1;
	}
	m_dispatcher->setChannel(channel);
	int ret = m_dispatcher->modify();
	return ret;
}

int EventLoop::freeChannel(Channel* channel)
{
	//删除channel和fd的对应关系
	auto it = m_channelMap.find(channel->getSocket());
	if (it != m_channelMap.end())
	{
		m_channelMap.erase(it);
	}
	//关闭fd
	close(channel->getSocket());
	//释放channel, 此处可能有BUG
	delete channel;
	return 0;
}

int EventLoop::readLocalMessage(void* arg)
{
	struct EventLoop* evLoop = static_cast<EventLoop *>(arg);
	char buf[256];
	//此处有细节，m_sockPair是私有的，但是可以，因为此时的访问在类的内部
	read(evLoop->m_socketPair[1], buf, sizeof(buf));
	return 0;
}

int EventLoop::readMessage()
{
	char buf[256];
	//此处有细节，m_sockPair是私有的，但是可以，因为此时的访问在类的内部
	read(m_socketPair[1], buf, sizeof(buf));
	return 0;
}

void EventLoop::taskWakeup()
{
	const char* msg = "我是要成为海贼王的男人!!!";
	write(m_socketPair[0], msg, strlen(msg));
}
