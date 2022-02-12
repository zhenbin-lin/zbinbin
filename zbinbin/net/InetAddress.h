#include "zbinbin/utility/copyable.h"

#include <string>
#include <netinet/in.h>
#include <stdint.h>


namespace zbinbin
{
namespace net
{

namespace sockets
{
static const in_addr_t kInaddrAny = INADDR_ANY;             // local ipv4 address
static const in_addr_t kInaddrLoopback = INADDR_LOOPBACK;   // 127.0.0.1
}
    
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

    std::string getIpString();
    std::string getIpPortString();
    uint16_t getPort();
    const struct sockaddr_in* getSockAddr() const { return &addr_; }

private:
    struct sockaddr_in addr_;
};


}   // namespace net
}   // namespace zbinbin
