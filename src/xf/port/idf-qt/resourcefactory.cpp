#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_RESOURCE_FACTORY_IMPLEMENTATION != 0)

#include <QtGlobal>
#include "thread-default.h"
#include "default/dispatcher-active.h"
#include "xf/interface/mutex.h"
#include "resourcefactory.h"

using interface::XFMutex;

//static
interface::XFResourceFactory * interface::XFResourceFactory::getInstance()
{
    return XFResourceFactoryPort::getInstance();
}


interface::XFResourceFactory *XFResourceFactoryPort::getInstance()
{
    static XFResourceFactoryPort resourceFactory;


    return &resourceFactory;
}

interface::XFDispatcher *XFResourceFactoryPort::getDefaultDispatcher()
{
    static XFDispatcherActiveDefault disp;
    return &disp;
}

interface::XFDispatcher *XFResourceFactoryPort::createDispatcher()
{
    return getDefaultDispatcher();
}

interface::XFThread *XFResourceFactoryPort::createThread(interface::XFThreadEntryPointProvider *pProvider, interface::XFThread::EntryMethodBody entryMethod, const char *threadName, const uint32_t stackSize)
{
    return new XFThreadDefault(pProvider,entryMethod,threadName,stackSize);
}

interface::XFMutex *XFResourceFactoryPort::createMutex()
{
    return interface::XFMutex::create();
}

#endif // USE_XF_PORT_IDF_QT_RESOURCE_FACTORY_IMPLEMENTATION
