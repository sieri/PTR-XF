#include "xf/nulltransition.h"

XFNullTransition::XFNullTransition(interface::XFReactive *pBehavior): XFEvent(NullTransition, 0, nullptr)
{
    this->_pBehavior = pBehavior;
}

bool XFNullTransition::deleteAfterConsume() const
{
    return true;
}
