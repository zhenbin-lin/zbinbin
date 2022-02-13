#include "zbinbin/net/TcpConnection.h"
#include "zbinbin/net/EventLoop.h"
#include "zbinbin/net/SocketOps.h"
#include "zbinbin/net/Channel.h"
#include "zbinbin/net/Socket.h"
#include "zbinbin/log/Logging.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h> // tcp_info
#include <stdio.h>  // snprintf
#include <string.h>
#include <assert.h>
#include <errno.h>


namespace zbinbin
{
TcpConnection::TcpConnection(EventLoop* loop,
                             const std::string& name,
                             int sockfd,
                             size_t connIdx,
                             const InetAddress& localAddr,
                             const InetAddress& peerAddr)
    : loop_(loop)
    , name_(name)
    , state_(kConnecting)
    , reading_(true)
    , connIdx_(connIdx)  // size_t MAX;
    , socket_(new Socket(sockfd))
    , channel_(new Channel(loop, sockfd))
    , localAddr_(localAddr)
    , peerAddr_(peerAddr)
{
    channel_->setReadCallback(
        std::bind(&TcpConnection::handleRead, this));
    channel_->setErrorCallback(
        std::bind(&TcpConnection::handleError, this));
    channel_->setCloseCallback(
        std::bind(&TcpConnection::handleClose, this));
    LOG_DEBUG << "TcpConnection::ctor[" <<  name_ << "] at " << this
              << " fd=" << sockfd;
    socket_->setKeepAlive(true);
}


TcpConnection::~TcpConnection()
{
    LOG_DEBUG << "TcpConnection::dtor[" <<  name_ << "] at " << this
              << " fd=" << channel_->getFd()
              << " state=" << getStateString();
    if (state_ != kDisconnected)
    {
        LOG_ERROR << "TcpConnetion dtor, but not Destroyed before.";
    }
}

const std::unique_ptr<struct tcp_info> TcpConnection::getTcpInfo() const
{
    struct tcp_info* tcpi = new struct tcp_info;
    ::memset(tcpi, 0, sizeof(struct tcp_info));
    if (socket_->getTcpInfo(tcpi))
    {
        return std::unique_ptr<struct tcp_info>(tcpi);
    }
    else
    {
        return std::make_unique<struct tcp_info>();
    }
}

const std::string TcpConnection::getTcpInfoString() const
{
    char buf[1024] = {'\0'};
    socket_->getTcpInfoString(buf, sizeof buf);
    return buf;
}


const std::string TcpConnection::getStateString() const
{
    static const char* StateString[4] = {
        "kDisconnected",
        "kConnecting",
        "kConnected",
        "kDisconnecting"
    };
    assert(kDisconnected <= state_ && state_ <= kDisconnecting);
    return StateString[state_];
}

void TcpConnection::setTcpNoDelay(bool on)
{
    socket_->setTcpNoDelay(on);
}

// called when TcpServer accepts a new connection
void TcpConnection::connectEstablished()
{
    loop_->assertInLoopThread();
    assert(state_ == kConnecting);
    state_ = kConnected;
    channel_->enableReading();
    channel_->enableWriting();
    if (connectionCallback_)
    {
        auto self = shared_from_this();
        connectionCallback_(self); // 连接建立完成，返回客户
    }
}
// called when TcpServer has removed me from its map
void TcpConnection::connectDestroyed()
{
    loop_->assertInLoopThread();
    // maybe is kConnecting
    if (state_ == kConnected)
    {
        channel_->disableAll();
        if (connectionCallback_)
        {
            auto self = shared_from_this();
            connectionCallback_(self); // 连接建立完成，返回客户
        }
    }
    channel_->remove(); // 放在dtor是否更好?
}

void TcpConnection::handleRead()
{
    loop_->assertInLoopThread();
    char buf[65536] = {'\0'};
    ssize_t n = sockets::read(channel_->getFd(), buf, sizeof buf);
    LOG_INFO << "TcpConnection: " << name_ << " recieve \"" << buf << "\"";
    if (n > 0)
    {

    }
    else if (n == 0) // close by peer
    {
        handleClose();
    }
    else // read error
    {
        LOG_SYSERR << "TcpConnection::handleRead";
        handleError();
    }
}

void TcpConnection::handleError()
{
    int err = sockets::getSocketError(channel_->getFd());
    LOG_ERROR << "TcpConnection::handleError [" << name_
                << "] - SO_ERROR = " << err << " " << strerror_tl(err);
}

void TcpConnection::handleClose()
{
    loop_->assertInLoopThread();
    LOG_TRACE << "fd = " << channel_->getFd() << " state = " << getStateString();
    assert(state_ == kConnected || state_ == kDisconnecting);
    state_ = kDisconnected;
    channel_->disableAll();

    // if must??
    if (connectionCallback_)
    {
        connectionCallback_(shared_from_this()); // return to client
    }
    closeCallback_(shared_from_this());  // return to TcpServer
}

}   // namespace zbinbin