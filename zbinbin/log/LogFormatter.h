#ifndef __ZBINBIN_LOGFORMATTER_H_
#define __ZBINBIN_LOGFORMATTER_H_
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <time.h>

namespace zbinbin{

class LogEvent;
// 日志级别
using LogEventPtr = std::shared_ptr<LogEvent>;


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
	LogEvent(const char *file, const char* func, int32_t m_line, LogLevel::Level level, uint32_t elapse, 
            uint32_t thread_id, uint32_t fiber_id, uint64_t time);

	const char* getFile() const { return m_file; }
	const char* getFunc() const { return m_func; }
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
	const char* m_func = 0;				// 函数名
	int32_t m_line = 0;					// 行号
	LogLevel::Level m_level;			// 事件级别
	uint32_t m_elapse = 0;				// 程序启动开始到现在的毫秒数
	uint32_t m_threadId = 0;			// 线程Id
	uint32_t m_fiberId = 0;				// 协程ID
	time_t m_time = 0;					// 时间戳
	std::stringstream m_ss;
};

// 日志格式器
class LogFormatter
{
public:
	using ptr = std::shared_ptr<LogFormatter>;
	LogFormatter(const std::string& pattern);


	const std::string format(LogEventPtr event);
public:
	class FormatItem {
	public:
		using ptr = std::shared_ptr<FormatItem>;
		FormatItem(const std::string& fmt = "") {};
		virtual ~FormatItem() {}
		virtual void format(std::ostream& os, LogEventPtr event) = 0;
	};

private:

	void init();
	
	std::string m_pattern;
	std::vector<FormatItem::ptr> m_items;

};
using FormatItemPtr = std::shared_ptr<LogFormatter::FormatItem>;

// 消息内容
class MessageFormatItem : public LogFormatter::FormatItem {
public:
	MessageFormatItem(const std::string& fmt = "") : FormatItem(fmt) {}
	void format(std::ostream& os, LogEventPtr event) override {
		os << event->getContent();
	}
};

// 事件的日志级别
class LevelFormatrItem : public LogFormatter::FormatItem { 
public:
	LevelFormatrItem(const std::string& fmt = "") : FormatItem(fmt) {}

	void format(std::ostream& os, LogEventPtr event) override {
		os << LogLevel::ToString(event->getLevel());
	}
};

// 从程序运行到当前的时间
class ElapseFormatItem : public LogFormatter::FormatItem { 
public:
	ElapseFormatItem(const std::string& fmt = "") : FormatItem(fmt) {}


	void format(std::ostream& os, LogEventPtr event) override {
		os << event->getElapse();
	}
};

// 日志文件名
class FileNameFormatItem : public LogFormatter::FormatItem { 
public:
	FileNameFormatItem(const std::string& fmt = "") : FormatItem(fmt) {}

	void format(std::ostream& os, LogEventPtr event) override {
		os << event->getFile();
	}
};

// 日志事件发生所在的函数
class FuncNameFormatItem : public LogFormatter::FormatItem { 
public:
	FuncNameFormatItem(const std::string& fmt = "") : FormatItem(fmt) {}

	void format(std::ostream& os, LogEventPtr event) override {
        if (event->getFunc() != NULL)
            os << event->getFunc();
	}
};

// 格式中的字符串
class StringFormatItem : public LogFormatter::FormatItem { 
public:
	StringFormatItem(const std::string& str) 
		: FormatItem(str), m_string(str) {}
	void format(std::ostream& os, LogEventPtr event) override {
		os << m_string;
	}
private:
	std::string m_string;
};


class ThreadIdFormatItem : public LogFormatter::FormatItem { 
public:
	ThreadIdFormatItem(const std::string& fmt = "") : FormatItem(fmt) {}

	void format(std::ostream& os, LogEventPtr event) override {
		os << event->getThreadId();
	}
};


class FiberIdFormatItem : public LogFormatter::FormatItem { 
public:
	FiberIdFormatItem(const std::string& fmt = "") : FormatItem(fmt) {}

	void format(std::ostream& os, LogEventPtr event) override {
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

	void format(std::ostream& os, LogEventPtr event) override {
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

	void format(std::ostream& os, LogEventPtr event) override {
		os << event->getLine();
	}
};

class NewLineFormatItem : public LogFormatter::FormatItem {
public:
	NewLineFormatItem(const std::string& fmt = "") : FormatItem(fmt) {}

	void format(std::ostream& os, LogEventPtr event) override {
		os << "\n";
	}
};

}

#endif  // __ZBINBIN_LOGFORMATTER_H_