#include "zbinbin/http/HttpServer.h"
#include "zbinbin/net/EventLoop.h"
#include "zbinbin/net/InetAddress.h"
#include "zbinbin/net/Callbacks.h"
#include "zbinbin/net/Buffer.h"
#include "zbinbin/thread/ThreadPool.h"
#include "zbinbin/log/Logging.h"



using namespace zbinbin;


HttpServer(EventLoop* loop, InetAddress listAddr)
    : loop_(loop)
    , server_(&loop, listAddr)
    , threadPool_("Http-ThreadPool")
{
    server_.setThreadNum(iothread);
    threadPool_.setThreadNum(northread);

    server_.setConnectionCallback(
        std::bind(&HttpServer::onConnection, this, _1));
    server_.setMessageCallback(
        std::bind(&HttpServer::onMessage, this, _1, _2));
}

HttpServer::~HttpServer()
{

}

HttpServer::start()
{
    if (!started_.exchange(true))
    {
        LOG_INFO << "HttpServer[" << server_.name()
                 << "] starts listening on " 
                 << server_.getIpPortString();
        server_.start();
        threadPool_.start();
    }
}

HttpServer::stop()
{
    if (started_.exchange(false))
    {
        server_.stop();
        threadPool_.stop();
    }
}

/// Must Call before start().
void HttpServer::setComputeThreadNum(int num)
{
    if (!started_.load())
    {
        threadPool_.setThreadNum(num);
    }
}

/// Must Call before start().
void HttpServer::setIoThreadNum(int num)
{
    if (!started_.load())
    {
        server_.setThreadNum(num);
    }
}


void HttpServer::onConnection(const TcpConnectionPtr& conn)
{

}

void HttpServer::onMessage(const TcpConnectionPtr& conn, Buffer* buffer)
{
    std::unique_ptr<Buffer> bufferPtr(new Buffer);
    bufferPtr->swap(*buffer);
    threadPool_.run(std::bind(&HttpServer::decodeMessage, conn, bufferPtr));
}

void HttpServer::decodeMessage(const TcpConnectionPtr& conn, std::unique_ptr<Buffer> buffer)
{
    HttpRequest request;
    if (request.parseRequest(buffer.get()))
    {
        if (onGetCallback_)
        {
            // onGetCallback_()
        }
        if (onPostCallback_)
        {

        }
    }
    else
    {

    }

}