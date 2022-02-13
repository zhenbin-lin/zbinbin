#ifndef __ZBINBIN_INETADDRESS_H_
#define __ZBINBIN_INETADDRESS_H_

#include "zbinbin/utility/copyable.h"

#include <string>
#include <netinet/in.h>
#include <stdint.h>


namespace zbinbin
{
namespace sockets
{
static const in_addr_t kInaddrAny = INADDR_ANY;             // local ipv4 address
static const in_addr_t kInaddrLoopback = INADDR_LOOPBACK;   // 127.0.0.1
}

/// just only support Ipv4   
class InetAddress : public copyable
{
public:
    /// Constructs an endpoint with given port number.
    /// Mostly used in TcpServer listening.
    explicit InetAddress(uint16_t port = 0, bool loopbackOnly = false);

    /// Constructs an endpoint with given struct @c sockaddr_in
    /// Mostly used when accepting new connections
    explicit InetAddress(const struct sockaddr_in& addr)
        : addr_(addr)
    {}

    void setSockAddr(const struct sockaddr_in& addr) { addr_ = addr; }

    sa_family_t family() const { return addr_.sin_family; }

    std::string getIpString() const;
    std::string getIpPortString() const;
    uint16_t getPort() const;
    const struct sockaddr_in* getSockAddr() const { return &addr_; }

private:
    struct sockaddr_in addr_;
};


}   // namespace zbinbin
#endif  // __ZBINBIN_INETADDRESS_H_