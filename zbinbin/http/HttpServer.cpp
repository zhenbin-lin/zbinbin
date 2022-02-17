#include "zbinbin/http/HttpServer.h"
#include "zbinbin/net/EventLoop.h"
#include "zbinbin/net/Callbacks.h"
#include "zbinbin/net/Buffer.h"
#include "zbinbin/log/Logging.h"
#include "zbinbin/net/TcpConnection.h"


#include <map>
#include <string>
#include <fstream>


using namespace zbinbin;


HttpServer::HttpServer(EventLoop* loop, InetAddress listAddr)
    : started_(false)
    , loop_(loop)
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

namespace zbinbin
{
namespace detail
{
class FileType
{
public:
    template<int N>
    FileType(const char (&arr)[N]) : data_(arr), size_(N - 1)
    {
        const char* slash = strrchr(data_, '.');
        if (slash) {
            data_ = slash + 1;
            size_ -= static_cast<int>(data_ - arr);
        }
    }
    explicit FileType(const char* filename)
    : data_(filename)
    {
        const char* slash = strrchr(filename, '.');
        if (slash)
        {
            data_ = slash + 1;
        }
        size_ = static_cast<int>(strlen(data_));
    }
    const char* data_;
    int size_;

    std::string getContextType()
    {
        static std::map<std::string, std::string> ContextType = {
            {"html", "text/html"},
            {"css", "text/html"},
            {"jsp", "text/html"},
            {"js", "application/x-javascript"},
            {"xml", "application/xml"},
            {"xhtml", "application/xhtml+xml"},
            {"json", "application/json"},
            {"gif", "image/gif"},
            {"jpeg", "image/jpeg"},
            {"png", "image/png"},
            {"jpg", "image/jpg"}
        };
        std::string result;
        auto it = ContextType.find(std::string(data_, size_));
        if (it != ContextType.end())
        {
            result = it->second;
        }
        return result;
    }
};
 
}   //namespace detail
}   // namespace zbinbin


void HttpServer::decodeMessage(const TcpConnectionPtr& conn, std::shared_ptr<Buffer> buffer)
{
    using namespace detail;
    // using std::string;
    HttpRequest request;
    HttpResponse response(false);
    if (request.parseRequest(buffer.get()))
    {        
        // Context-Type
        std::string url = request.getUrl();
        LOG_INFO << url;
        if (url != "/")
        {
            // LOG_TRACE << request.getUrl();
            FileType fileType(url.c_str());
            if (fileType.getContextType().empty())
            {
                conn->send("HTTP/1.1 417 Unkown File Type\r\n\r\n");
                conn->shutdown();
                return;
            }
            else
            {
                response.addHeader("Context-Type", fileType.getContextType());
            }
        }
        else // 主页
        {
            url = "/index.html";
            response.addHeader("Context-Type", "text/html");
        }
        
        // Method
        const std::string& method = request.getMethod();
        if (method == "GET" && onGetCallback_)
        {
            onGetCallback_(request, response);
        }
        if (method == "PUT" && onPostCallback_)
        {
            onPostCallback_(request, response);
        }

        //打开文件。
        url = "www" + url;
        FILE *fp = ::fopen(url.c_str(), "rb");   
        if (fp)
        {
            ::fseek(fp, 0, SEEK_END);     //定位文件指针到文件尾。
            size_t size = ::ftell (fp);   //获取文件指针偏移量，即文件大小。
            ::fseek(fp, 0, SEEK_SET);     //定位文件指针到文件尾。
            char *binaryBuffer = (char*)malloc(sizeof(char)*size);
            size_t nread = 0;
            size_t total = 0;
            size_t tmp = size;
            while((nread = ::fread(binaryBuffer + total, 1, tmp, fp)) > 0)
            {
                total += nread;
                tmp -= total;
            }
            if (total == size)
                response.setBody(binaryBuffer, total);
        }
        else
        {
            response.setStatusCode(HttpResponse::k404NotFound);
            response.setStatusMessage("Not Found");
            response.setCloseConnection(true);
        }

    }
    else  // 客户端请求的语法错误，服务器无法理解
    {
        response.setStatusCode(HttpResponse::k400BadRequest);
        response.setStatusMessage("Bad Request");
        response.setCloseConnection(true);
    }


    Buffer buf;
    response.appendToBuffer(&buf);
    conn->send(&buf);
    if (response.closeConnection())
    {
        conn->shutdown();
    }
}