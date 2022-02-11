#ifndef __ZBINBIN_LOGGING_H_
#define __ZBINBIN_LOGGING_H_


#include "zbinbin/utility/Singleton.h"
#include <list>
#include <functional>
#include <stdint.h>
#include <sstream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <assert.h>
#include <memory>


namespace zbinbin {

class LogEvent;
struct LogLevel;
class LogFormatter;
class LogAppender;
class AsyncLogger;

using LogEventPtr = std::shared_ptr<LogEvent>;
using LogFormatterPtr = std::shared_ptr<LogFormatter>;
using LogAppenderPtr = std::shared_ptr<LogAppender>;
using LoggerPtr = std::shared_ptr<AsyncLogger>;


// 日志输出地
class LogAppender
{
public:
	using ptr = std::shared_ptr<LogAppender>;
	LogAppender(LogLevel::Level level) : m_level(level) {}
	virtual ~LogAppender() {}

	virtual void log(LoggerPtr logger, LogEventPtr event) = 0;
	
	void setFormatter(LogFormatterPtr formatter) { m_formatter = formatter; }
	LogFormatterPtr getFormatter() const { return m_formatter; }

protected:
	LogLevel::Level m_level;
	LogFormatterPtr m_formatter;
};


// 输出到控制台的Appender
class StdoutLogAppender : public LogAppender 
{
public:
	using ptr = std::shared_ptr<StdoutLogAppender>;

	StdoutLogAppender(LogLevel::Level level) : LogAppender(level) {}
	void log(LoggerPtr logger, LogEventPtr event) override;
};

// 输出到文件的Appender
class FileLogAppender : public LogAppender 
{
public:
	using ptr = std::shared_ptr<FileLogAppender>;
	
	FileLogAppender(const std::string& filename, LogLevel::Level level = LogLevel::Level::DEBUG);
	~FileLogAppender();

	void log(LoggerPtr logger, LogEventPtr event) override;

	/// 重新打开文件，文件打开成功返回true
	bool reopen();
private:
	std::string m_filename;
	std::ofstream m_filestream;
};

// 日志器
class AsyncLogger : public std::enable_shared_from_this<AsyncLogger> 
{
public:
	using ptr = std::shared_ptr<AsyncLogger>;

	AsyncLogger(const std::string& name = "root", LogLevel::Level level = LogLevel::Level::DEBUG);

	void log(LogEvent::ptr event);

	void addAppender(LogAppenderPtr appender);
	void delAppender(LogAppenderPtr appender);
	LogAppenderPtr getAppender() { return appender; }

    LogLevel::Level getLevel() const { return m_level; }
	void setLevel(LogLevel::Level level) { m_level = level; }

	const std::string& getName() const { return m_name; }

private:
	std::string m_name;						// 日志名称
	LogLevel::Level m_level;				// 日志级别
	std::list<LogAppenderPtr> m_appenders;	// 输出到目的地集合
};







class LoggerManager {
public:
	LoggerManager();
	LoggerPtr getLogger(const std::string& name = "");

	void init();

private:
	std::map<std::string, LoggerPtr> m_loggers;
	LoggerPtr m_root;
};

extern zbinbin::AsyncLogger G_logger;

#define ZBINBIN_LOG_LEVEL(logger, level)	    \
	if (logger->getLevel() <= level) 		    \
		LogEventGurad(logger                    \
        , LogEventPtr(new LogEvent(__FILE__, __FUNCTION__, __LINE__, level, 0, CurrentThread::tid(), 0, time(0)))).stream()


#define LOG_DEBUG ZBINBIN_LOG_LEVEL(G_logger, LogLevel::Level::DEBUG)
#define LOG_INFO ZBINBIN_LOG_LEVEL(G_logger, LogLevel::Level::INFO)
#define LOG_WARN ZBINBIN_LOG_LEVEL(G_logger, LogLevel::Level::WARN)
#define LOG_ERROR ZBINBIN_LOG_LEVEL(G_logger, LogLevel::Level::ERROR)
#define LOG_FATAL ZBINBIN_LOG_LEVEL(G_logger, LogLevel::Level::FATAL)

}


#endif	// __ZBINBIN_LOGGING_H_
