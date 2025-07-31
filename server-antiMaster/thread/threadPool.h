#pragma once
#include"eventLoop.h"
#include"workThread.h"
#include<assert.h>
#include<vector>
using namespace std;
//定义线程池
class ThreadPool
{
public:
	//初始化线程池
	ThreadPool(EventLoop* mainLoop, int count);
	//释放线程池
	~ThreadPool();
	//启动线程池
	void run();
	//取出线程池中的某个子线程的反应堆实例
	EventLoop* takeWorkerEventLoop();
private:
	//主线程的反应堆模型
	EventLoop* m_mainLoop;
	bool m_isStart;
	int m_threadNum;
	vector<WorkerThread*> m_workerThreads;
	int m_index;
};


