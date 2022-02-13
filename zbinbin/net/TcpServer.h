#ifndef __ZBINBIN_TCPSERVER_H_
#define __ZBINBIN_TCPSERVER_H_

#include "zbinbin/net/Callbacks.h"
#include "zbinbin/net/InetAddress.h"
#include "zbinbin/utility/noncopyable.h"

#include <string>
#include <functional>
#include <atomic>
#include <vector>


namespace zbinbin
{
class Acceptor;
class EventLoop;
// class EventLoopThreadPool;

class TcpServer : noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;
    enum Option
    {
        kNoReusePort,
        kReusePort,
    };


    TcpServer(EventLoop* loop,
              const InetAddress& listenAddr,
              const std::string& nameArg,
              Option option = kReusePort);
    ~TcpServer();

    /// Starts the server if it's not listening.
    ///
    /// It's harmless to call it multiple times.
    /// Thread safe.
    void start();

    /// Set connection callback.
    /// connection Established and Destroyed will callback
    /// Not thread safe.
    void setConnectionCallback(const ConnectionCallback& cb)
    { connectionCallback_ = cb; }

    /// Set message callback.
    /// Not thread safe.
    void setMessageCallback(const MessageCallback& cb)
    { messageCallback_ = cb; }

    /// Set write complete callback.
    /// Not thread safe.
    void setWriteCompleteCallback(const WriteCompleteCallback& cb)
    { writeCompleteCallback_ = cb; }


    const std::string& ipPort() const { return ipPort_; }
    const std::string& name() const { return name_; }

private:
    using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
    using ConnectionList = std::vector<TcpConnectionPtr>;

    void newConnection(int connfd, const InetAddress& clientAddr);
    void removeConnection(const TcpConnectionPtr& conn);
    void removeConnectionInLoop(const TcpConnectionPtr& conn);

    EventLoop* loop_;   // the acceptor loop
    const std::string ipPort_;
    const std::string name_;
    std::unique_ptr<Acceptor> acceptor_;

    std::atomic_flag started_;
    int nextConnId_;    // sure use in loop

    // use by TcpConnection
    // callback when connection construct complete
    ConnectionCallback connectionCallback_;     
    MessageCallback messageCallback_;
    WriteCompleteCallback writeCompleteCallback_;

    ConnectionList connections_;
};

}   // namespace zbinbin




#endif  // __ZBINBIN_TCPSERVER_H_