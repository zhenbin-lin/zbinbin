#include "zbinbin/http/HttpRequest.h"
#include "zbinbin/log/Logging.h"

#include <algorithm>
#include <string>
#include <ctype.h>
#include <memory>

using namespace zbinbin;

char HttpRequest::kLF = '\n';
char HttpRequest::kCR = '\r';

HttpRequest::HttpRequest(Buffer& lhs)
{
    buffer_.swap(lhs);
    parseInternal();
}

HttpRequest::~HttpRequest()
{
    
}


void HttpRequest::parseInternal()
{
    state_ = BEFORE_STATE;
    const char* begin = buffer_.peek();
    const char* cur = begin;
    // HttpRequestDecodeState errorState ;
    std::string key;
    std::string val;
    bool hasMore = true;
    
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
                    method_ = buffer_.retrieveAsString(cur - begin);
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
                    buffer_.retrieve(cur - begin);    // 清除掉空格
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
                url_ = buffer_.retrieveAsString(cur - begin);
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
                buffer_.retrieve(1);    // 清除掉'?' 或者 '&'
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
                key = buffer_.retrieveAsString(cur - begin);
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
                    buffer_.retrieve(1);    // 清除掉'='
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
                requestParams_[key] = buffer_.retrieveAsString(cur - begin);
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
                    buffer_.retrieve(cur - begin);
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
                    protocol_ = buffer_.retrieveAsString(cur - begin);
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
                    buffer_.retrieve(1);    // 清除掉'/'
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
                    version_ = buffer_.retrieveAsString(cur - begin);
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
                    buffer_.retrieve(1); // 清除掉 CR
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
                buffer_.retrieve(1);    // 清除掉 LF
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
                key = buffer_.retrieveAsString(cur - begin);
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
                    buffer_.retrieve(cur - begin);
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
                buffer_.retrieve(cur - begin);
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
                headers_[key] = buffer_.retrieveAsString(cur - begin);
                begin = cur;
                state_ = WHEN_CR;
                break;
            }
            case CR_LF_CR:
            {
                cur++;
                if (*cur == kLF)
                {
                    buffer_.retrieve(1);    // 清除掉 CR
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
                buffer_.retrieve(1);    // 清除掉 LF
                if (buffer_.readableBytes() > 0) // 还有body
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
                body_ = buffer_.retrieveAllAsString();
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
                          << buffer_.retrieveAsString(
                              std::min(static_cast<size_t>(30), buffer_.readableBytes())) << "\"";
                buffer_.retrieveAll();  // 清空buffer
                cur = begin = nullptr;
                hasMore = false;
                break;
            }
            default:
            {
                LOG_ERROR << "HttpRequest::parseInternal: parse error unkown state! ";
                cur = begin = nullptr;
                hasMore = false;
                break;
            }
        }
    }   // while (hasMore)
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