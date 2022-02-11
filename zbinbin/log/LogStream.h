#ifndef __ZBINBIN_LOGSTREAM_H_
#define __ZBINBIN_LOGSTREAM_H_
#include "zbinbin/utility/noncopyable.h"
#include "zbinbin/log/FixedBuffer.h"
#include <string>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

namespace zbinbin 
{




class LogStream : noncopyable
{
public:
    using Buffer = FixedBuffer<kSmallBuffer>;

    LogStream& operator<<(bool v)
    {
        buffer_.append(v ? "1" : "0", 1);
        return *this;
    }
    LogStream& operator<<(char v)
    {
        buffer_.append(&v, 1);
        return *this;
    }
    LogStream& operator<<(short);
    LogStream& operator<<(unsigned short);
    LogStream& operator<<(int);
    LogStream& operator<<(unsigned int);
    LogStream& operator<<(long);
    LogStream& operator<<(unsigned long);
    LogStream& operator<<(long long);
    LogStream& operator<<(unsigned long long);
    LogStream& operator<<(float);
    LogStream& operator<<(double);

    LogStream& operator<<(const void*);
    LogStream& operator<<(const char*);
    LogStream& operator<<(const unsigned char*);
    LogStream& operator<<(const std::string&);
    // LogStream& operator<<(const StringPiece& v);
    // LogStream& operator<<(const Buffer& v);

    void append(const char* data, int len) { buffer_.append(data, len); }
    Buffer& buffer() { return buffer_; }
    void resetBuffer() { buffer_.reset(); }


private:

    template<typename T>
    void formatInteger(T v);


    Buffer buffer_;

    static const int kMaxNumericSize = 48;
};

class Fmt // : noncopyable
{
public:
    template<typename T>
    Fmt(const char* fmt, T val);

    const char* data() const { return buf_; }
    int length() const { return length_; }

private:
    char buf_[32];
    int length_;
};

inline LogStream& operator<<(LogStream& s, const Fmt& fmt)
{
    s.append(fmt.data(), fmt.length());
    return s;
}


}   // namespace zbinbin


#endif  // __ZBINBIN_LOGSTREAM_H_
