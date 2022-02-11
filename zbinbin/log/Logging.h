#ifndef __ZBINBIN_LOGGING_H_
#define __ZBINBIN_LOGGING_H_

#include "zbinbin/log/LogStream.h"
#include "zbinbin/utility/Timestamp.h"


namespace zbinbin {


class LogEvent;


class Logger
{
public:
    enum LogLevel
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
        NUM_LOG_LEVELS,
    };

    // 将__FILE__中的文件名提取出来
    // 实现了编译时就可以获取文件名
    class SourceFile
    {
    public:
        template<int N>
        SourceFile(const char (&arr)[N]) : data_(arr), size_(N - 1)
        {
            const char* slash = strrchr(data_, '/');
            if (slash) {
                data_ = slash + 1;
                size_ -= static_cast<int>(data_ - arr);
            }
        }
        explicit SourceFile(const char* filename)
        : data_(filename)
        {
            const char* slash = strrchr(filename, '/');
            if (slash)
            {
                data_ = slash + 1;
            }
            size_ = static_cast<int>(strlen(data_));
        }
        const char* data_;
        int size_;
    };


    typedef void (*OutputFunc)(const char* msg, size_t len);
    typedef void (*FlushFunc)();
    static void setOutput(OutputFunc);
    static void setFlush(FlushFunc);

    LogStream& stream() { return impl_.stream_; }


    static LogLevel logLevel();
    static void setLogLevel(LogLevel level);

    Logger(SourceFile file, int line);
    Logger(SourceFile file, int line, LogLevel level);
    Logger(SourceFile file, int line, LogLevel level, const char* func);
    Logger(SourceFile file, int line, bool toAbort);
    ~Logger();
private:
    class Impl
    {
    public:
        typedef Logger::LogLevel LogLevel;

        Impl(LogLevel, int old_errno, const SourceFile& file, int line);
        void formatTime();
        void finish();

        Timestamp time_;
        LogStream stream_;
        LogLevel level_;
        int line_;
        SourceFile basename_;
    };

    Impl impl_;

};

extern Logger::LogLevel g_logLevel;

inline Logger::LogLevel Logger::logLevel()
{
    return g_logLevel;
}


// if (zbinbin::LogLevel::logLevel() <= zbinbin::LogLevel::TRACE)

#define LOG_TRACE if (zbinbin::Logger::logLevel() <= zbinbin::Logger::TRACE) \
    zbinbin::Logger(__FILE__, __LINE__, zbinbin::Logger::TRACE, __FUNCTION__).stream()

#define LOG_DEBUG if (zbinbin::Logger::logLevel() <= zbinbin::Logger::DEBUG) \
    zbinbin::Logger(__FILE__, __LINE__, zbinbin::Logger::DEBUG, __FUNCTION__).stream()

#define LOG_INFO if (zbinbin::Logger::logLevel() <= zbinbin::Logger::INFO) \
    zbinbin::Logger(__FILE__, __LINE__, zbinbin::Logger::INFO).stream()
#define LOG_WARN zbinbin::Logger(__FILE__, __LINE__, zbinbin::Logger::WARN).stream()
#define LOG_ERROR zbinbin::Logger(__FILE__, __LINE__, zbinbin::Logger::ERROR).stream()
#define LOG_FATAL zbinbin::Logger(__FILE__, __LINE__, zbinbin::Logger::FATAL).stream()

#define LOG_SYSERR zbinbin::Logger(__FILE__, __LINE__, false).stream()
#define LOG_SYSFATAL zbinbin::Logger(__FILE__, __LINE__, true).stream()


}   // namespace zbinbin
#endif	// __ZBINBIN_LOGGING_H_
