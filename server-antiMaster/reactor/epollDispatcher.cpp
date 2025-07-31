
#include "epollDispatcher.h"
#include"dispatcher.h"



EpollDispatcher::EpollDispatcher(EventLoop* evLoop) : Dispatcher(evLoop)
{
	m_epfd = epoll_create(10);
	if (m_epfd == -1)
	{
		perror("epoll_create error");
		exit(0);
	}
	//calloc会自动初始化初始为0，不需要再用memset, Max为需要的内存块的个数
	m_events = new struct epoll_event[m_maxNode];
	m_name = "Epoll";
}

EpollDispatcher::~EpollDispatcher()
{
	close(m_epfd);
	delete[] m_events;
}

int EpollDispatcher::add()
{
	int ret = epollCtl(EPOLL_CTL_ADD);
	if (ret == -1)
	{
		perror("epoll_ctl_add error");
		exit(0);
	}
	return ret;
}

int EpollDispatcher::remove()
{
	int ret = epollCtl(EPOLL_CTL_DEL);
	if (ret == -1)
	{
		perror("epoll_ctl_del error");
		exit(0);
	}
	//通过channel释放对应的TcpConnection资源
	m_channel->destroyCallback(const_cast<void*>(m_channel->getArg()));
	return ret;
}

int EpollDispatcher::modify()
{
	int ret = epollCtl(EPOLL_CTL_MOD);
	if (ret == -1)
	{
		perror("epoll_ctl_mod error");
		exit(0);
	}
	return ret;
}

int EpollDispatcher::dispatch(int timeout)
{
	int count = epoll_wait(m_epfd, m_events, m_maxNode, timeout * 1000);
	for (int i = 0; i < count; i++)
	{
		uint32_t events = m_events[i].events;
		int fd = m_events[i].data.fd;
		//对端断开连接之后自动产生EPOLLERR事件，对端断开连接之后还和对方进行数据通信自动产生EPOLLHUP事件
		if (events & EPOLLERR || events & EPOLLHUP)
		{
			//epollRemove(Channel, evLoop)
			continue;
		}
		if (events & EPOLLIN)
		{
			m_evLoop->eventActivate(fd, static_cast<int>(FDEvent::ReadEvent));
		}
		if (events & EPOLLOUT)
		{
			m_evLoop->eventActivate(fd, static_cast<int>(FDEvent::WriteEvent));
		}
	}
	return 0;
}

int EpollDispatcher::epollCtl(int op)
{
	struct epoll_event ev;
	ev.data.fd = m_channel->getSocket();
	uint32_t events = 0;
	if (m_channel->getEvent() & static_cast<int>(FDEvent::ReadEvent))
	{
		events |= EPOLLIN;
	}
	if (m_channel->getEvent() & static_cast<int>(FDEvent::WriteEvent))
	{
		events |= EPOLLOUT;
	}
	ev.events = events;
	int ret = epoll_ctl(m_epfd, op, m_channel->getSocket(), &ev);
	return ret;
}
