#pragma once
#include"dispatcher.h"
#include<sys/select.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
using namespace std;

class SelectDispatcher : public Dispatcher
{
public:
	SelectDispatcher(EventLoop* evLoop);

	~SelectDispatcher();
	//���
	int add() override;
	//ɾ��
	int remove() override;
	//�޸�
	int modify() override;
	//�¼����  ��ʱ��λ��s
	int dispatch(int timeout = 2) override;
private:
	fd_set m_readSet;
	fd_set m_writeSet;
	const int m_maxSize = 1024;
	void setFdSet();
	void clearFdSet();
};