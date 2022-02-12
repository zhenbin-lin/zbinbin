#include "zbinbin/net/SocketOps.h"


#include <fcntl.h>
#include <stdio.h>  // snprintf
#include <sys/socket.h>
#include <sys/uio.h>  // readv
#include <unistd.h>
#include <assert.h>
#include <cstring>


namespace zbinbin
{
namespace net
{
namespace sockets
{

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
}  // namespace net
}  // namespace zbinbin
