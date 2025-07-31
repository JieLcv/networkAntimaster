#pragma once
#include"dispatcher.h"
#include<thread>
#include<queue>
#include<map>
#include<mutex>
#include<assert.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
//#include"Log.h"
using namespace std;

//处理该节点中的channel的方式
enum class ElemType:char { ADD, DELETE, MODIFY };
//定义任务队列的节点
struct ChannelElement
{
	ElemType type;    //如何处理该节点中的channel
	Channel* channel;
};
//防止Dispatcher和EventLoop相互包含
class Dispatcher;
class EventLoop
{
public:
	//释放
	~EventLoop();
	//初始化
	EventLoop();
	EventLoop(const string threadName);
	//初始化主线程，指定主线程名字
	//启动反应堆模型
	int run();
	//处理激活的文件fd
	int eventActivate(int fd, int event);
	//添加任务到任务队列
	int addTask(struct Channel* channel, ElemType type);
	//处理任务队列中的任务
	int processTaskQ();
	//处理dispatcher中的节点
	int add(Channel* channel);
	int remove(Channel* channel);
	int modify(Channel* channel);
	//释放channel
	int freeChannel(struct Channel* channel);
	static int readLocalMessage(void *arg);
	int readMessage();
	//返回线程ID
	inline thread::id getThreadID()
	{
		return m_threadID;
	}
	inline string getThreadName()
	{
		return m_threadName;
	}

private:
	bool m_isQuit;
	//该指针指向子类的实例 epoll, poll, select
	Dispatcher* m_dispatcher;
	//任务队列
	queue<ChannelElement*> m_taskQ;
	//map存放文件描述符和channel的映射关系
	map<int, Channel*> m_channelMap;
	//线程id， name, nutex
	thread::id m_threadID;
	string m_threadName;
	mutex m_mutex;
	int m_socketPair[2];  //存储本地通信的fd 通过socketpair初始化
	void taskWakeup();
};
