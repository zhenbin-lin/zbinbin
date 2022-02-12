#ifndef __ZBINBIN_SOCKET_H_
#define __ZBINBIN_SOCKET_H_


struct tcp_info;

namespace zbinbin
{
class InetAddress;

class Socket
{
public:
    explicit Socket(int sockfd)
        : sockfd_(sockfd)
    {
    }

    ~Socket();

    int fd() const { return sockfd_; }
    

    /// abort if address in use
    void bindAddress(const InetAddress& localaddr);

    /// abort if address in use
    void listen();

    /// On success, returns a non-negative integer that is
    /// a descriptor for the accepted socket, which has been
    /// set to non-blocking and close-on-exec. *peeraddr is assigned.
    /// On error, -1 is returned, and *peeraddr is untouched.
    int accept(InetAddress* peeraddr);

    void shutdownWrite();

    ///
    /// Enable/disable TCP_NODELAY (disable/enable Nagle's algorithm).
    ///
    void setTcpNoDelay(bool on);

    ///
    /// Enable/disable SO_REUSEADDR
    ///
    void setReuseAddr(bool on);

    ///
    /// Enable/disable SO_REUSEPORT
    ///
    void setReusePort(bool on);

    ///
    /// Enable/disable SO_KEEPALIVE
    ///
    void setKeepAlive(bool on);


    bool getTcpInfo(struct tcp_info* tcpi) const;

    bool getTcpInfoString(char* buf, int len) const;

private:
    const int sockfd_;
};


}   // namespace zbinbin




#endif  // __ZBINBIN_SOCKET_H_