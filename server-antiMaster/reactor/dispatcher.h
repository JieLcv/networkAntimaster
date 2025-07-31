#pragma once
#include"channel.h"
#include"eventLoop.h"
#include<string>
using namespace std;
//IO��·����ģ��
//��ֹEventLoop��Dispatcher�ظ�����
class EventLoop;
class Dispatcher 
{
public:
	Dispatcher(EventLoop* evLoop);
	//�粻����Ϊ������������ָ��ָ�����������ͷŵ��Ǹ���Ĳ��֣��������û���ͷ�
	virtual ~Dispatcher();
	//���
	virtual int add();
	//ɾ��
	virtual int remove();
	//�޸�
	virtual int modify();
	//�¼����  ��ʱ��λ��s
	virtual int dispatch(int timeout = 2);
	inline void setChannel(Channel* channel)
	{
		m_channel = channel;
	}
protected:
	//�����Ա����ʱ����ֱ�ӳ�ʼ��
	string m_name = string();
	Channel* m_channel;
	EventLoop* m_evLoop;
};
