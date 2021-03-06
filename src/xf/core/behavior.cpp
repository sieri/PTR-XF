#include <cassert>
#include "xf/xf.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/timeout.h"
#include "xf/initialevent.h"
#include "xf/behavior.h"

using interface::XFResourceFactory;

XFBehavior::XFBehavior(bool ownDispatcher)
{
    this->_hasOwnDispatcher = ownDispatcher;

    if(this->_hasOwnDispatcher)
    {
    	this->_pDispatcher = XFResourceFactory::getInstance()->createDispatcher();
    }
    else
    {
    	this->_pDispatcher = XFResourceFactory::getInstance()->getDefaultDispatcher();
    }
}

XFBehavior::~XFBehavior()
{
	//check if the dispatcher is owned by this behaviour
	if(this->_hasOwnDispatcher && this->_pDispatcher != XFResourceFactory::getInstance()->getDefaultDispatcher())
	{
		delete _pDispatcher;
	}

}

void XFBehavior::startBehavior()
{
    GEN(XFInitialEvent);
}

void XFBehavior::pushEvent(XFEvent *pEvent)
{
    pEvent->setBehavior(this); //link the event with this behaviour

    this->getDispatcher()->pushEvent(pEvent); //and hand it to the dispatcher

}

bool XFBehavior::deleteOnTerminate() const
{
    return this->deleteOnTerminate_;
}

void XFBehavior::setDeleteOnTerminate(bool deleteBehaviour)
{
    this->deleteOnTerminate_ = deleteBehaviour;
}

const XFEvent *XFBehavior::getCurrentEvent() const
{
    return this->_pCurrentEvent;
}

interface::XFDispatcher *XFBehavior::getDispatcher()
{
    return this->_pDispatcher;
}

const XFTimeout *XFBehavior::getCurrentTimeout()
{
    if(this->_pCurrentEvent->getEventType() != XFEvent::Timeout)
    {
        return nullptr;
    }
    else
    {
        return (XFTimeout*)(this->_pCurrentEvent);
    }
}

void XFBehavior::setCurrentEvent(const XFEvent *pEvent)
{
    this->_pCurrentEvent = pEvent;
}

interface::XFReactive::TerminateBehavior XFBehavior::process(const XFEvent *pEvent)
{
    setCurrentEvent(pEvent);

    XFEventStatus status = this->processEvent();


    if(status.is(XFEventStatus::Terminate))
    {
       return deleteOnTerminate();
    }
    else
    {
        return false;
    }

    if(pEvent->deleteAfterConsume() && (status.is(status.Consumed) ||   //check if needed to be consumed
                                        status.is(status.Terminate) ||
                                        status.is(status.RegionFinished))){
        delete pEvent;
    }
}


