#ifndef __ZBINBIN_HTTPREQUEST_H_
#define __ZBINBIN_HTTPREQUEST_H_

#include "zbinbin/net/Buffer.h"

#include <string>
#include <map>


/* "POST /audiolibrary/music?ar=1595301089068&n=1p1 HTTP/1.1\r\n"
		"Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, application/x-silverlight, application/x-shockwave-flash\r\n"
		"Referer: http://www.google.cn\r\n"
		"Accept-Language: zh-cn\r\n"
		"Accept-Encoding: gzip, deflate\r\n"
		"User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727; TheWorld)\r\n"
		"content-length:28\r\n"
		"Host: www.google.cn\r\n"
		"Connection: Keep-Alive\r\n"
		"Cookie: PREF=ID=80a06da87be9ae3c:U=f7167333e2c3b714:NW=1:TM=1261551909:LM=1261551917:S=ybYcq2wpfefs4V9g; NID=31=ojj8d-IygaEtSxLgaJmqSjVhCspkviJrB6omjamNrSm8lZhKy_yMfO2M4QMRKcH1g0iQv9u\r\n"
		"\r\n"
		"hl=zh-CN&source=hp&q=domety"; */

namespace zbinbin
{
class HttpRequest
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
    HttpRequest(Buffer &rhs);
    ~HttpRequest();

    std::string getMethod() const { return method_; }
    std::string getUrl() const { return url_; }

    ///
    /// @param key url中的参数名字
    /// @return 如果有则返回value, 否则返回一个空字符串
    ///
    std::string getParams(const std::string& key) const 
    { 
        if (requestParams_.find(key) != requestParams_.end())
        {
            return requestParams_.find(key)->second;
        }
        return std::string(); 
    }
    std::map<std::string, std::string> getRequestParams() const 
    {
        return requestParams_;
    }

    std::string getProtocol() const { return protocol_; }
    std::string getVersion() const { return version_; }
    std::map<std::string, std::string> getHeaders() const { return headers_; }

    std::string getBody() const { return body_; }
private:
    void parseInternal();
    const char* toStateString(HttpRequestDecodeState state);

    Buffer buffer_;

    std::string method_;
    std::string url_;

    std::map<std::string, std::string> requestParams_;

    std::string protocol_;
    std::string version_;

    std::map<std::string, std::string> headers_;

    std::string body_;
    HttpRequestDecodeState state_ = BEFORE_STATE;

    static char kLF;    // 换行
    static char kCR;    // 回车
};



}   // namespace zbinbin
#endif  // __ZBINBIN_HTTPREQUEST_H_