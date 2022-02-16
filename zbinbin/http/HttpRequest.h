#ifndef __ZBINBIN_HTTPREQUEST_H_
#define __ZBINBIN_HTTPREQUEST_H_

#include "zbinbin/net/Buffer.h"
#include "zbinbin/utility/noncopyable.h"

#include <string>
#include <map>

namespace zbinbin
{
class HttpRequest : noncopyable
{
private:
    enum HttpRequestDecodeState {
        BEFORE_STATE,
        // 请求方法解析
        INVALID_METHOD,
        METHOD,

        // 请求URI解析
        BEFORE_URI,
        IN_URI,
            // URI后面附带的参数解析
            BEFORE_URI_PARAM_KEY,
            URI_PARAM_KEY,
            BEFORE_URI_PARAM_VALUE,
            URI_PARAM_VALUE,
        INVALID_URI,
        
        BEFORE_PROTOCOL,
        INVALID_PROTOCOL,
        PROTOCOL,

        // 版本号解析
        BEFORE_VERSION,
        VERSION,
        INVALID_VERSION,

        WHEN_CR,
        CR_LF,
        CR_LF_CR,
        CR_LF_CR_LF,    // header到body的过度

        HEADER_KEY,
        BEFORE_HEADER_COLON,    // header和:之间的空格
        HEADER_COLON,
        HEADER_VALUE,
        INVALID_HEADER,


        COMPLETE,
        BODY,
        INVALID,

        HttpRequestDecodeStateLength,
    };

public:
    explicit HttpRequest();
    ~HttpRequest();

    bool HttpRequest::parseRequest(Buffer* buffer);

    std::string getMethod() const { return method_; }
    std::string getUrl() const { return url_; }

    ///
    /// @param key url中的参数名字
    /// @return 如果有则返回value, 否则返回一个空字符串
    ///
    std::string getParams(const std::string& key) const 
    { 
        std::string result;
        auto it = requestParams_.find(key);
        if (it != requestParams_.end())
        {
            result = it->second;
        }
        return result; 
    }

    std::map<std::string, std::string> getRequestParams() const 
    {
        return requestParams_;
    }

    std::string getProtocol() const { return protocol_; }
    std::string getVersion() const { return version_; }
    std::map<std::string, std::string> getHeaders() const { return headers_; }


    ///
    /// @param field header中的参数名字
    /// @return 如果有则返回value, 否则返回一个空字符串
    ///
    std::string getHeader(const std::string& field) const
    {
        std::string result;
        auto it = headers_.find(field);
        if (it != headers_.end())
        {
            result = it->second;
        }
        return result;
    }

    std::string getBody() const { return body_; }
private:
    const char* toStateString(HttpRequestDecodeState state);

    std::string method_;
    std::string url_;

    std::map<std::string, std::string> requestParams_;

    std::string protocol_;
    std::string version_;

    std::map<std::string, std::string> headers_;

    std::string body_;
    HttpRequestDecodeState state_;

    static char kLF;    // 换行
    static char kCR;    // 回车
};



}   // namespace zbinbin
#endif  // __ZBINBIN_HTTPREQUEST_H_