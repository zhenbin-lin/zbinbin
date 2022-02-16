#ifndef __ZBINBIN_HTTPSERVER_H_
#define __ZBINBIN_HTTPSERVER_H_

#include "zbinbin/http/HttpRequest.h"
#include "zbinbin/http/HttpResponse.h"
#include "zbinbin/net/Callbacks.h"
#include "zbinbin/net/TcpServer.h"


#include <functional>
#include <atomic>
#include <memory>

namespace zbinbin
{
class EventLoop;
class ThreadPool;
class InetAddress;

class HttpServer
{
public:
      typedef std::function<void (const HttpRequest&,
                              HttpResponse&)> HttpCallback;

    ///
    /// @param iothread IO-Reactor的个数, 默认情况下为零个
    /// 也就是Acceptor和IO公用一个Thread
    /// @param northread normal Thread的个数, 计算型线程的个数
    /// 个数为0时, 表示decode calculate encode等的操作都由Reactor来完成
    HttpServer(EventLoop* loop, InetAddress listAddr);
    ~HttpServer();

    void start();

    /// Thread safe, but Must call before start().
    void setGetCallback(const HttpCallback& cb) { onGetCallback_ = cb; }
    /// Thread safe, but Must call before start().
    void setPOSTCallback(const HttpCallback& cb) { onPostCallback_ = cb; }

    /// Must Call before start().
    void setComputeThreadNum(int num);
    /// Must Call before start().
    void setIoThreadNum(int num);


private:
    void onConnection(const TcpConnectionPtr& conn);
    void onMessage(const TcpConnectionPtr& conn, Buffer* buffer);
    void decodeMessage(const TcpConnectionPtr& conn, std::unique_ptr<Buffer> buffer);

    std::atomic<bool> started_; 
    EventLoop* loop_;
    TcpServer server_;
    ThreadPool threadPool_;

    HttpCallback onGetCallback_;
    HttpCallback onPostCallback_;
};


}   // namespace zbinbin
#endif  // __ZBINBIN_HTTPSERVER_H_