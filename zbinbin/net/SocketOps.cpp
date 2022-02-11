
#include "zbinbin/net/SocketOps.h"


#include <fcntl.h>
#include <stdio.h>  // snprintf
#include <sys/socket.h>
#include <sys/uio.h>  // readv
#include <unistd.h>

namespace zbinbin
{
namespace net
{
namespace sockets
{

ssize_t readv(int sockfd, const struct iovec *iov, int iovcnt)
{
    return ::readv(sockfd, iov, iovcnt);
}

}  // namespace sockets
}  // namespace net
}  // namespace zbinbin
