#ifndef XF_EVENT_QUEUE_DEFAULT_QT_H
#define XF_EVENT_QUEUE_DEFAULT_QT_H

#include "config/xf-config.h"

#if (USE_XF_EVENT_QUEUE_DEFAULT_QT_IMPLEMENTATION != 0)

#include <stdint.h>
#include <QMutex>
#include <QWaitCondition>
#include <QQueue>
#include "xf/interface/eventqueue.h"

/** @ingroup port_default_qt
 *  @{
 */

/**
 * @brief Default Qt implementation for the XFEventQueue interface.
 */
class XFEventQueueDefault : public interface::XFEventQueue
{
public:
    XFEventQueueDefault();
    ~XFEventQueueDefault() override;

    // XFEventQueue interface implementation
public:
    bool empty() const override;                    ///< Returns true if no event is in the queue.
    bool push(const XFEvent * pEvent) override;     ///< Pushes the given event onto the queue. Returns false if the event could not be pushed.
    const XFEvent * front() override;               ///< Returns pointer to next event to pop.
    void pop() override;                            ///< Pops the next event from the queue.
    bool pend() override;                           ///< Wait for the next event to arrive. Returns true if an event is in the queue.

protected:
    typedef QQueue<const XFEvent *> EventQueue;     ///< Type of the event queue.

    QMutex _mutex;                                  ///< Mutex protecting access to _queue.
    QWaitCondition _newEvents;                      ///< Wait condition to let thread wait until a new event arrives.
    EventQueue _queue;                              ///< Internal queue holding the events.
};

/** @} */ // end of port_default_qt group
#endif // USE_XF_EVENT_QUEUE_DEFAULT_QT_IMPLEMENTATION
#endif // XF_EVENT_QUEUE_DEFAULT_QT_H
