
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



interface::XFTimeoutManager *XFTimeoutManagerDefault::getInstance()
{
    static XFTimeoutManagerDefault instance;
    return &instance;
}

XFTimeoutManagerDefault::~XFTimeoutManagerDefault()
{
    _timeouts.clear();
    delete _pMutex;
}

XFTimeoutManagerDefault::XFTimeoutManagerDefault():interface::XFTimeoutManager()
{
    _pMutex = interface::XFMutex::create();

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
    _pMutex->lock();

    TimeoutList::iterator it =  _timeouts.begin();


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

    _pMutex->unlock();

}

void XFTimeoutManagerDefault::tick()
{

    _pMutex->lock();

    if(!_timeouts.empty())
    {
        _timeouts.front()->substractFromRelTicks(_tickInterval);

        while(!_timeouts.empty() && _timeouts.front()->getRelTicks() <= 0) //send all timers that ended up at 0
        {
            returnTimeout(_timeouts.front());
            _timeouts.pop_front();
        }
    }

    _pMutex->unlock();

}


void XFTimeoutManagerDefault::addTimeout(XFTimeout *pNewTimeout)
{

    _pMutex->lock();

    TimeoutList::iterator it =  _timeouts.begin();

    bool inserted = false;

    while (!inserted && it!= _timeouts.end()) {
        if((*it)->getRelTicks() <= pNewTimeout->getRelTicks()){

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
    _pMutex->unlock();

}

void XFTimeoutManagerDefault::returnTimeout(XFTimeout *pTimeout)
{
    pTimeout->getBehavior()->pushEvent(pTimeout); //push the timeout to the event queue
}


#endif // USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION
