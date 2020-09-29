#include <config/xf-config.h>
#include "xf/interface/timeoutmanager.h"

#if (USE_XF_PORT_FUNCTIONS_DEFAULT_QT_IMPLEMENTATION != 0)

#include <QObject>
#include <QTimerEvent>
#include "port-functions.h"



#include <QDebug>

static class TimeoutManagerTimer : public QObject
{
public:
    TimeoutManagerTimer()
    : _timerId(0)
    {
    }

    void start(int32_t tickInterval)
    {
        Q_ASSERT(_timerId == 0);	// Method should be called only once!
        _timerId = startTimer(tickInterval, Qt::PreciseTimer);
    }

    void timerEvent(QTimerEvent * event) override
    {
        if (event->timerId() == _timerId)
        {
            XF_tick();
        }
    }

protected:
    int32_t _timerId;
} timeoutManagerTimer;

uint32_t TICKINTERVAL;


void XF_startTimeoutManagerTimer(uint32_t tickInterval){
    static TimeoutManagerTimer t;
    t.start(tickInterval);
    TICKINTERVAL = tickInterval;
}




int32_t XF_tickIntervalInMilliseconds()
{
    return TICKINTERVAL;
}


void XF_tick()
{
    interface::XFTimeoutManager::getInstance()->tick();
}

#endif // USE_XF_PORT_FUNCTIONS_DEFAULT_QT_IMPLEMENTATION
