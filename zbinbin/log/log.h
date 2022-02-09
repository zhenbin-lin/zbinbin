#ifndef __ZBINBIN_LOG_H_
#define __ZBINBIN_LOG_H_

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
class Logger;

using LogEventPtr = std::shared_ptr<LogEvent>;
using LogFormatterPtr = std::shared_ptr<LogFormatter>;
using LogAppenderPtr = std::shared_ptr<LogAppender>;
using LoggerPtr = std::shared_ptr<Logger>;


// 日志级别
struct LogLevel 
{
public:
	enum Level {
		UNKNOW = 0,
		DEBUG = 1,
		INFO = 2,
		WARN = 3,
		ERROR = 4,
		FATAL = 5
	};

	static const char* ToString(LogLevel::Level level);
};

// 日志事件
class LogEvent {
public:
	using ptr = std::shared_ptr<LogEvent>;
	LogEvent(const char *file, int32_t m_line, LogLevel::Level level, uint32_t elapse, uint32_t thread_id, uint32_t fiber_id, uint64_t time);

	const char* getFile() const { return m_file; }
	int32_t getLine() const { return m_line; }
	uint32_t getElapse() const { return m_elapse; }
	uint32_t getThreadId() const { return m_threadId; }
	uint32_t getFiberId() const { return m_fiberId; }
	uint64_t getTime() const { return m_time; }
	const std::string getContent() const { return m_ss.str(); }
	const LogLevel::Level getLevel() const { return m_level; }
	std::stringstream& getLogStream() { return m_ss; }
private:
	const char* m_file = nullptr;		// 文件名
	int32_t m_line = 0;					// 行号
	LogLevel::Level m_level;			// 事件级别
	uint32_t m_elapse = 0;				// 程序启动开始到现在的毫秒数
	uint32_t m_threadId = 0;			// 线程Id
	uint32_t m_fiberId = 0;				// 协程ID
	time_t m_time = 0;					// 时间戳
	std::stringstream m_ss;
};


class LogEventGurad {
public:
	LogEventGurad(LoggerPtr Logger, LogEventPtr event);
	~LogEventGurad();

	std::stringstream& stream() { return m_event->getLogStream(); }

private:
	LoggerPtr m_logger;
	LogEventPtr m_event;
};



// 日志格式器
class LogFormatter
{
public:
	using ptr = std::shared_ptr<LogFormatter>;
	LogFormatter(const std::string& pattern);


	const std::string format(LoggerPtr logger, const LogLevel::Level& level, LogEventPtr event);
public:
	class FormatItem{
	public:
		using ptr = std::shared_ptr<FormatItem>;
		FormatItem(const std::string& fmt = "") {};
		virtual ~FormatItem() {}
		virtual void format(std::ostream& os, LoggerPtr logger,
				const LogLevel::Level& level, LogEventPtr event) = 0;
	};

private:

	void init();
	
	std::string m_pattern;
	std::vector<FormatItem::ptr> m_items;

};
using FormatItemPtr = LogFormatter::FormatItem::ptr;


// 日志输出地
class LogAppender
{
public:
	using ptr = std::shared_ptr<LogAppender>;
	// LogAppender(LogLevel::Level level) : m_level(level) {}
	virtual ~LogAppender() {}

	virtual void log(LoggerPtr logger, LogLevel::Level level, LogEventPtr event) = 0;
	
	void setFormatter(LogFormatterPtr formatter) { m_formatter = formatter; }
	LogFormatterPtr getFormatter() const { return m_formatter; }

protected:
	LogLevel::Level m_level = LogLevel::Level::DEBUG;
	LogFormatterPtr m_formatter;
};


// 输出到控制台的Appender
class StdoutLogAppender : public LogAppender 
{
public:
	using ptr = std::shared_ptr<StdoutLogAppender>;

	StdoutLogAppender() = default;
	void log(LoggerPtr logger, LogLevel::Level level, LogEventPtr event) override;
};

// 输出到文件的Appender
class FileLogAppender : public LogAppender 
{
public:
	using ptr = std::shared_ptr<FileLogAppender>;
	
	FileLogAppender(const std::string& filename, LogLevel::Level level = LogLevel::Level::DEBUG);
	~FileLogAppender();

	void log(LoggerPtr logger, LogLevel::Level level, LogEventPtr event) override;

	/// 重新打开文件，文件打开成功返回true
	bool reopen();
private:
	std::string m_filename;
	std::ofstream m_filestream;
};

// 日志器
class Logger : public std::enable_shared_from_this<Logger> 
{
public:
	using ptr = std::shared_ptr<Logger>;

	Logger(const std::string& name = "root");
	void log(/* LogLevel::Level level, */ LogEvent::ptr event);

	// void debug(LogEvent::ptr event);
	// void info(LogEvent::ptr event);
	// void warn(LogEvent::ptr event);
	// void error(LogEvent::ptr event);
	// void fatal(LogEvent::ptr event);

	void addAppender(LogAppenderPtr appender);
	void delAppender(LogAppenderPtr appender);

	LogLevel::Level getLevel() const { return m_level; }
	void setLevel(LogLevel::Level level) { m_level = level; }

	const std::string& getName() const { return m_name; }

private:
	std::string m_name;						// 日志名称
	LogLevel::Level m_level;				// 日志级别
	std::list<LogAppenderPtr> m_appenders;	// 输出到目的地集合
	LogFormatterPtr m_formatter;
};




class MessageFormatItem : public LogFormatter::FormatItem {
public:
	MessageFormatItem(const std::string& fmt = "") : FormatItem(fmt) {}
	void format(std::ostream& os, LoggerPtr logger, const LogLevel::Level& level, LogEventPtr event) override {
		os << event->getContent();
	}
};

class LevelFormatrItem : public LogFormatter::FormatItem { 
public:
	LevelFormatrItem(const std::string& fmt = "") : FormatItem(fmt) {}

	void format(std::ostream& os, LoggerPtr logger, const LogLevel::Level& level, LogEventPtr event) override {
		os << LogLevel::ToString(level);
	}
};

class ElapseFormatItem : public LogFormatter::FormatItem { 
public:
	ElapseFormatItem(const std::string& fmt = "") : FormatItem(fmt) {}


	void format(std::ostream& os, LoggerPtr logger, const LogLevel::Level& level, LogEventPtr event) override {
		os << event->getElapse();
	}
};

class FileNameFormatItem : public LogFormatter::FormatItem { 
public:
	FileNameFormatItem(const std::string& fmt = "") : FormatItem(fmt) {}

	void format(std::ostream& os, LoggerPtr logger, const LogLevel::Level& level,  LogEventPtr event) override {
		os << event->getFile();
	}
};

class NameFormatItem : public LogFormatter::FormatItem { 
public:
	NameFormatItem(const std::string& fmt = "") : FormatItem(fmt) {}

	void format(std::ostream& os, LoggerPtr logger, const LogLevel::Level& level, LogEventPtr event) override {
		os << logger->getName();
	}
};

class StringFormatItem : public LogFormatter::FormatItem { 
public:
	StringFormatItem(const std::string& str) 
		: FormatItem(str), m_string(str) {}
	void format(std::ostream& os, LoggerPtr logger, const LogLevel::Level& level, LogEventPtr event) override {
		os << m_string;
	}
private:
	std::string m_string;
};

class ThreadIdFormatItem : public LogFormatter::FormatItem { 
public:
	ThreadIdFormatItem(const std::string& fmt = "") : FormatItem(fmt) {}

	void format(std::ostream& os, LoggerPtr logger, const LogLevel::Level& level, LogEventPtr event) override {
		os << event->getThreadId();
	}
};


class FiberIdFormatItem : public LogFormatter::FormatItem { 
public:
	FiberIdFormatItem(const std::string& fmt = "") : FormatItem(fmt) {}

	void format(std::ostream& os, LoggerPtr logger, const LogLevel::Level& level, LogEventPtr event) override {
		os << event->getFiberId();
	}
};

class DateTimeFormatItem : public LogFormatter::FormatItem { 
public:
	DateTimeFormatItem(const std::string& format = "%Y-%m-%d %H:%M:%S") 
		: m_format(format) {
			if (m_format.empty()) {
				m_format = "%Y-%m-%d %H:%M:%S";
			}
	}

	void format(std::ostream& os, LoggerPtr logger, const LogLevel::Level& level, LogEventPtr event) override {
		struct tm tm;
		time_t time = event->getTime();
		::localtime_r(&time, &tm);
		char buf[64];
		::strftime(buf, sizeof(buf), m_format.c_str(), &tm);
		os << std::string(buf);
	}
private:
	std::string m_format;
};

class LineFormatItem : public LogFormatter::FormatItem {
public:
	LineFormatItem(const std::string& fmt = "") : FormatItem(fmt) {}

	void format(std::ostream& os, LoggerPtr logger, const LogLevel::Level& level, LogEventPtr event) override {
		os << event->getLine();
	}
};

class NewLineFormatItem : public LogFormatter::FormatItem {
public:
	NewLineFormatItem(const std::string& fmt = "") : FormatItem(fmt) {}

	void format(std::ostream& os, LoggerPtr logger, const LogLevel::Level& level, LogEventPtr event) override {
		os << "\n";
	}
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


#define ZBINBIN_LOG_LEVEL(logger, level)	\
	if (logger->getLevel() <= level) 		\
		LogEventGurad(logger, LogEventPtr(new LogEvent(__FILE__, __LINE__, level, 0, CurrentThread::tid(), 0, time(0)))).stream()

#define LOG_RESIGTER_APPENDER(appender)		\
	logger->addAppender(LogAppender::ptr(new appender));



#define LOG_DEBUG(logger) ZBINBIN_LOG_LEVEL(logger, LogLevel::Level::DEBUG)
#define LOG_INFO(logger) ZBINBIN_LOG_LEVEL(logger, LogLevel::Level::INFO)
#define LOG_WARN(logger) ZBINBIN_LOG_LEVEL(logger, LogLevel::Level::WARN)
#define LOG_ERROR(logger) ZBINBIN_LOG_LEVEL(logger, LogLevel::Level::ERROR)
#define LOG_FATAL(logger) ZBINBIN_LOG_LEVEL(logger, LogLevel::Level::FATAL)


}


#endif	// __zbinbin_LOG_H_
