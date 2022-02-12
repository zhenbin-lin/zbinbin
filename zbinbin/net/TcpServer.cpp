#include "zbinbin/net/TcpServer.h"
#include "zbinbin/log/Logging.h"
#include "zbinbin/net/InetAddress.h"
#include "zbinbin/net/EventLoop.h"
#include "zbinbin/net/Acceptor.h"
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
    , acceptor_(new Accpetor(loop_, listenAddr, option == kReusePort))
    , started_(ATOMIC_FLAG_INIT)    // false
    , nextConnId_(0)
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
    if (!started_.test_and_set())
    {
        LOG_TRACE << "TcpServer started in " << CurrentThread::tid();
        assert(!acceptor_->listening());
        loop_->runInLoop(
            std::bind(&Acceptor::listen(), acceptor_.get()));
    }
}


void TcpServer::newConnection(int connfd, const InetAddress& clientAddr)
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
}

}