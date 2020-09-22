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

// TODO: Implement code for XFResourceFactoryPort class

#endif // USE_XF_PORT_IDF_QT_RESOURCE_FACTORY_IMPLEMENTATION
