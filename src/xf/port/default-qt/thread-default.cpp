#include <config/xf-config.h>

#if (USE_XF_THREAD_DEFAULT_QT_IMPLEMENTATION != 0)

#include <cassert>
#include <string.h>
#include "thread-default.h"

#if !defined(XFTHREAD_DEFAULT_STACK_SIZE)
    #define XFTHREAD_DEFAULT_STACK_SIZE	256
#endif

// TODO: Implement code for XFThreadDefault class

#endif // USE_XF_THREAD_DEFAULT_QT_IMPLEMENTATION

void XFThreadDefault::start()
{
    this->QThread::start();
}

void XFThreadDefault::stop()
{

}

void XFThreadDefault::setPriority(XFThreadPriority priority)
{
    this->QThread::setPriority(QThread::Priority(priority));
}

XFThreadPriority XFThreadDefault::getPriority() const
{
    return (XFThreadPriority) this->priority();
}

void XFThreadDefault::delay(uint32_t milliseconds)
{
    this->wait(milliseconds);
}

XFThreadDefault::XFThreadDefault(interface::XFThreadEntryPointProvider *pProvider, interface::XFThread::EntryMethodBody entryMethod, const char *threadName, const uint32_t stackSize):QThread(),interface::XFThread()
{
    this->_pEntryMethodProvider = pProvider;
    this->_entryMethod = entryMethod;

    this->setStackSize(stackSize);

    //TODO names

}

void XFThreadDefault::run()
{
   (_pEntryMethodProvider->*_entryMethod)( (const void*) nullptr );
}
