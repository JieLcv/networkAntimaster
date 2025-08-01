#include "channel.h"


Channel::Channel(int fd, FDEvent events, handleFunc readFunc, handleFunc writeFunc, handleFunc destroyFunc, void* arg)
{
	m_arg = arg;
	m_fd = fd;
	m_events = static_cast<int>(events);
	readCallback = readFunc;
	writeCallback = writeFunc;
	destroyCallback = destroyFunc;
}

void Channel::writeEventEnable(bool flag)
{
	if (flag)
	{
		m_events |= static_cast<int>(FDEvent::WriteEvent);
	}
	else
	{
		m_events = m_events & ~static_cast<int>(FDEvent::WriteEvent);
	}
}

bool Channel::isWriteEventEnable()
{
	return m_events & (int)FDEvent::WriteEvent;
}

bool Channel::isReadEventEnable()
{
    return m_events & (int)FDEvent::ReadEvent;
}
void Channel::setCurrentEvent(FDEvent ev)
{
    m_events = static_cast<int>(ev);
}
