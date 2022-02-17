#include "zbinbin/http/HttpServer.h"
#include "zbinbin/net/EventLoop.h"
#include "zbinbin/net/Callbacks.h"
#include "zbinbin/net/Buffer.h"
#include "zbinbin/log/Logging.h"
#include "zbinbin/net/TcpConnection.h"



using namespace zbinbin;


HttpServer::HttpServer(EventLoop* loop, InetAddress listAddr)
    : loop_(loop)
    , server_(loop, listAddr, "Tcp")
    , threadPool_("Http-ThreadPool")
{
    server_.setConnectionCallback(
        std::bind(&HttpServer::onConnection, this, _1));
    server_.setMessageCallback(
        std::bind(&HttpServer::onMessage, this, _1, _2));
}

HttpServer::~HttpServer()
{

}

void HttpServer::start()
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

void HttpServer::stop()
{
    if (started_.exchange(false))
    {
        // server_.stop();
        threadPool_.stop();
    }
}

void HttpServer::setComputeThreadNum(int num)
{
    threadPool_.setThreadNum(num);
}

void HttpServer::setIoThreadNum(int num)
{
    server_.setThreadNum(num);
}


void HttpServer::onConnection(const TcpConnectionPtr& conn)
{

}

void HttpServer::onMessage(const TcpConnectionPtr& conn, Buffer* buffer)
{
    std::shared_ptr<Buffer> buf(new Buffer);
    buf->swap(*buffer);
    // int i = 1;
    threadPool_.run(
        std::bind(&HttpServer::decodeMessage, this, conn, buf));
}

void HttpServer::print(int)
{

}

void HttpServer::decodeMessage(const TcpConnectionPtr& conn, std::shared_ptr<Buffer> buffer)
{
    HttpRequest request;
    HttpResponse response(false);
    bool success = true;
    if (request.parseRequest(buffer.get()))
    {
        LOG_INFO << request.getMethod() << " " << (request.getMethod() == "GET");
        if (request.getMethod() == "GET")
        {
            if (onGetCallback_)
            {
                onGetCallback_(request, response);
            }
        }
        else if (request.getMethod() == "POST")
        {
            if (onPostCallback_)
            {
                onPostCallback_(request, response);
            }
        }   
        else // 服务器不支持请求的功能，无法完成请求
        {
            conn->send("HTTP/1.1 501 Not Implemented Method\r\n\r\n");
            success = false;
        }
    }
    else  // 客户端请求的语法错误，服务器无法理解
    {
        conn->send("HTTP/1.1 400 Bad Request\r\n\r\n");
        success = false;
    }

    if (success)
    {

    }
    else
    {
        conn->shutdown();
    }   
}