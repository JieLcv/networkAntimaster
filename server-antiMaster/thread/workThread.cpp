#include "workThread.h"



WorkerThread::WorkerThread(int index)
{
	m_evLoop = nullptr;
	m_thread = nullptr;
	m_threadID = thread::id();
	m_name = "SubThread-" + to_string(index);
}

WorkerThread::~WorkerThread()
{
	if (m_thread != nullptr)
	{
		delete m_thread;
	}
}

void WorkerThread::run()
{
	//创建子线程函数
	m_thread = new thread(&WorkerThread::running, this);
	//阻塞主线程，让当前函数不会直接结束，防止子线程中eventLoop还未创建出来，就往其中添加任务
	//下行代码会给m_mutex加锁
	unique_lock<mutex> locker(m_mutex);
	while (m_evLoop == nullptr)
	{
		m_cond.wait(locker);
	}
	//locker的生命周期结束，在释放之前，会把互斥锁解开
}

void WorkerThread::running()
{
	m_mutex.lock();
	m_evLoop = new EventLoop(m_name);
	m_mutex.unlock();
	//唤醒一个子线程
	m_cond.notify_one();
	m_evLoop->run();
}
