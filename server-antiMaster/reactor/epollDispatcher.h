#pragma once
#include"dispatcher.h"
#include<unistd.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<stdio.h>
class EpollDispatcher: public Dispatcher
{
public:
	EpollDispatcher(EventLoop* evLoop);
	~EpollDispatcher();
	//添加
	int add() override;
	//删除
	int remove() override;
	//修改
	int modify() override;
	//事件检测  超时单位：s
	int dispatch(int timeout = 2) override;
private:
	int m_epfd;
	struct epoll_event* m_events;
	const int m_maxNode = 520;

	int epollCtl(int op);
};
