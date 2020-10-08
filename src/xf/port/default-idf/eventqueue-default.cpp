#include <config/xf-config.h>

#if (USE_XF_EVENT_QUEUE_DEFAULT_IDF_IMPLEMENTATION != 0)

#include <cassert>
#include "eventqueue-default.h"



XFEventQueueDefault::XFEventQueueDefault()
{

}

XFEventQueueDefault::~XFEventQueueDefault()
{

}

bool XFEventQueueDefault::empty() const
{
	return _queue.empty();
}

bool XFEventQueueDefault::push(const XFEvent* pEvent)
{
	//STD lists aren't safe from interrupts so need to be secured at this level, prevent having to lock more than the push
	_mutex.lock();
	_queue.push(pEvent);
	_mutex.unlock();
	return true;

}

const XFEvent * XFEventQueueDefault::front()
{
	return _queue.front();
}

void XFEventQueueDefault::pop()
{
	_mutex.lock();
	_queue.pop();
	_mutex.unlock();
}

bool XFEventQueueDefault::pend()
{
	//wait for the event queue to fill in. shouldn't be locked in because if waiting events can only come from interrupts.
	while(_queue.empty());
	return 	_queue.empty();
}

#endif // USE_XF_EVENT_QUEUE_DEFAULT_IDF_IMPLEMENTATION
