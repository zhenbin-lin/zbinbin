#ifndef __ZBINBIN_BUFFER_H_
#define __ZBINBIN_BUFFER_H_
#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>



namespace zbinbin
{
class TcpConnection;

class Buffer
{
public:
    static const size_t kCheapPrepend = 8;
    static const size_t kInitialSize = 1024;

    Buffer(size_t initialSize = kInitialSize)
        : buffer_(kCheapPrepend + initialSize)
        , readerIndex_(kCheapPrepend)
        , writerIndex_(kInitialSize)
    {   
    }

    ~Buffer() = default;

    void swap(Buffer& rhs)
    {
        buffer_.swap(rhs.buffer_);
        std::swap(readerIndex_, rhs.readerIndex_);
        std::swap(writerIndex_, rhs.writerIndex_);
    }

    size_t readableBytes() const 
    {
        return writerIndex_ - readerIndex_;
    }

    size_t writableBytes() const
    {
        return buffer_.size() - writerIndex_;
    }

    size_t prependableBytes() const
    {
        return readerIndex_;
    }

    void append(const char* data, size_t len)
    {
        ensureWritableBytes(len);
        std::copy(data, data + len, begin() + writerIndex_);
        writerIndex_ += len;
    }

    void append(const void* data, size_t len)
    {
        append(static_cast<const char*>(data), len);
    }

    std::string retrieveAsString(size_t len) const
    {
        assert(len <= readableBytes());
        std::string result(peek(), len);
        retrieve(len);
        return result;
    }

    std::string retrieveAllAsString() const
    {
        return retrieveAsString(readableBytes());
    }

    const char* peek() const
    { return begin() + readerIndex_; }

    void ensureWritableBytes(size_t len)
    {
        if (writableBytes() < len)
        {
            makeSpace(len);
        }
        assert(writableBytes() >= len);
    }

    ssize_t readFd(int fd, int* savedErrno);

private:
    friend class TcpConnection;

    char* begin()
    { return buffer_.data(); }

    const char* begin() const
    { return buffer_.data(); }

    void retrieve(size_t len) const
    {
        assert(len <= readableBytes());
        if (len < readableBytes())
        {
            readerIndex_ += len;
        }
        else
        {
            retrieveAll();
        }
    }

    void retrieveAll() const
    {
        readerIndex_ = kCheapPrepend;
        writerIndex_ = kCheapPrepend;
    }

    void makeSpace(size_t len)
    {
        if (writableBytes() + prependableBytes() < len + kCheapPrepend)
        {
            buffer_.resize(writerIndex_ + len); // 空间不够了，需要扩容
        }
        else
        {
            // prependableBytes - kCheapPrepend的空间足够容纳数据
            // 将readerIndex_ ~ writerIndex_中的数据往前挪
            size_t readable = readableBytes();
            std::copy(begin() + readerIndex_,
                      begin() + writerIndex_,
                      begin() + kCheapPrepend);
            readerIndex_ = kCheapPrepend;
            writerIndex_ = readerIndex_ + readable;
            assert(readable == readableBytes());
        }
    }

    std::vector<char> buffer_;
    mutable size_t readerIndex_;
    mutable size_t writerIndex_;
};


}   // namespace zbinbin

#endif  // __ZBINBIN_BUFFER_H_