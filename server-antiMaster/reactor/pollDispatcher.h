#pragma once
#include"dispatcher.h"
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<poll.h>
class PollDispatcher : public Dispatcher
{
public:
	PollDispatcher(EventLoop* evLoop);

	~PollDispatcher();
	//���
	int add() override;
	//ɾ��
	int remove() override;
	//�޸�
	int modify() override;
	//�¼����  ��ʱ��λ��s
	int dispatch(int timeout = 2) override;
private:
	int m_maxfd;
	struct pollfd *m_fds;
	const int m_maxNode = 1024;
};