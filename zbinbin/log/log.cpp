#include "log.h"
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
				   int32_t line, 
				   LogLevel::Level leve, 
				   uint32_t elapse, 
				   uint32_t thread_id, 
				   uint32_t fiber_id, 
				   uint64_t time)
		: m_file(file)
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
	m_logger->log(/* m_event->getLevel(),  */m_event);
}



Logger::Logger(const std::string& name)
	: m_name(name)
	, m_level(LogLevel::Level::DEBUG) {
	m_formatter.reset(new LogFormatter("%d{%Y-%m-%d %H:%M:%S}  %t  [%p]  [%c]  %f:%l    %m %n"));

}


void Logger::addAppender(LogAppenderPtr appender) {
	if (!appender->getFormatter()) {
		appender->setFormatter(m_formatter);
	}
	m_appenders.push_back(appender);
}
void Logger::delAppender(LogAppenderPtr appender) {
	for (auto it = m_appenders.begin();
			it != m_appenders.end(); ++it) {
		if (*it == appender) {
			m_appenders.erase(it);
			break;
		}
	}
}

void Logger::log(/* LogLevel::Level level, */ LogEventPtr event){
	// if (m_level <= level) {
	// 	auto self = shared_from_this();
	// 	for (auto& i : m_appenders) {
	// 		i->log(self, level, event);
	// 	}
	// }
	if (m_level <= event->getLevel()) {
		auto self = shared_from_this();
		for (auto& i : m_appenders) {
			i->log(self, event->getLevel(), event);
		}
	}
}

/* void Logger::debug(LogEventPtr event){
	log(LogLevel::DEBUG, event);
}

void Logger::info(LogEventPtr event){
	log(LogLevel::INFO, event);
}

void Logger::warn(LogEventPtr event){
	log(LogLevel::WARN, event);
}

void Logger::error(LogEventPtr event){
	log(LogLevel::ERROR, event);
}

void Logger::fatal(LogEventPtr event){
	log(LogLevel::FATAL, event);
} */

///
/// LogFormatter
///
LogFormatter::LogFormatter(const std::string& pattern) 
	: m_pattern(pattern) {
	
	init();
}

const std::string LogFormatter::format(LoggerPtr logger, const LogLevel::Level& level, LogEventPtr event) {
	std::stringstream ss;
	for (auto& i : m_items) {
		i->format(ss, logger, level, event);
	}
	return ss.str();
}


void LogFormatter::init() {
	std::vector<std::tuple<std::string, std::string, int> > vec;
	std::string nstr;	// 正常的字符串
	for (size_t i = 0; i < m_pattern.size(); ++i) {
		if (m_pattern[i] != '%') {
			nstr.append(1, m_pattern[i]);
			continue;
		}
		if ((i + 1 ) < m_pattern.size() && m_pattern[i + 1] == '%') {
			nstr.append(1, '%');
			continue;
		}
		size_t n = i + 1;
		int fmt_status = 0;
		size_t fmt_begin = 0;

		std::string str;  // 在%...{之间
		std::string fmt;  // {...}之间
		while (n < m_pattern.size()) {
			if (!fmt_status && (!::isalpha(m_pattern[n])) && m_pattern[n] != '{' && m_pattern[n] != '}') {
				str = m_pattern.substr(i + 1, n - i - 1);
				break;
			}
			if (fmt_status == 0) {
				if (m_pattern[n] == '{') {
					// i: %
					// i+1: first letter
					str = m_pattern.substr(i + 1, n - i - 1);
					fmt_status = 1; // 开始解析{...}
					fmt_begin = n;
					++n;
					continue;
				}
			}
			if (fmt_status == 1) {
				if (m_pattern[n] == '}') {
					// fmt_begin: {
					fmt = m_pattern.substr(fmt_begin + 1, n - fmt_begin - 1);
					fmt_status = 0;
					++n;
					break;
				}	
			}
			++n;
			if (n == m_pattern.size()) {
				if (str.empty()) {
					str = m_pattern.substr(i + 1);
				}
			}
		}

		// %xxx后没有{}
		// 正常字符串
		if (fmt_status == 0) {
			if (!nstr.empty()) {
				vec.push_back(std::make_tuple(nstr, "", 0));
				nstr.clear();
			}
			if (str.empty())
				str = m_pattern.substr(i + 1, n - i - 1);
			vec.push_back(std::make_tuple(str, fmt, 1));
			i = n - 1;
		} else if (fmt_status == 1) {
			// TODO error handle detail
			vec.push_back(std::make_tuple("<<pattern_error>>", fmt, 0));
		}
	}
	// 正常字符串
	if (!nstr.empty()) {
		vec.push_back(std::make_tuple(nstr, "", 0));
	}

	static std::map<std::string, std::function<FormatItemPtr(const std::string&)> > s_format_items = {
#define XX(str, C) \
		{#str, [](const std::string& fmt) { return FormatItemPtr(new C(fmt));}}
	
	// %m -- 消息体
	// %p -- level
	// %r -- 启动后的时间
	// %c -- 日志名称
	// %t -- thread id
	// %n -- 回车换行
	// %d -- 系统时间
	// %f -- 文件名
	// %l -- 行号
		XX(m, MessageFormatItem),
		XX(p, LevelFormatrItem),
		XX(r, ElapseFormatItem),
		XX(c, NameFormatItem),
		XX(t, ThreadIdFormatItem),
		XX(n, NewLineFormatItem),
		XX(d, DateTimeFormatItem),
		XX(f, FileNameFormatItem),
		XX(l, LineFormatItem),

#undef XX
	};
	
	for (auto& i : vec) {
		if (std::get<2>(i) == 0) {
			m_items.push_back(FormatItemPtr(new StringFormatItem(std::get<0>(i))));
		} else {
			auto it = s_format_items.find(std::get<0>(i));
			if (it == s_format_items.end()) {
				m_items.push_back(FormatItemPtr(new StringFormatItem("<<format_error %" + std::get<0>(i) + ">>")));
			} else {
				m_items.push_back(it->second(std::get<1>(i)));
			}
		}
		std::cout << "("<< std::get<0>(i) << ") - (" << std::get<1>(i) << ") - (" << std::get<2>(i) << ")" << std::endl;

	}

} 



/// 
/// StdoutLogAppender
///
void StdoutLogAppender::log(LoggerPtr logger, LogLevel::Level level, LogEventPtr event) {
	if (level >= m_level) {
		std::string str = m_formatter->format(logger, level, event);
		std::cout << str;
	}
}

///
/// FileLogAppender
///
FileLogAppender::FileLogAppender(const std::string& filename, LogLevel::Level level)
	: m_filename(filename) {
		m_filestream.open(filename);
		if (!m_filestream) {
			// TODO 完善try catch
			::abort();
		}
}

FileLogAppender::~FileLogAppender() {
	m_filestream.close();
}

void FileLogAppender::log(LoggerPtr logger, LogLevel::Level level, LogEventPtr event) {
	if (level >= m_level) {
		std::string str = m_formatter->format(logger, level, event);
		std::cout << str;
		m_filestream << str;
	}
}

bool FileLogAppender::reopen() {
	if (m_filestream) {
		m_filestream.close();
	}
	m_filestream.open(m_filename);
	return !!m_filestream;
}


LoggerManager::LoggerManager() {
	m_root.reset(new Logger);
	m_root->addAppender(LogAppenderPtr(new StdoutLogAppender));
}

LoggerPtr LoggerManager::getLogger(const std::string& name) {
	auto it = m_loggers.find(name);
	return it == m_loggers.end() ? m_root : it->second;
}

void LoggerManager::init() {

}



}
