#include <cassert>
#include <config/xf-config.h>

#if (USE_XF_DISPATCHER_DEFAULT_IMPLEMENTATION != 0)
#if (XF_TRACE_EVENT_PUSH_POP != 0)
    #include "trace/trace.h"
#endif // XF_TRACE_EVENT_PUSH_POP
#include "xf/eventstatus.h"
#include "xf/interface/timeoutmanager.h"
#include "xf/interface/reactive.h"
#include "xf/interface/resourcefactory.h"
#include "dispatcher-default.h"

using interface::XFTimeoutManager;
using interface::XFResourceFactory;
using interface::XFReactive;
using interface::XFMutex;

XFDispatcherDefault::XFDispatcherDefault()
{
	_bExecuting = false;
	_pMutex = XFResourceFactory::getInstance()->createMutex();
}

XFDispatcherDefault::~XFDispatcherDefault()
{
	delete _pMutex;
}

void XFDispatcherDefault::start()
{
	_bExecuting = true;
}

void XFDispatcherDefault::stop()
{
	_bExecuting = false;
}

void XFDispatcherDefault::pushEvent(XFEvent* pEvent)
{
#if defined(XF_TRACE_EVENT_PUSH_POP) && (XF_TRACE_EVENT_PUSH_POP != 0)
        Trace::out("Push event: 0x%x", pEvent);
#endif // XF_TRACE_EVENT_PUSH_POP
        _events.push(pEvent);
}

void XFDispatcherDefault::scheduleTimeout(int timeoutId, int interval, XFReactive* pReactive)
{
    // Forward timeout to the timeout manager
    XFTimeoutManager::getInstance()->scheduleTimeout(timeoutId, interval, pReactive);
}

void XFDispatcherDefault::unscheduleTimeout(int timeoutId, XFReactive* pReactive)
{
   // Forward timeout to the timeout manager
	XFTimeoutManager::getInstance()->unscheduleTimeout(timeoutId, pReactive);
}

int XFDispatcherDefault::execute(const void * param)
{
    (void)param;

    while(_bExecuting)
    {
        while (_events.empty() && _bExecuting)
        {
            _events.pend();	// Wait until something to do
        }

        executeOnce();
    }

    return 0;

}

int XFDispatcherDefault::executeOnce()
{
	//access to the event queue is protected by the implementation of the queue and doesn't need to be managed at this level
    if(!_events.empty())
    {
		const XFEvent* e = _events.front();
        _events.pop();
        dispatchEvent(e);
    }

    return _bExecuting;
}

void XFDispatcherDefault::dispatchEvent(const XFEvent * pEvent) const
{
    XFReactive* target = pEvent->getBehavior();
    if(target->process(pEvent)) //process event, and check if needed to terminate on close
    {
        delete target;
    }
}




#endif // USE_XF_DISPATCHER_DEFAULT_IMPLEMENTATION
