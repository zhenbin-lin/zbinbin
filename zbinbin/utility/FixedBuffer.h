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
    FixedBuffer() : capacity_(SIZE) { curIdx_ = buffer_; }
    ~FixedBuffer() = default;

    ///
    /// 往缓冲区中添加数据
    ///
    bool append(const char* buf, size_t len) {
        if (len + length() <= capacity_) {
            memcpy(curIdx_ , buf, len);
            curIdx_ += len;
            return true;
        }
        return false;
    }

    ///
    /// 获取Buffer中的数据长度
    /// 
    size_t length() { return static_cast<size_t>(curIdx_ - buffer_); }
    size_t size() { return length(); }

    ///
    /// 剩余的空间大小
    /// 
    size_t avail() const { return end() - curIdx_; }

    ///
    /// 返回指向最后一个有效字符的指针
    /// 
    const char* back() { return curIdx_; }

    ///
    /// 指向最后一个字符的下一个
    /// 
    const char* end() const { return buffer_ + capacity_; }

    /// 
    /// 返回输入位置指针
    /// 
    char* tell() { return curIdx_; }

    ///
    /// 
    ///
    void add(size_t s) { curIdx_ += s; }

    ///
    /// 将缓冲区清空
    ///
    void clear() {
        bzero(static_cast<void*>(buffer_), sizeof(buffer_));
    }

    /// 
    /// 重置curIdx
    ///
    void reset() { curIdx_ = buffer_; }

    ///
    /// 将Buffer转成string
    /// 
    std::string toString() { return std::string(buffer_, size()); }
    const std::string toString() const { return std::string(buffer_, size()); }



private:
    size_t capacity_;
    char buffer_[SIZE];
    char* curIdx_;
};

}



#endif  // __ZBINBIN_FIXEDBUFFER_H_