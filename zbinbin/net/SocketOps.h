#ifndef __ZBINBIN_SOCKETOPS_H_
#define __ZBINBIN_SOCKETOPS_H_

#include <arpa/inet.h>

namespace zbinbin
{
namespace net
{
namespace sockets
{

ssize_t readv(int sockfd, const struct iovec *iov, int iovcnt);

}  // namespace sockets
}  // namespace net
}  // namespace zbinbin

#endif  // __ZBINBIN_SOCKETOPS_H_