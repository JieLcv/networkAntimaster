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
	//���
	int add() override;
	//ɾ��
	int remove() override;
	//�޸�
	int modify() override;
	//�¼����  ��ʱ��λ��s
	int dispatch(int timeout = 2) override;
private:
	int m_epfd;
	struct epoll_event* m_events;
	const int m_maxNode = 520;

	int epollCtl(int op);
};
