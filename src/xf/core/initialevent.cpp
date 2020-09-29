#include "xf/initialevent.h"

XFInitialEvent::XFInitialEvent():XFEvent(Initial, 42, nullptr)
{

}

bool XFInitialEvent::deleteAfterConsume() const
{
    return true;
}
