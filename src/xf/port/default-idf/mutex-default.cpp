#include <config/xf-config.h>

#if (USE_XF_MUTEX_DEFAULT_IDF_IMPLEMENTATION != 0)

#include "critical/critical.h"	// Provided by the platform used
#include "mutex-default.h"

//implement create for the mutex implementation used
interface::XFMutex* interface::XFMutex::create()
{
	return new XFMutexDefault();
}

XFMutexDefault::XFMutexDefault()
{

}

XFMutexDefault::~XFMutexDefault()
{

}

void XFMutexDefault::lock()
{
	enterCritical();
}

void XFMutexDefault::unlock()
{
	exitCritical();
}

bool XFMutexDefault::tryLock(int32_t timeout)
{
	//always can lock in a single threaded, OS less embedded system
	enterCritical();

	return true;

}


#endif // USE_XF_MUTEX_DEFAULT_IDF_IMPLEMENTATION
