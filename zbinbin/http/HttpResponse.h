#ifndef __ZBINBIN_HTTPRESPONSE_H_
#define __ZBINBIN_HTTPRESPONSE_H_

#include "zbinbin/net/Buffer.h"

#include <string>
#include <map>

namespace zbinbin
{
class HttpResponse
{
public:
    enum HttpStatusCode
    {
        kUnknown,
        k200Ok = 200,
        // 永久移动。请求的资源已被永久的移动到新URI，返回信息会包括新的URI，浏览器会自动定向到新URI
        k301MovedPermanently = 301,
        // 未修改。所请求的资源未修改，服务器返回此状态码时，不会返回任何资源。
        k304NotModified = 304,      
        // 临时移动。与301类似。但资源只是临时被移动。客户端应继续使用原有URI
        k302Found = 302, 
        // 客户端请求的语法错误，服务器无法理解
        k400BadRequest = 400,       
        // 服务器无法根据客户端的请求找到资源（网页）。通过此代码，网站设计人员可设置"您所请求的资源无法找到"的个性页面

        k404NotFound = 404,
        // 客户端请求的范围无效
        k416RequestedRangeNotSatisfiable = 416,
        // 服务器不支持请求的HTTP协议的版本，无法完成处理
        k505HTTPVersionNotSupported = 505,
    };


    explicit HttpResponse(bool close)
        : statusCode_(kUnknown)
        , closeConnection_(close)
    {
    }

    ~HttpResponse() = default;

    void setStatusCode(HttpStatusCode code) 
    { statusCode_ = code; }

    void setStatusMessage(const std::string& message)
    { statusMessage_ = message; }

    void setCloseConnection(bool on)
    { closeConnection_ = on; }

    void addHeader(const std::string& key, const std::string& value) 
    {
        headers_[key] = value;
    }
    void setBody(const std::string& body)
    {
        body_ = body;
    }

private:
    std::map<std::string, std::string> headers_;
    HttpStatusCode statusCode_;
    std::string statusMessage_;
    bool closeConnection_;

    std::string body_;
};
} // namespace zbinbin
#endif  // __ZBINBIN_HTTPRESPONSE_H_