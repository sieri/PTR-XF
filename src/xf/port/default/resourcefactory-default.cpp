#include <config/xf-config.h>

#if (USE_XF_RESOURCE_FACTORY_DEFAULT_IMPLEMENTATION != 0)

#include "resourcefactory-default.h"
#include "mutex-default.h"

//static
interface::XFResourceFactory * interface::XFResourceFactory::getInstance()
{
	return XFResourceFactoryDefault::getInstance();
}


interface::XFResourceFactory *XFResourceFactoryDefault::getInstance()
{
    static XFResourceFactoryDefault resourceFactory;
    return &resourceFactory;
}

interface::XFDispatcher *XFResourceFactoryDefault::getDefaultDispatcher()
{
    static XFDispatcherDefault disp;
    return &disp;
}

interface::XFDispatcher *XFResourceFactoryDefault::createDispatcher()
{
    return getDefaultDispatcher();
}

interface::XFThread *XFResourceFactoryDefault::createThread(interface::XFThreadEntryPointProvider *pProvider, interface::XFThread::EntryMethodBody entryMethod, const char *threadName, const uint32_t stackSize)
{
    return 0;
}

interface::XFMutex *XFResourceFactoryDefault::createMutex()
{
    return interface::XFMutex::create();
}







#endif // USE_XF_RESOURCE_FACTORY_DEFAULT_IMPLEMENTATION
