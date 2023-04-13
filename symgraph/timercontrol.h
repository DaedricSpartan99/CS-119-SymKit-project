#ifndef TIMERCONTROL_H
#define TIMERCONTROL_H

#include <QtPlugin>

class TimerControl
{
public:

    virtual ~TimerControl() {}

    virtual QObject * getQObject() = 0;

signals:

    virtual void canStart() = 0;
};

Q_DECLARE_INTERFACE(TimerControl, "TimerControl")

#endif // TIMERCONTROL_H
