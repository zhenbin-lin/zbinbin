#include "zbinbin/http/HttpRequest.h"
#include "zbinbin/log/Logging.h"

#include <algorithm>
#include <string>
#include <ctype.h>
#include <memory>

using namespace zbinbin;

char HttpRequest::kLF = '\n';
char HttpRequest::kCR = '\r';

HttpRequest::HttpRequest()
{
}

HttpRequest::~HttpRequest()
{
}

bool HttpRequest::parseRequest(Buffer* buffer)
{
    state_ = BEFORE_STATE;
    const char* begin = buffer->peek();
    const char* cur = begin;
    // HttpRequestDecodeState errorState ;
    std::string key;
    std::string val;
    bool hasMore = true;
    bool ok = true;
    
    while (hasMore)
    {
        // const char* begin = cur;
        switch(state_)
        {
            case BEFORE_STATE:
            {
                state_ = METHOD;
                while (::isupper(*cur))
                {
                    ++cur;
                }
                if (::isblank(*cur))  // 空格，说明方法解析结束，下一步开始解析URI
                {
                    state_ = BEFORE_URI;
                    method_ = buffer->retrieveAsString(cur - begin);
                    begin = cur;
                }
                else
                {
                    state_ = INVALID_METHOD;   
                }
                break;
            }
            case BEFORE_URI:
            {
                while (::isblank(*cur))
                {
                    ++cur;
                }
                if (*cur == '/')
                {
                    buffer->retrieve(cur - begin);    // 清除掉空格
                    begin = cur;
                    state_ = IN_URI;
                }
                else
                {
                    state_ = INVALID;
                    // errorState = INVALID_URI;
                }
                break;
            }
            case IN_URI:
            {
                while (!::isblank(*cur) && *cur != '?' && !(kLF == *cur || kCR == *cur))
                {
                    ++cur;
                }
                if (::isblank(*cur)) // 协议 eg: HTTP/1.1
                { 
                    state_ = BEFORE_PROTOCOL;
                }   
                else if (*cur == '?') // url后面的参数
                { 
                    state_ = BEFORE_URI_PARAM_KEY; 
                }    
                else // 错误
                { 
                    state_ = INVALID_URI; 
                    break; 
                }  
                url_ = buffer->retrieveAsString(cur - begin);
                begin = cur;
                break;
            }
            case BEFORE_URI_PARAM_KEY:  // ? 或者 &
            {
                cur++;
                if (::isblank(*cur) || kLF == *cur || kCR == *cur)
                {
                    state_ = INVALID_URI;
                    break;
                }
                buffer->retrieve(1);    // 清除掉'?' 或者 '&'
                begin = cur;
                state_ = URI_PARAM_KEY;
                break;
            }
            case URI_PARAM_KEY:
            {
                while (*cur != '=')
                {
                    ++cur;
                }
                key = buffer->retrieveAsString(cur - begin);
                state_ = BEFORE_URI_PARAM_VALUE;
                begin = cur;
                break;
            }
            case BEFORE_URI_PARAM_VALUE:
            {
                ++cur;
                if (::isblank(*cur) || kLF == *cur || kCR == *cur)
                {
                    state_ = INVALID;
                }
                else
                {
                    buffer->retrieve(1);    // 清除掉'='
                    begin = cur;
                    state_ = URI_PARAM_VALUE;
                }
                break;
            }
            case URI_PARAM_VALUE:
            {
                while (!::isblank(*cur) && *cur != '&')
                {
                    ++cur;
                }
                if (isblank(*cur))
                {
                    state_ = BEFORE_PROTOCOL;
                } else if (*cur == '&') {
                    state_ = BEFORE_URI_PARAM_KEY;
                } /* else {
                    state_ = INVALID;
                } */
                requestParams_[key] = buffer->retrieveAsString(cur - begin);
                key.clear();
                begin = cur;
                break;
            }
            case BEFORE_PROTOCOL:
            {
                while (::isblank(*cur))
                {
                    ++cur;
                }
                if (!::isupper(*cur))
                {
                    state_ = INVALID;
                }
                else
                {
                    buffer->retrieve(cur - begin);
                    begin = cur;
                    state_ = PROTOCOL;
                }
                break;
            }
            case PROTOCOL:
            {
                while (::isalnum(*cur))  // 协议由 字母或者数字组成 (!!是否应该支持其它字符？？)
                {
                    ++cur;
                }
                if (*cur != '/')
                {
                    state_ = INVALID_PROTOCOL;
                }
                else
                {
                    protocol_ = buffer->retrieveAsString(cur - begin);
                    begin = cur;
                    state_ = BEFORE_VERSION;    // 版本号
                }
                break;
            }
            case BEFORE_VERSION:
            {
                ++cur;
                if (::isdigit(*cur))
                {
                    state_ = VERSION;
                    buffer->retrieve(1);    // 清除掉'/'
                    begin = cur;
                }
                else
                {
                    state_ = INVALID_VERSION;
                }
                break;
            }
            case VERSION:
            {
                while (::isdigit(*cur) || *cur == '.')
                {
                    ++cur;
                }
                if (*cur != kCR)
                {
                    state_ = INVALID;
                }
                else
                {
                    version_ = buffer->retrieveAsString(cur - begin);
                    begin = cur;
                    state_ = WHEN_CR;
                }
                break;
            }
            case WHEN_CR:
            {
                cur++;
                if (*cur == kLF)
                {
                    state_ = CR_LF;
                    buffer->retrieve(1); // 清除掉 CR
                    begin = cur;
                }
                else
                {
                    state_ = INVALID;
                }
                break;
            }
            case CR_LF:
            {
                cur++;
                if (*cur == kCR)
                {
                    state_ = CR_LF_CR;
                }
                else    // 解析 headers
                {
                    state_ = HEADER_KEY;
                }
                buffer->retrieve(1);    // 清除掉 LF
                begin = cur;
                break;
            }
            case HEADER_KEY:
            {
                while (!::isblank(*cur) && *cur != ':')
                {
                    cur++;
                }
                if (*cur == ':')
                {
                    state_ = HEADER_COLON;
                }
                else   // : 之前有空格
                {
                    state_ = BEFORE_HEADER_COLON;
                }
                key = buffer->retrieveAsString(cur - begin);
                begin = cur;
                break;
            }
            case BEFORE_HEADER_COLON:
            {
                while (::isblank(*cur))
                {
                    ++cur;
                }
                if (*cur == ':')
                {
                    state_ = HEADER_COLON;
                    buffer->retrieve(cur - begin);
                    begin = cur;
                }
                else
                {
                    state_ = INVALID_HEADER;
                }
                break;
            }
            case HEADER_COLON:
            {
                cur++;
                while (::isblank(*cur))  // 清除:之后的空格
                {
                    ++cur;
                }
                buffer->retrieve(cur - begin);
                begin = cur;
                state_ = HEADER_VALUE;
                break;
            }
            case HEADER_VALUE:
            {
                while (*cur != kCR)
                {
                    ++cur;
                }
                headers_[key] = buffer->retrieveAsString(cur - begin);
                begin = cur;
                state_ = WHEN_CR;
                break;
            }
            case CR_LF_CR:
            {
                cur++;
                if (*cur == kLF)
                {
                    buffer->retrieve(1);    // 清除掉 CR
                    state_ = CR_LF_CR_LF;
                    begin = cur;
                }
                else
                {
                    state_ = INVALID;
                }
                break;
            }
            case CR_LF_CR_LF:
            {
                buffer->retrieve(1);    // 清除掉 LF
                if (buffer->readableBytes() > 0) // 还有body
                {
                    cur++;
                    begin = cur;
                    state_ = BODY;
                }
                else
                {
                    state_ = COMPLETE;
                    cur = begin = nullptr;
                }
                break;
            }
            case BODY:
            {
                body_ = buffer->retrieveAllAsString();
              cur = begin = nullptr;
                hasMore = false;
                break;
            }
            case COMPLETE:
            {
                LOG_TRACE << "HttpRequest::parseInternal completed!";
                cur = begin = nullptr;
                hasMore = false;
                break;
            }
            case INVALID_PROTOCOL:
            case INVALID:
            case INVALID_METHOD:
            case INVALID_URI:
            case INVALID_VERSION:
            case INVALID_HEADER:
            {
                LOG_ERROR << "HttpRequest::parseInternal: parse error "
                          << toStateString(state_) 
                          << " near "
                          << "\"" 
                          << buffer->retrieveAsString(
                              std::min(static_cast<size_t>(30), buffer->readableBytes())) << "\"";
                buffer->retrieveAll();  // 清空buffer
                cur = begin = nullptr;
                hasMore = false;
                ok = false;
                break;
            }
            default:
            {
                LOG_ERROR << "HttpRequest::parseInternal: parse error unkown state! ";
                cur = begin = nullptr;
                hasMore = false;
                ok = false;
                break;
            }
        }
    }   // while (hasMore)
    return ok;
}

const char *HttpRequest::toStateString(HttpRequestDecodeState state)
{
    static const char* stateString[HttpRequestDecodeStateLength] = 
    {
        "BEFORE_STATE",
        "INVALID_METHOD",
        "METHOD",

        "BEFORE_URI",
        "IN_URI",

        "BEFORE_URI_PARAM_KEY",
        "URI_PARAM_KEY",
        "BEFORE_URI_PARAM_VALUE",
        "URI_PARAM_VALUE",
        "INVALID_URI",
        
        "BEFORE_PROTOCOL",
        "INVALID_PROTOCOL",
        "PROTOCOL",

        "BEFORE_VERSION",
        "VERSION",
        "INVALID_VERSION",

        "WHEN_CR",
        "CR_LF",
        "CR_LF_CR",
        "CR_LF_CR_LF",    // header到body的过度

        "HEADER_KEY",
        "BEFORE_HEADER_COLON",    // header和:之间的空格
        "HEADER_COLON",
        "HEADER_VALUE",
        "INVALID_HEADER",

        "COMPLETE",
        "BODY",
        "INVALID",
    };

    return stateString[state];
}

// "POST /audiolibrary/music?ar=1595301089068&n=1p1 HTTP/1.1\r\n"
// 		"Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, application/x-silverlight, application/x-shockwave-flash\r\n"
// 		"Referer: http://www.google.cn\r\n"
// 		"Accept-Language: zh-cn\r\n"
// 		"Accept-Encoding: gzip, deflate\r\n"
// 		"User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727; TheWorld)\r\n"
// 		"content-length:28\r\n"
// 		"Host: www.google.cn\r\n"
// 		"Connection: Keep-Alive\r\n"
// 		"Cookie: PREF=ID=80a06da87be9ae3c:U=f7167333e2c3b714:NW=1:TM=1261551909:LM=1261551917:S=ybYcq2wpfefs4V9g; NID=31=ojj8d-IygaEtSxLgaJmqSjVhCspkviJrB6omjamNrSm8lZhKy_yMfO2M4QMRKcH1g0iQv9u\r\n"
// 		"\r\n"
// 		"hl=zh-CN&source=hp&q=domety";