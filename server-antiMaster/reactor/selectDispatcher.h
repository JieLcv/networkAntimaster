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
	//添加
	int add() override;
	//删除
	int remove() override;
	//修改
	int modify() override;
	//事件检测  超时单位：s
	int dispatch(int timeout = 2) override;
private:
	fd_set m_readSet;
	fd_set m_writeSet;
	const int m_maxSize = 1024;
	void setFdSet();
	void clearFdSet();
};