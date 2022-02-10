#include "zbinbin/log/Logging.h"
#include "zbinbin/log/LogFormatter.h"
#include <iostream>

namespace zbinbin{

using LogFormatterPtr = zbinbin::LogFormatter::ptr;

namespace 
{
LogFormatterPtr g_Formatter;
const char* g_pattern = "%d{%Y-%m-%d %H:%M:%S}  %t  [%p]  %f:%l  %m %n";

std::shared_ptr<LogFormatter> getDefaultFormatter() {
    if (!g_Formatter) {
        g_Formatter.reset(new LogFormatter(g_pattern));
    }
    return g_Formatter;
}

}

Logger::Logger(LogEvent::ptr event)
    : m_event(event)
{
}

Logger::~Logger()
{
    LogFormatterPtr formatter = getDefaultFormatter();
    std::cout << formatter->format(m_event);
    if (m_event->getLevel() >= LogLevel::Level::FATAL) {
        ::abort();
    }
}


}