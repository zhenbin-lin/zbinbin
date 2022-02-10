#ifndef __ZBINBIN_LOGSTREAM_H_
#define __ZBINBIN_LOGSTREAM_H_
#include "zbinbin/utility/noncopyable.h"
#include "zbinbin/utility/FixedBuffer.h"
#include <string>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

namespace zbinbin 
{




class LogStream : noncopyable
                  , std::enable_shared_from_this<LogStream>

{
private:


    template<typename T>
    void formatInteger(T v);

public:
    using Buffer = FixedBuffer<kSmallBuffer>;
    using BufferPtr = std::unique_ptr<Buffer>;

    LogStream(Buffer* buffer);
    LogStream(BufferPtr buffer);
    ~LogStream();


    LogStream& operator<<(bool v);
    LogStream& operator<<(char v);
    LogStream& operator<<(short);
    LogStream& operator<<(unsigned short);
    LogStream& operator<<(int);
    LogStream& operator<<(unsigned int);
    LogStream& operator<<(long);
    LogStream& operator<<(unsigned long);
    LogStream& operator<<(long long);
    LogStream& operator<<(unsigned long long);
    LogStream& operator<<(float v);
    LogStream& operator<<(double);

    LogStream& operator<<(const void*);
    LogStream& operator<<(const char* str);
    LogStream& operator<<(const unsigned char* str);
    LogStream& operator<<(const std::string& v);
    // LogStream& operator<<(const StringPiece& v);
    // LogStream& operator<<(const Buffer& v);

    ///
    /// 返回buffer指针，并释放LogStream对其的管理权
    ///
    BufferPtr getBufferPtr() { 
        return std::forward<BufferPtr>(buffer_); 
    } 

    ///
    /// 重置LogStream的Buffer
    ///
    void resetBuffer(BufferPtr buf) { 
        return buffer_.swap(buf); 
    } 

private:

    BufferPtr buffer_;


    static const int kMaxNumericSize = 48;
};

}   // namespace zbinbin


#endif  // __ZBINBIN_LOGSTREAM_H_
