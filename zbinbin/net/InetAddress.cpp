#include "zbinbin/net/InetAddress.h"
#include "zbinbin/net/SocketOps.h"

#include <cstring>

namespace zbinbin
{
namespace net
{

/// Constructs an endpoint with given port number.
/// Mostly used in TcpServer listening.
InetAddress::InetAddress(uint16_t port, bool loopbackOnly)
{
    ::memset(&addr_, 0, sizeof addr_);
    addr_.sin_family = AF_INET;
    in_addr_t ip = loopbackOnly ? INADDR_LOOPBACK : INADDR_ANY;
    addr_.sin_addr.s_addr = sockets::hostToNetwork32(ip);
    addr_.sin_port = sockets::hostToNetwork16(port);
}


std::string InetAddress::getIpPortString()
{
    char buf[64] = "";
    sockets::toIpPort(buf, sizeof buf, getSockAddr());
    return buf;
}

std::string InetAddress::getIpString()
{
    char buf[64] = "";
    sockets::toIp(buf, sizeof buf, getSockAddr());
    return buf;
}

uint16_t InetAddress::getPort()
{
    return sockets::networkToHost16(addr_.sin_port);
}

    
}   // namespace net
}   // namespace zbinbin
