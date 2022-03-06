#include "zbinbin/net/Buffer.h"
#include "zbinbin/net/SocketOps.h"

#include <errno.h>
#include <sys/uio.h>
#include <sys/stat.h>


namespace zbinbin
{

ssize_t Buffer::readFd(int fd, int* savedErrno)
{
    char extraBuf[65536];
    struct iovec vec[2];
    const size_t writable = writableBytes();
    vec[0].iov_base = begin() + writerIndex_;
    vec[0].iov_len = writable;
    vec[1].iov_base = extraBuf;
    vec[1].iov_len = sizeof extraBuf;
    const int iovcnt = (writable < sizeof extraBuf) ? 2 : 1;
    const ssize_t n = sockets::readv(fd, vec, iovcnt);
    if (n < 0)
    {
        *savedErrno = errno;
    }
    else if (static_cast<size_t>(n) <= writable)
    {
        writerIndex_ += n;
    }
    else 
    {
        writerIndex_ = buffer_.size();
        append(extraBuf, n - writable);       
    }
    return n;
}

ssize_t Buffer::readFile(const char* fileName, int* savedErrno)
{
    // static const size_t bufferSize = 1024 * 256;
    size_t n = 0;
    FILE *fp = ::fopen(fileName, "rb");
    struct stat fileStat;  
    stat(fileName, &fileStat);
    size_t size = static_cast<size_t>(fileStat.st_size);
    if (fp) 
    {
        size_t nread = 0;
        ensureWritableBytes(size);
        while((nread = ::fread(begin() + writerIndex_, 1, size, fp)) > 0)
        {
            writerIndex_ += nread;
            n += nread;
            size -= nread;
        }
    } else {
        *savedErrno = errno;
    }
    return n;
}

}   // namespace zbinbin

