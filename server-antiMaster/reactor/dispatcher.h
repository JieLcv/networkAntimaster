#pragma once
#include"channel.h"
#include"eventLoop.h"
#include<string>
using namespace std;
//IO多路复用模型
//防止EventLoop和Dispatcher重复包含
class EventLoop;
class Dispatcher 
{
public:
	Dispatcher(EventLoop* evLoop);
	//如不声名为虚析构，父类指针指向子类对象后，释放的是父类的部分，而子类的没有释放
	virtual ~Dispatcher();
	//添加
	virtual int add();
	//删除
	virtual int remove();
	//修改
	virtual int modify();
	//事件检测  超时单位：s
	virtual int dispatch(int timeout = 2);
	inline void setChannel(Channel* channel)
	{
		m_channel = channel;
	}
protected:
	//定义成员变量时可以直接初始化
	string m_name = string();
	Channel* m_channel;
	EventLoop* m_evLoop;
};
