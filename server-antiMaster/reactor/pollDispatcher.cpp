#include "pollDispatcher.h"


PollDispatcher::PollDispatcher(EventLoop* evLoop):Dispatcher(evLoop)
{
	m_maxfd = 0;
	m_fds = new struct pollfd[m_maxNode];
	for (int i = 0; i < m_maxNode; ++i)
	{
		m_fds[i].fd = -1;
		m_fds[i].events = 0;
		m_fds[i].revents = 0;
	}
	m_name = "Poll";
}

PollDispatcher::~PollDispatcher()
{
	delete[] m_fds;
}

int PollDispatcher::add()
{
	int events = 0;
	if (m_channel->getEvent() & static_cast<int>(FDEvent::ReadEvent));
	{
		events |= POLLIN;
		printf("添加poll读事件：%d\n", m_channel->getSocket());
	}
	if (m_channel->getEvent() & static_cast<int>(FDEvent::WriteEvent))
	{
		events |= POLLOUT;
	}
	int i = 0;
	for (; i < m_maxNode; ++i)
	{
		if (m_fds[i].fd == -1)
		{
			m_fds[i].fd = m_channel->getSocket();
			m_fds[i].events = events;
			m_maxfd = m_maxfd < i ? i : m_maxfd;
			printf("添加poll成功：%d\n", m_channel->getSocket());
			break;
		}
	}
	//epoll使用场景：检测的文件描述符特别多
	//poll使用场景：检测的文件描述符不多，且待检测的文件描述符大多数处于激活状态
	if (i >= m_maxNode)return -1;

	return 0;
}

int PollDispatcher::remove()
{
	int i = 0;
	for (; i < m_maxNode; ++i)
	{
		if (m_fds[i].fd == m_channel->getSocket())
		{
			m_fds[i].fd = -1;
			m_fds[i].events = 0;
			m_fds[i].revents = 0;
			break;
		}
	}
	//通过channel释放对应的TcpConnection资源
	m_channel->destroyCallback(const_cast<void*>(m_channel->getArg()));
	if (i >= m_maxNode)return -1;
	return 0;
}

int PollDispatcher::modify()
{
	short int events = 0;
	if (m_channel->getEvent() & static_cast<int>(FDEvent::ReadEvent))
	{
		events |= POLLIN;
	}
	if (m_channel->getEvent() & static_cast<int>(FDEvent::WriteEvent))
	{
		events |= POLLOUT;
	}
	short int i = 0;
	for (; i < m_maxNode; ++i)
	{
		if (m_fds[i].fd == m_channel->getSocket())
		{
			m_fds[i].events = events;
			break;
		}
	}
	if (i >= m_maxNode)return -1;
	return 0;
}

int PollDispatcher::dispatch(int timeout)
{
	//maxfd+1,是因为底层源码判断的时候是<, 而maxfd下标是有效的
	int count = poll(m_fds, m_maxfd + 1, timeout * 1000);
	if (count == -1)
	{
		perror("poll");
		exit(0);
	}
	for (int i = 0; i < m_maxfd + 1; i++)
	{
		if (m_fds[i].fd == -1)continue;

		if (m_fds[i].revents & POLLIN)
		{
			m_evLoop->eventActivate(m_fds[i].fd, static_cast<int>(FDEvent::ReadEvent));
		}
		if (m_fds[i].revents & POLLOUT)
		{
			m_evLoop->eventActivate(m_fds[i].fd, static_cast<int>(FDEvent::WriteEvent));
		}
	}
	return 0;
}
