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
    , reading_(false)
    , connIdx_(connIdx)  // size_t MAX;
    , socket_(new Socket(sockfd))
    , channel_(new Channel(loop, sockfd))
    , localAddr_(localAddr)
    , peerAddr_(peerAddr)
{
    channel_->setReadCallback(
        std::bind(&TcpConnection::handleRead, this));
    channel_->setReadCallback(
        std::bind(&TcpConnection::handleWrite, this));
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


void TcpConnection::send(const void* message, size_t len)
{
    if (loop_->isInLoopThread())
    {
        sendInLoop(message, len);
    }
    else
    {
        loop_->runInLoop(
            std::bind(&TcpConnection::sendInLoop, this, message, len));
    }
}

void TcpConnection::send(Buffer* message)
{
    TcpConnection::send(message->peek(), message->readableBytes());
}

void TcpConnection::send(const std::string& message)
{
    send(message.c_str(), message.size());
}


void TcpConnection::startRead()
{
    loop_->runInLoop(
        std::bind(&TcpConnection::startReadInLoop, this));
}

void TcpConnection::stopRead()
{
    loop_->runInLoop(
        std::bind(&TcpConnection::stopReadInLoop, this));
}


void TcpConnection::setTcpNoDelay(bool on)
{
    socket_->setTcpNoDelay(on);
}

void TcpConnection::shutdown()
{
    loop_->runInLoop(
        std::bind(&TcpConnection::shutdownInLoop, this));
}   

void TcpConnection::forceClose()
{
    loop_->runInLoop(
        std::bind(&TcpConnection::forceCloseInLoop, this));
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
        connectionCallback_(shared_from_this()); // 连接建立完成，返回客户
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
            connectionCallback_(shared_from_this()); // 连接建立完成，返回客户
        }
    }
    channel_->remove(); // 放在dtor是否更好?
}

void TcpConnection::startReadInLoop()
{
    loop_->assertInLoopThread();
    if (!reading_ || !channel_->isReading())
    {
        channel_->enableReading();
        reading_ = true;
    }
}

void TcpConnection::stopReadInLoop()
{
    loop_->assertInLoopThread();
    if (reading_ || channel_->isReading())
    {
        channel_->disableReading();
        reading_ = false;
    }
}

void TcpConnection::shutdownInLoop()
{
    loop_->assertInLoopThread();
    if (state_ == kConnected)
    {
        state_ = kDisconnecting;
        if (!channel_->isWriting())
        {
            socket_->shutdownWrite();
        }
    }
}

void TcpConnection::forceCloseInLoop()
{
    loop_->assertInLoopThread();
    if (state_ == kConnected || state_ == kDisconnecting)
    {
        handleClose();
    }
}

void TcpConnection::sendInLoop(const void* message, size_t len)
{
    loop_->assertInLoopThread();
    ssize_t nwrited = 0;
    size_t remaining = len;
    bool faultError = false;
    if (state_ == kDisconnected)
    {
        LOG_WARN << "TcpConnection send data failure! Disconnected, give up writing";
        return;
    }
    // if no thing in output queue, try writing directly
    if (!channel_->isWriting() && outputBuffer_.readableBytes() == 0)
    {
        nwrited = sockets::write(channel_->getFd(), message, len);
        if (nwrited >= 0)
        {
            remaining = len - nwrited;
            if (0 == remaining && writeCompleteCallback_)
            {
                loop_->queueInLoop(
                    std::bind(writeCompleteCallback_, shared_from_this()));
            }
        }
        else
        {
            nwrited = 0;
            if (errno != EWOULDBLOCK)
            {
                LOG_SYSERR << "TcpConnection::sendInLoop " << strerror_tl(errno);
                if (errno == EPIPE || errno == ECONNRESET) // FIXME: any others?
                {
                    faultError = true;
                }
            }           
        }
    }

    assert(remaining <= len);
    // 放入outputBuffer中
    if (!faultError || remaining > 0)
    {
        size_t oldLen = outputBuffer_.readableBytes();
        if (oldLen + remaining >= highWaterMark_
            && oldLen < highWaterMark_
            && highWaterMarkCallback_)
        {
            loop_->queueInLoop(
                std::bind(highWaterMarkCallback_, shared_from_this(), oldLen + remaining));
        }
        outputBuffer_.append(static_cast<const char*>(message) + nwrited, remaining);
        if (!channel_->isWriting())
        {
            channel_->enableWriting();
        }
    }
}

void TcpConnection::handleRead()
{
    loop_->assertInLoopThread();
    int saveErrno = 0;
    ssize_t n = inputBuffer_.readFd(channel_->getFd(), &saveErrno);
    if (n > 0)
    {
        messageCallback_(shared_from_this(), &inputBuffer_);
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

void TcpConnection::handleWrite()
{
    loop_->assertInLoopThread();
    if (channel_->isWriting())
    {
        ssize_t n = sockets::write(channel_->getFd(),
                                   outputBuffer_.peek(),
                                   outputBuffer_.readableBytes());
        if (n > 0)
        {
            outputBuffer_.retrieve(n);
            if (outputBuffer_.readableBytes() == 0)
            {
                channel_->disableWriting();
                if (writeCompleteCallback_)
                {
                    // 直接调用和放入queueInLoop貌似都可以
                    loop_->queueInLoop(
                        std::bind(writeCompleteCallback_, shared_from_this()));
                }
                if (state_ == kDisconnecting)
                {
                    shutdownInLoop();
                }
            }
        }
        else
        {
            LOG_SYSERR << "TcpConnection::handleWrite";
        }
    }
    else
    {
        LOG_TRACE << "Connection fd = " << channel_->getFd()
                  << " is down, no more writing";
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