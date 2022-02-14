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
class EventLoopThreadPool;

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

    /// Set the number of threads for handling input.
    ///
    /// Always accepts new connection in loop's thread.
    /// Must be called before @c start
    /// @param numThreads
    /// - 0 means all I/O in loop's thread, no thread will created.
    ///   this is the default value.
    /// - 1 means all I/O in another thread.
    /// - N means a thread pool with N threads, new connections
    ///   are assigned on a round-robin basis.
    void setThreadNum(int numThreads);
    void setThreadInitCallback(const ThreadInitCallback& cb)
    { threadInitCallback_ = cb; }

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

    std::atomic_bool started_;
    int nextConnId_;    // sure use in loop

    // use by TcpConnection
    // callback when connection construct complete
    ConnectionCallback connectionCallback_;     
    MessageCallback messageCallback_;
    WriteCompleteCallback writeCompleteCallback_;
    ThreadInitCallback threadInitCallback_;

    std::unique_ptr<EventLoopThreadPool> ioEventLoop_;
    ConnectionList connections_;
};

}   // namespace zbinbin




#endif  // __ZBINBIN_TCPSERVER_H_