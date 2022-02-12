#include "zbinbin/net/Socket.h"
#include "zbinbin/net/SocketOps.h"
#include "zbinbin/log/Logging.h"
#include "zbinbin/net/InetAddress.h"


#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h> // tcp_info
#include <stdio.h>  // snprintf
#include <cstring>



namespace zbinbin
{
Socket::~Socket()
{
    sockets::close(sockfd_);
}


bool Socket::getTcpInfo(struct tcp_info* tcpi) const
{
    socklen_t len = sizeof(*tcpi);
    ::memset(tcpi, 0,len);
    return ::getsockopt(sockfd_, SOL_TCP, TCP_INFO, tcpi, &len) == 0;
}

bool Socket::getTcpInfoString(char* buf, int len) const
{
    struct tcp_info tcpi;
    bool ok = getTcpInfo(&tcpi);
    if (ok)
    {
        snprintf(buf, len, "unrecovered=%u "
                    "rto=%u ato=%u snd_mss=%u rcv_mss=%u "
                    "lost=%u retrans=%u rtt=%u rttvar=%u "
                    "sshthresh=%u cwnd=%u total_retrans=%u",
                    tcpi.tcpi_retransmits,  // Number of unrecovered [RTO] timeouts
                    tcpi.tcpi_rto,          // Retransmit timeout in usec
                    tcpi.tcpi_ato,          // Predicted tick of soft clock in usec
                    tcpi.tcpi_snd_mss,
                    tcpi.tcpi_rcv_mss,
                    tcpi.tcpi_lost,         // Lost packets
                    tcpi.tcpi_retrans,      // Retransmitted packets out
                    tcpi.tcpi_rtt,          // Smoothed round trip time in usec
                    tcpi.tcpi_rttvar,       // Medium deviation
                    tcpi.tcpi_snd_ssthresh,
                    tcpi.tcpi_snd_cwnd,
                    tcpi.tcpi_total_retrans);  // Total retransmits for entire connection
    }
    return ok;
}


void Socket::bindAddress(const InetAddress& localaddr)
{
    sockets::bind(sockfd_, localaddr.getSockAddr());
}

/// abort if address in use
void Socket::listen()
{
    sockets::listen(sockfd_);
}

/// On success, returns a non-negative integer that is
/// a descriptor for the accepted socket, which has been
/// set to non-blocking and close-on-exec. *peeraddr is assigned.
/// On error, -1 is returned, and *peeraddr is untouched.
int Socket::accept(InetAddress* peeraddr)
{
    struct sockaddr_in client;
    int connfd = sockets::accept(sockfd_, &client);
    if (connfd >= 0)
    {
        peeraddr->setSockAddr(client);
    }
    return connfd;
}

void Socket::shutdownWrite()
{
    sockets::shutdownWrite(sockfd_);
}

///
/// Enable/disable TCP_NODELAY (disable/enable Nagle's algorithm).
///
void Socket::setTcpNoDelay(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY,
                &optval, static_cast<socklen_t>(sizeof optval));
}

///
/// Enable/disable SO_REUSEADDR
///
void Socket::setReuseAddr(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR,
                &optval, static_cast<socklen_t>(sizeof optval));
}

///
/// Enable/disable SO_REUSEPORT
///
void Socket::setReusePort(bool on)
{
#ifdef SO_REUSEPORT
    int optval = on ? 1 : 0;
    int ret = ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT,
                            &optval, static_cast<socklen_t>(sizeof optval));
    if (ret < 0 && on)
    {
        LOG_SYSERR << "SO_REUSEPORT failed.";
    }
#else
    if (on)
    {
        LOG_ERROR << "SO_REUSEPORT is not supported.";
    }
#endif
}

///
/// Enable/disable SO_KEEPALIVE
///
void Socket::setKeepAlive(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE,
                &optval, static_cast<socklen_t>(sizeof optval));
}

}   // namespace zbinbin


