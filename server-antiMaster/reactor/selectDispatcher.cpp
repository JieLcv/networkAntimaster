#include"selectDispatcher.h"

SelectDispatcher::SelectDispatcher(EventLoop* evLoop):Dispatcher(evLoop)
{
	FD_ZERO(&m_readSet);
	FD_ZERO(&m_writeSet);
	m_name = "Select";
}

SelectDispatcher::~SelectDispatcher()
{
}

int SelectDispatcher::add()
{
	if (m_channel->getSocket() >= m_maxSize)return -1;
	setFdSet();
	return 0;
}

int SelectDispatcher::remove()
{
	clearFdSet();
	//通过channel释放对应的TcpConnection资源
	m_channel->destroyCallback(const_cast<void*>(m_channel->getArg()));
	return 0;
}

int SelectDispatcher::modify()
{
	//在项目中读写事件互斥
	if (m_channel->getEvent() & static_cast<int>(FDEvent::ReadEvent))
	{
		FD_SET(m_channel->getSocket(), &m_readSet);
		FD_CLR(m_channel->getSocket(), &m_writeSet);
	}
	if (m_channel->getEvent() & static_cast<int>(FDEvent::WriteEvent))
	{
		FD_SET(m_channel->getSocket(), &m_writeSet);
		FD_CLR(m_channel->getSocket(), &m_readSet);
	}
}

int SelectDispatcher::dispatch(int timeout)
{
	struct timeval val;
	val.tv_sec = timeout;
	val.tv_usec = 0;
	fd_set readSet = m_readSet;
	fd_set writeSet = m_writeSet;
	//因为readSet和writeSet是传入传出参数，若直接传入data里面的set，会导致set里面检测的文件描述符越来越少,因此需要备份
	int count = select(m_maxSize, &readSet, &writeSet, NULL, &val);
	if (count == -1)
	{
		perror("select");
		exit(0);
	}
	for (int i = 0; i < m_maxSize; i++)
	{
		if (FD_ISSET(i, &readSet))
		{
			m_evLoop->eventActivate(i, static_cast<int>(FDEvent::ReadEvent));

		}
		if (FD_ISSET(i, &writeSet))
		{
			m_evLoop->eventActivate(i, static_cast<int>(FDEvent::WriteEvent));
		}
	}
	return 0;
}

void SelectDispatcher::setFdSet()
{
	if (m_channel->getEvent() & static_cast<int>(FDEvent::ReadEvent))
	{
		FD_SET(m_channel->getSocket(), &m_readSet);
	}
	if (m_channel->getEvent() & static_cast<int>(FDEvent::WriteEvent))
	{
		FD_SET(m_channel->getSocket(), &m_writeSet);
	}

}

void SelectDispatcher::clearFdSet()
{
	if (m_channel->getEvent() & static_cast<int>(FDEvent::ReadEvent))
	{
		FD_CLR(m_channel->getSocket(), &m_readSet);
	}
	if (m_channel->getEvent() & static_cast<int>(FDEvent::WriteEvent))
	{
		FD_CLR(m_channel->getSocket(), &m_readSet);
	}
}
