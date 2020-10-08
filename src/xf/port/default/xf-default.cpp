#include <cassert>
#include <config/xf-config.h>

#if (USE_XF_DEFAULT_IMPLEMENTATION != 0)

#include "xf/interface/timeoutmanager.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/xf.h"

using interface::XFResourceFactory;
using interface::XFTimeoutManager;

bool XF::_bInitialized = false;
bool XF::_bIsRunning = false;

void XF::initialize(int timeInterval, int argc, char** argv){
    if (!_bInitialized)
    {
       // Create and initialize TimeoutManager
        interface::XFTimeoutManager::getInstance()->initialize(timeInterval);
        // Start it
        interface::XFTimeoutManager::getInstance()->start();

        _bInitialized = true;
    }
}

int XF::exec()
{
	_bIsRunning = true;
	 // Start default dispatcher
	XFResourceFactory::getInstance()->getDefaultDispatcher()->start();


	int retVal = XFResourceFactory::getInstance()->getDefaultDispatcher()->execute();

	_bIsRunning = false;

	return retVal;
}

int XF::execOnce()
{
	_bIsRunning = true;

	int retVal = XFResourceFactory::getInstance()->getDefaultDispatcher()->executeOnce();

	_bIsRunning = false;

	return retVal;
}

bool XF::isRunning()
{
	return _bIsRunning;
}
#endif // USE_XF_DEFAULT_IMPLEMENTATION




void XF_initialize(int timeInterval)
{
	XF::initialize(timeInterval, 0, NULL);
}

void XF_exec()
{
	XF::exec();
}

void XF_execOnce()
{
	XF::execOnce();
}

