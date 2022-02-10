#include "zbinbin/log/AsyncLogging.h"
#include "zbinbin/thread/Mutex.h"
#include <map>
#include <tuple>
#include <iostream>
#include <string>


namespace zbinbin{

///
/// LogLevel
///
const char*	LogLevel::ToString(LogLevel::Level level) {
	switch(level) {
#define XX(name) \
		case LogLevel::name: \
			return #name; \
			break;
		XX(DEBUG);
		XX(INFO);
		XX(WARN);
		XX(ERROR);
		XX(FATAL);
#undef XX
		default:
			return "UNKNOW";
	}
	return "UNKNOW";
}

///
/// LogEvent
/// 
LogEvent::LogEvent(const char *file, 
				   const char *func, 
				   int32_t line, 
				   LogLevel::Level leve, 
				   uint32_t elapse, 
				   uint32_t thread_id, 
				   uint32_t fiber_id, 
				   uint64_t time)
		: m_file(file)
        , m_func(func)
		, m_line(line)
		, m_level(leve)
		, m_elapse(elapse)
		, m_threadId(thread_id)
		, m_fiberId(fiber_id)
		, m_time(time) {

}

///
/// LogEventGurad
///
LogEventGurad::LogEventGurad(LoggerPtr logger, LogEventPtr event) 
	: m_logger(logger)
	, m_event(event) 
{
}

LogEventGurad::~LogEventGurad() 
{
	m_logger->log(m_event);
}



AsyncLogger::AsyncLogger(const std::string& name, LogLevel::Level level)
	: m_name(name)
	, m_level(level) 
{
}


void AsyncLogger::addAppender(LogAppenderPtr appender) {
	if (!appender->getFormatter()) {
		appender->setFormatter(m_formatter);
	}
	m_appenders.push_back(appender);
}

void AsyncLogger::delAppender(LogAppenderPtr appender) {
	for (auto it = m_appenders.begin();
			it != m_appenders.end(); ++it) {
		if (*it == appender) {
			m_appenders.erase(it);
			break;
		}
	}
}

void AsyncLogger::resetFormat(const std::string& fmt) {
    m_formatter.reset(new LogFormatter(fmt));
}


void AsyncLogger::log(LogEventPtr event) {
	if (m_level <= event->getLevel()) {
		auto self = shared_from_this();
		for (auto& i : m_appenders) {
    		i->log(self, event);
		}
	}
}


///
/// LogFormatter
///






/// 
/// StdoutLogAppender
///
void StdoutLogAppender::append(const std::string& message) {
    std::cout << message;
}

///
/// FileLogAppender
///
FileLogAppender::FileLogAppender(const std::string& filename, LogLevel::Level level)
    : LogAppender(level)
	, m_filename(filename)
{
    m_filestream.open(filename);
    if (!m_filestream) {
        // TODO 完善try catch
        ::abort();
    }
}

FileLogAppender::~FileLogAppender() {
	m_filestream.close();
}

void FileLogAppender::append(const std::string& message) {
    m_filestream << message;
}

bool FileLogAppender::reopen() {
	if (m_filestream) {
		m_filestream.close();
	}
	m_filestream.open(m_filename);
	return !!m_filestream;
}


}   // namespace zbinbin
