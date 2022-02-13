#include "zbinbin/net/Acceptor.h"
#include "zbinbin/net/SocketOps.h"
#include "zbinbin/net/InetAddress.h"
#include "zbinbin/net/EventLoop.h"
#include "zbinbin/log/Logging.h"

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

namespace zbinbin
{

Acceptor::Acceptor(EventLoop* loop, const InetAddress& listenAdrr, bool resuseport)
    : listening_(false)
    , loop_(loop)
    , acceptSocket_(sockets::createNonblockingOrDie(listenAdrr.family()))
    , acceptChannel_(loop, acceptSocket_.fd())
    , idleFd_(::open("/dev/null", O_RDONLY | O_CLOEXEC))
{
    acceptSocket_.setReuseAddr(true);
    acceptSocket_.setReusePort(resuseport);
    acceptSocket_.bindAddress(listenAdrr);
    acceptChannel_.setReadCallback(
        std::bind(&Acceptor::handleRead, this));
}

Acceptor::~Acceptor()
{
    acceptChannel_.disableAll();
    acceptChannel_.remove();
    ::close(idleFd_);
}

void Acceptor::listen()
{
    loop_->assertInLoopThread();
    assert(!listening_);
    listening_ = true;
    acceptSocket_.listen();
    acceptChannel_.enableReading();
}

void Acceptor::handleRead()
{
    loop_->assertInLoopThread();
    InetAddress peerAddress;
    int connfd = acceptSocket_.accept(&peerAddress);
    if (connfd >= 0)
    {
        if (newConnectCallback_)
        {
            newConnectCallback_(connfd, peerAddress);
        }
        else
        {
            sockets::close(connfd);
        }
    } 
    else
    {
        // Read the section named "The special problem of
        // accept()ing when you can't" in libev's doc.
        // By Marc Lehmann, author of libev.
        // 处理文件描述符上限问题
        if (errno == EMFILE)
        {
            ::close(idleFd_);
            idleFd_ = ::accept(acceptSocket_.fd(), NULL, NULL);
            ::close(idleFd_);
            idleFd_ = ::open("/dev/null", O_RDONLY | O_CLOEXEC);
            LOG_SYSERR << "in Acceptor::handleRead accept error, not more fd could use";
        }
        else
        {
            LOG_SYSERR << "in Acceptor::handleRead accept error: " << strerror(errno);
        }
    }
}

}   // namespace zbinbin