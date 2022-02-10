#ifndef __ZBINBIN_LOGGING_H_
#define __ZBINBIN_LOGGING_H_


#include "zbinbin/log/LogFormatter.h"
#include <functional>
#include <sstream>
#include <string>
#include <memory>


namespace zbinbin {


class LogEvent;


class Logger
{
public:
    Logger(LogEvent::ptr event);
    std::stringstream& stream() { return m_event->getLogStream(); }

    ~Logger();
private:
    LogEvent::ptr m_event;
};

using LoggerPtr = std::shared_ptr<Logger>;
}   // namespace zbinbin


#define LOG_DEBUG \
    zbinbin::Logger(zbinbin::LogEvent::ptr(new \
        zbinbin::LogEvent(__FILE__, __FUNCTION__, __LINE__, LogLevel::Level::DEBUG, 0, CurrentThread::tid(), 0, time(0)))).stream()

#define LOG_INFO \
    zbinbin::Logger(zbinbin::LogEvent::ptr(new \
        zbinbin::LogEvent(__FILE__, __FUNCTION__, __LINE__, LogLevel::Level::INFO, 0, CurrentThread::tid(), 0, time(0)))).stream()
#define LOG_WARN \
    zbinbin::Logger(zbinbin::LogEvent::ptr(new \
        zbinbin::LogEvent(__FILE__, NULL, __LINE__, LogLevel::Level::WARN, 0, CurrentThread::tid(), 0, time(0)))).stream()
#define LOG_ERROR \
    zbinbin::Logger(zbinbin::LogEvent::ptr(new \
        zbinbin::LogEvent(__FILE__, NULL, __LINE__, LogLevel::Level::ERROR, 0, CurrentThread::tid(), 0, time(0)))).stream()
#define LOG_FATAL \
    zbinbin::Logger(zbinbin::LogEvent::ptr(new \
        zbinbin::LogEvent(__FILE__, NULL, __LINE__, LogLevel::Level::FATAL, 0, CurrentThread::tid(), 0, time(0)))).stream()

#endif	// __ZBINBIN_LOGGING_H_
