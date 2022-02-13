#include "zbinbin/net/SocketOps.h"
#include "zbinbin/log/Logging.h"


#include <fcntl.h>
#include <stdio.h>  // snprintf
#include <sys/socket.h>
#include <sys/uio.h>  // readv
#include <unistd.h>
#include <assert.h>
#include <cstring>
#include <errno.h>


namespace zbinbin
{
namespace sockets
{

#if VALGRIND || defined (NO_ACCEPT4)
void setNonBlockAndCloseOnExec(int sockfd)
{
    // non-block
    int flags = ::fcntl(sockfd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    int ret = ::fcntl(sockfd, F_SETFL, flags);
    // FIXME check

    // close-on-exec
    flags = ::fcntl(sockfd, F_GETFD, 0);
    flags |= FD_CLOEXEC;
    ret = ::fcntl(sockfd, F_SETFD, flags);
    // FIXME check

    (void)ret;
}
#endif

int createNonblockingOrDie(sa_family_t family)
{
#if VALGRIND
    int sockfd = ::socket(family, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0)
    {
        LOG_SYSFATAL << "sockets::createNonblockingOrDie";
    }
    setNonBlockAndCloseOnExec(sockfd);
#else
    int sockfd = ::socket(family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if (sockfd < 0)
    {
        LOG_SYSFATAL << "sockets::createNonblockingOrDie";
    }
#endif
return sockfd;
}




int listen(int sockfd)
{
    int ret = ::listen(sockfd, SOMAXCONN);
    if (ret < 0)
    {
        LOG_SYSFATAL << "sockets::listen:" << strerror(errno);
    }
    return ret;
}


void bind(int sockfd, const struct sockaddr_in* addr)
{
    int ret = ::bind(sockfd, reinterpret_cast<const struct sockaddr*>(addr), static_cast<socklen_t>(sizeof(*addr)));
    if (ret < 0)
    {
        LOG_SYSFATAL << "sockets::bindOrDie:" << strerror(errno);
    }
}


int accept(int sockfd, struct sockaddr_in* addr)
{
    socklen_t addrlen = static_cast<socklen_t>(sizeof *addr);
    int connfd = ::accept4(sockfd, reinterpret_cast<struct sockaddr*>(addr), &addrlen, SOCK_NONBLOCK | SOCK_CLOEXEC);
    if (connfd < 0)
    {
        int savedErrno = errno;
        LOG_SYSERR << "Socket::accept:" << strerror(savedErrno);
        switch (connfd)
        {
            /* The socket is marked nonblocking and no connections are
                present to be accepted.  POSIX.1-2001 and POSIX.1-2008
                allow either error to be returned for this case, and do
                not require these constants to have the same value, so a
                portable application should check for both possibilities. */
            case EAGAIN: // EWOULDBLOCK
            //  A connection has been aborted.
            case ECONNABORTED:
            /* The system call was interrupted by a signal that was
                caught before a valid connection arrived; */
            case EINTR:  
            // Protocol error.
            case EPROTO: 
            // Firewall rules forbid connection
            case EPERM:
                // LOG_SYSERR << "Socket::accept:Firewall rules forbid connection.";
                errno = savedErrno;
                break;
            // sockfd is not an open file descriptor.
            case EBADF:  
            /* The addr argument is not in a writable part of the user
                address space. */
            case EFAULT: 
            /* Socket is not listening for connections, or addrlen is
                invalid (e.g., is negative). */
            case EINVAL: 
            /* Not enough free memory.  This often means that the memory
                allocation is limited by the socket buffer limits, not by
                the system memory. */
            case ENOBUFS:
            case ENOMEM:
            // The file descriptor sockfd does not refer to a socket.
            case ENOTSOCK:
            // The referenced socket is not of type SOCK_STREAM.
            case EOPNOTSUPP:
                LOG_FATAL << "Socket::accept error:" << strerror(savedErrno);
                break;
            default:
                LOG_FATAL << "unknown error of ::accept " << savedErrno;
                break;
        }
    }
    return connfd;
}


int connect(int sockfd, const struct sockaddr_in* addr)
{
    return ::connect(sockfd, reinterpret_cast<const struct sockaddr*>(addr), static_cast<socklen_t>(sizeof(&addr)));
}


ssize_t read(int sockfd, void *buf, size_t count)
{
    return ::read(sockfd, buf, count);
}

ssize_t readv(int sockfd, const struct iovec *iov, int iovcnt)
{
    return ::readv(sockfd, iov, iovcnt);
}

ssize_t write(int sockfd, const void *buf, size_t count)
{
  return ::write(sockfd, buf, count);
}

void close(int sockfd)
{
    if (::close(sockfd) < 0)
    {
        LOG_SYSERR << "sockets::close";
    }
}

void shutdownWrite(int sockfd)
{
    if (::shutdown(sockfd, SHUT_WR) < 0)
    {
        LOG_SYSERR << "sockets::shutdownWrite";
    }
}

int getSocketError(int sockfd)
{
    int optval;
    socklen_t optlen = static_cast<socklen_t>(sizeof optval);

    if (::getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0)
    {
        return errno;
    }
    else
    {
        return optval;
    }
}


struct sockaddr_in getLocalAddr(int sockfd)
{
    struct sockaddr_in localaddr;
    ::memset(&localaddr, 0, sizeof localaddr);
    socklen_t addrlen = static_cast<socklen_t>(sizeof localaddr);
    if (::getsockname(sockfd, reinterpret_cast<struct sockaddr*>(&localaddr), &addrlen) < 0)
    {
    LOG_SYSERR << "sockets::getLocalAddr";
    }
    return localaddr;
}

struct sockaddr_in getPeerAddr(int sockfd)
{
  struct sockaddr_in peeraddr;
  ::memset(&peeraddr, 0, sizeof peeraddr);
  socklen_t addrlen = static_cast<socklen_t>(sizeof peeraddr);
  if (::getpeername(sockfd, reinterpret_cast<struct sockaddr*>(&peeraddr), &addrlen) < 0)
  {
    LOG_SYSERR << "sockets::getPeerAddr";
  }
  return peeraddr;
}

void toIpPort(char* buf, size_t size,
                       const struct sockaddr_in* addr4)
{
    
    toIp(buf, size, addr4);
    size_t end = ::strlen(buf);
    uint16_t port = networkToHost16(addr4->sin_port);
    assert(size > end);
    snprintf(buf+end, size-end, ":%u", port);
}


void toIp(char* buf, size_t size,
                   const struct sockaddr_in* addr4)
{
    assert(size >= INET_ADDRSTRLEN);
    ::inet_ntop(AF_INET, &addr4->sin_addr, buf, static_cast<socklen_t>(size));
}


}  // namespace sockets
}  // namespace zbinbin
