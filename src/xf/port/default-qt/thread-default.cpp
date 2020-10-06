#include <config/xf-config.h>

#if (USE_XF_THREAD_DEFAULT_QT_IMPLEMENTATION != 0)

#include <cassert>
#include <string.h>
#include "thread-default.h"

#if !defined(XFTHREAD_DEFAULT_STACK_SIZE)
    #define XFTHREAD_DEFAULT_STACK_SIZE	256
#endif




void XFThreadDefault::start()
{
    this->QThread::start();
}

void XFThreadDefault::stop()
{
    this->QThread::terminate();
}

void XFThreadDefault::setPriority(XFThreadPriority priority)
{

    switch (priority) {
        case XF_THREAD_PRIO_HIGH:
            this->QThread::setPriority(QThread::HighPriority);
            break;
        case XF_THREAD_PRIO_MAX:
            this->QThread::setPriority(QThread::HighestPriority);
            break;
        case XF_THREAD_PRIO_NORMAL:
            this->QThread::setPriority(QThread::NormalPriority);
            break;
        case XF_THREAD_PRIO_LOW:
            this->QThread::setPriority(QThread::LowPriority);
            break;
        case XF_THREAD_PRIO_UNKNOWN:
            this->QThread::setPriority(QThread::InheritPriority);
            break;
    }
}

XFThreadPriority XFThreadDefault::getPriority() const
{
    switch(this->priority()){
        case QThread::HighestPriority:
            return XF_THREAD_PRIO_MAX;

        case QThread::HighPriority:
            return XF_THREAD_PRIO_HIGH;

        case QThread::NormalPriority:
            return XF_THREAD_PRIO_NORMAL;

        case QThread::LowPriority:
            return XF_THREAD_PRIO_LOW;

        default:
            return XF_THREAD_PRIO_UNKNOWN;
    }



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

    this->setObjectName(threadName);
}

void XFThreadDefault::run()
{
   (_pEntryMethodProvider->*_entryMethod)( (const void*) nullptr );
}
#endif // USE_XF_THREAD_DEFAULT_QT_IMPLEMENTATION
