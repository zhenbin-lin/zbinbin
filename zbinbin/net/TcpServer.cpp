#include "zbinbin/log/Logging.h"
#include "zbinbin/net/Acceptor.h"
#include "zbinbin/net/TcpServer.h"
#include "zbinbin/net/EventLoop.h"
#include "zbinbin/net/SocketOps.h"
#include "zbinbin/net/InetAddress.h"
#include "zbinbin/net/TcpConnection.h"
#include "zbinbin/net/EventLoopThreadPool.h"
#include "zbinbin/thread/CurrentThread.h"


namespace zbinbin
{

TcpServer::TcpServer(EventLoop* loop,
                     const InetAddress& listenAddr,
                     const std::string& nameArg,
                     Option option)
    : loop_(loop)
    , ipPort_(listenAddr.getIpPortString())
    , name_(nameArg)
    , acceptor_(new Acceptor(loop, listenAddr, option == kReusePort))
    , started_(false)    // false
    , nextConnId_(1)
    , ioEventLoop_(new EventLoopThreadPool(loop, nameArg + " io thread"))
{   
    acceptor_->setNewConnectionCallback(
        std::bind(&TcpServer::newConnection, this, _1, _2));
}


TcpServer::~TcpServer()
{
    // is neccessary ???
    // loop_->assertInLoopThread(); 
    LOG_TRACE << "TcpServer::~TcpServer [" << name_ << "] destructing";
}


void TcpServer::start()
{
    // set started_ = true and return old value
    if (!started_.exchange(true))
    {
        LOG_TRACE << "TcpServer started in " << CurrentThread::tid();
        assert(!acceptor_->listening());
        loop_->runInLoop(
            std::bind(&Acceptor::listen, acceptor_.get()));
        ioEventLoop_->start(threadInitCallback_);
    }
}

void TcpServer::setThreadNum(int numThreads)
{
    assert(!started_.load());
    assert(0 <= numThreads);
    ioEventLoop_->setThreadNum(numThreads);
}

void TcpServer::newConnection(int sockfd, const InetAddress& clientAddr)
{
    loop_->assertInLoopThread();
    // EventLoop* ioLoop = threadPool_->getNextLoop();
    char buf[64];
    snprintf(buf, sizeof buf, "-%s#%d", ipPort_.c_str(), nextConnId_);
    ++nextConnId_;
    std::string connName = name_ + buf;
    LOG_INFO << "TcpServer::newConnection [" << name_
             << "] - new connection [" << connName
             << "] from " << clientAddr.getIpPortString();
    InetAddress localAddr(sockets::getLocalAddr(sockfd));
    EventLoop* ioLoop = ioEventLoop_->getNextLoop();
    TcpConnectionPtr conn = TcpConnectionPtr(
        new TcpConnection(
            ioLoop, connName, sockfd, connections_.size(), localAddr, clientAddr));
    connections_.push_back(conn);   // must before new conn
    conn->setConnectionCallback(connectionCallback_);
    conn->setMessageCallback(messageCallback_);
    conn->setWriteCompleteCallback(writeCompleteCallback_);
    conn->setCloseCallback(
        std::bind(&TcpServer::removeConnection, this, _1));
    ioLoop->runInLoop(
        std::bind(&TcpConnection::connectEstablished, conn));
}

void TcpServer::removeConnection(const TcpConnectionPtr& conn)
{
    // FIXME: unsafe
    loop_->runInLoop(std::bind(&TcpServer::removeConnectionInLoop, this, conn));
}

void TcpServer::removeConnectionInLoop(const TcpConnectionPtr& conn)
{
    loop_->assertInLoopThread();
    LOG_INFO << "TcpServer::removeConnectionInLoop [" << name_
            << "] - connection " << conn->getName();
    size_t idx = conn->getIdx();
    if (idx == connections_.size() - 1)
    {
        connections_.pop_back();
    }
    else
    {
        assert(0 <= idx && idx < connections_.size());
        std::iter_swap(connections_.begin() + idx,
                       connections_.end() - 1);
        connections_[idx]->setIdx(idx);          
    }
    // ???IO???????????????connection
    EventLoop* ioLoop = conn->getLoop();
    ioLoop->runInLoop(
        std::bind(&TcpConnection::connectDestroyed, conn));
}

}