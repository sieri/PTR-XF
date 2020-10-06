#include "config/trace-config.h"

#if (USE_PLATFORM_QT_TRACE != 0)

#include <QDebug>
#include <QTime>
#include "trace/trace.h"

#define ADD_CRLF_SEQU 	1

//static
void Trace::initialize()
{

}

void Trace::out(string str)
{
    QTime t = QTime::currentTime();
    QString s = t.toString("HH:mm:ss.zzz");
    qDebug() << s << str.c_str() ;
}

void Trace::out(const char * format, ...)
{
    QTime t = QTime::currentTime();
    QString s = t.toString("HH:mm:ss.zzz");

    char str[255];

    va_list args;

    va_start(args, format);
    vsprintf(str, format, args);
    va_end(args);

    qDebug() << s << "--->" << str;
}

#endif // USE_PLATFORM_QT_TRACE
