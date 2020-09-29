#include "xf/timeout.h"

XFTimeout::XFTimeout(int id, int interval, interface::XFReactive *pBehavior):XFEvent(XFEventType::Timeout,id,pBehavior)
{
    this->_interval = this->_relTicks = interval;
}

bool XFTimeout::deleteAfterConsume() const
{
    return true;
}
