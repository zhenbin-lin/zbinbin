

namespace zbinbin
{
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


}