#ifndef __ZBINBIN_FIXEDBUFFER_H_
#define __ZBINBIN_FIXEDBUFFER_H_

#include "zbinbin/utility/noncopyable.h"
#include <sstream>
#include <cstring>

namespace zbinbin {

const int kSmallBuffer = 4000;
const int kLargeBuffer = 4000 * 1000;

template<int SIZE>
class FixedBuffer : noncopyable
{

public:
    FixedBuffer() 
    { 
        cur_ = data_; 
    }
    ~FixedBuffer() = default;

    ///
    /// 往缓冲区中添加数据
    ///
    bool append(const char* buf, size_t len) {
        if (len < avail()) {
            memcpy(cur_ , buf, len);
            cur_ += len;
            return true;
        }
        return false;
    }

    const char* data() { return data_; }

    ///
    /// 获取Buffer中的数据长度
    /// 
    size_t length() { return static_cast<size_t>(cur_ - data_); }
    size_t size() { return length(); }

    ///
    /// 剩余的空间大小
    /// 
    size_t avail() { return end() - cur_; }

    ///
    /// 返回指向最后一个有效字符的指针
    /// 
    const char* back() { return cur_; }

    /// 
    /// 返回输入位置指针
    /// 
    char* tell() { return cur_; }

    ///
    /// 
    ///
    void add(size_t s) { cur_ += s; }

    ///
    /// 将缓冲区清空
    ///
    void clear() {
        bzero(static_cast<void*>(data_), sizeof(data_));
    }

    /// 
    /// 重置cur
    ///
    void reset() { cur_ = data_; }

    ///
    /// 将Buffer转成string
    /// 
    std::string toString() { return std::string(data_, size()); }
    const std::string toString() const { return std::string(data_, size()); }



private:
    const char* end() const { return data_ + sizeof data_; }


    char data_[SIZE];
    char* cur_;
};

}



#endif  // __ZBINBIN_FIXEDBUFFER_H_