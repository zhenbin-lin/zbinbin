#include "zbinbin/net/InetAddress.h"
#include "zbinbin/net/SocketOps.h"

#include <cstring>

namespace zbinbin
{
/// Constructs an endpoint with given port number.
/// Mostly used in TcpServer listening.
InetAddress::InetAddress(uint16_t port, bool loopbackOnly)
{
    ::memset(&addr_, 0, sizeof addr_);
    addr_.sin_family = AF_INET;
    in_addr_t ip = loopbackOnly ? sockets::kInaddrLoopback : sockets::kInaddrAny;
    addr_.sin_addr.s_addr = sockets::hostToNetwork32(ip);
    addr_.sin_port = sockets::hostToNetwork16(port);
}


std::string InetAddress::getIpPortString() const
{
    char buf[64] = "";
    sockets::toIpPort(buf, sizeof buf, getSockAddr());
    return buf;
}

std::string InetAddress::getIpString() const
{
    char buf[64] = "";
    sockets::toIp(buf, sizeof buf, getSockAddr());
    return buf;
}

uint16_t InetAddress::getPort() const
{
    return sockets::networkToHost16(addr_.sin_port);
}

}   // namespace zbinbin
