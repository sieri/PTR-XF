
#include <config/xf-config.h>

#if (USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION != 0)

#include <cassert>
#include "xf/interface/reactive.h"
#include "xf/interface/mutex.h"
#include "port-functions.h"
#include "timeoutmanager-default.h"

using interface::XFMutex;

interface::XFTimeoutManager * interface::XFTimeoutManager::getInstance()
{
    return XFTimeoutManagerDefault::getInstance();
}

// TODO: Implement code for XFTimeoutManagerDefault class

#endif // USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION

interface::XFTimeoutManager *XFTimeoutManagerDefault::getInstance()
{
    static XFTimeoutManagerDefault instance = XFTimeoutManagerDefault(); //TODO: check this look buggy
    return &instance;
}

XFTimeoutManagerDefault::~XFTimeoutManagerDefault()
{

}

XFTimeoutManagerDefault::XFTimeoutManagerDefault():interface::XFTimeoutManager()
{

}

void XFTimeoutManagerDefault::start()
{
    XF_startTimeoutManagerTimer(_tickInterval);
}

void XFTimeoutManagerDefault::scheduleTimeout(int32_t timeoutId, int32_t interval, interface::XFReactive *pReactive)
{
    XFTimeout* newTimeout = new XFTimeout(timeoutId, interval, pReactive);

    addTimeout(newTimeout);
}

void XFTimeoutManagerDefault::unscheduleTimeout(int32_t timeoutId, interface::XFReactive *pReactive)
{
    TimeoutList::iterator it =  _timeouts.begin();
    //TODO: Lock
    while (it != _timeouts.end()) {

        if((*it)->getBehavior() == pReactive && (*it)->getId() == timeoutId)
        {
            it = _timeouts.erase(it);
        }
        else
        {
            it++;
        }

    }
}

void XFTimeoutManagerDefault::tick()
{
    if(!_timeouts.empty())
    {
        _timeouts.front()->substractFromRelTicks(_tickInterval);

        while(!_timeouts.empty() && _timeouts.front()->getRelTicks() <= 0)
        {
            returnTimeout(_timeouts.front());
            _timeouts.pop_front();
        }
    }

}


void XFTimeoutManagerDefault::addTimeout(XFTimeout *pNewTimeout)
{

    //TODO:Check access
    TimeoutList::iterator it =  _timeouts.begin();

    bool inserted = false;

    while (!inserted && it!= _timeouts.end()) {
        if((*it)->getRelTicks() < pNewTimeout->getRelTicks()){

            pNewTimeout->substractFromRelTicks((*it)->getRelTicks()); //remove the adequate amount of relative ticks

            it++;
        }
        else
        {
            //add new timeout in front of current one.
            (*it)->substractFromRelTicks(pNewTimeout->getRelTicks()); //remove the adequate amount of relative ticks
            _timeouts.insert(it,pNewTimeout);
            inserted = true;
        }
    }

    if(!inserted)
    {
        _timeouts.insert(it,pNewTimeout); //insert at the end
    }
}

void XFTimeoutManagerDefault::returnTimeout(XFTimeout *pTimeout)
{
    pTimeout->getBehavior()->pushEvent(pTimeout); //push the timeout to the event queue
}
