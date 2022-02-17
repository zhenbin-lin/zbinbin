#ifndef __ZBINBIN_HTTPSERVER_H_
#define __ZBINBIN_HTTPSERVER_H_

#include "zbinbin/http/HttpRequest.h"
#include "zbinbin/http/HttpResponse.h"
#include "zbinbin/thread/ThreadPool.h"
#include "zbinbin/net/Callbacks.h"
#include "zbinbin/net/TcpServer.h"
#include "zbinbin/net/InetAddress.h"


#include <functional>
#include <atomic>
#include <memory>

namespace zbinbin
{
class EventLoop;

class HttpServer
{
public:
    typedef std::function<void (const HttpRequest&,
                            HttpResponse&)> HttpCallback;
    using c = std::function<void (const TcpConnectionPtr&, std::unique_ptr<Buffer>)>;

    HttpServer(EventLoop* loop, InetAddress listAddr);
    ~HttpServer();

    void start();

    void stop();

    /// Thread safe, but Must call before start().
    void setGetCallback(const HttpCallback& cb) { onGetCallback_ = cb; }
    /// Thread safe, but Must call before start().
    void setPOSTCallback(const HttpCallback& cb) { onPostCallback_ = cb; }
    /// NOT Thread Safe
    /// Must Call before start().
    /// Set the number of threads for handling decode,encode,compute
    ///
    /// dispatch Not-IO task to ThreadPool
    /// - 0 means all Not-IO task handle by they IO Thread
    /// - 1 means a Thread handle all Not-IO task
    /// - N means a thread pool with N threads, new task
    ///   are assigned on a round-robin basis.
    void setComputeThreadNum(int num);

    /// NOT Thread Safe
    /// Must Call before start().
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
    void setIoThreadNum(int num);

private:
    void onConnection(const TcpConnectionPtr& conn);
    void onMessage(const TcpConnectionPtr& conn, Buffer* buffer);
    void decodeMessage(const TcpConnectionPtr& conn, std::shared_ptr<Buffer> buffer);

    std::atomic<bool> started_; 
    EventLoop* loop_;
    TcpServer server_;
    ThreadPool threadPool_;

    HttpCallback onGetCallback_;
    HttpCallback onPostCallback_;
};


}   // namespace zbinbin
#endif  // __ZBINBIN_HTTPSERVER_H_