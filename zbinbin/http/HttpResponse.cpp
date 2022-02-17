#include "zbinbin/http/HttpResponse.h"


using namespace zbinbin;


void HttpResponse::appendToBuffer(Buffer* output) const
{
    std::string str = "HTTP/1.1 " 
                    + std::to_string(statusCode_)
                    + " "
                    + statusMessage_;
    output->append(str.c_str(), str.size());
    output->append("\r\n", 2);


    if (closeConnection_)
    {
        output->append("Connection: close\r\n", 19);
    }
    else
    {
        std::string str = "Content-Length: " 
                        + std::to_string(bodyLen_);
        output->append(str.c_str(), str.size());
        output->append("\r\n", 2);
        output->append("Connection: Keep-Alive\r\n", 24);
    }

    for (const auto& header : headers_)
    {
        output->append(header.first.c_str(), header.first.size());
        output->append(": ", 2);
        output->append(header.second.c_str(), header.second.size());
        output->append("\r\n", 2);
    }

    output->append("\r\n", 2);
    output->append(body_, bodyLen_);
}