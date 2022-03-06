#include "zbinbin/http/HttpResponse.h"
#include "zbinbin/log/Logging.h"
#include <sys/stat.h>


using namespace zbinbin;


void HttpResponse::appendToBuffer(std::shared_ptr<Buffer>& output)
{
    const char* fileName = fileName_.c_str();
    FILE *fp = ::fopen(fileName, "rb");
    if (fp)
    {
        std::string str = "HTTP/1.1 " 
                        + std::to_string(statusCode_)
                        + " "
                        + statusMessage_;
        output->append(str.c_str(), str.size());
        output->append("\r\n", 2);

        for (const auto& header : headers_)
        {
            output->append(header.first.c_str(), header.first.size());
            output->append(": ", 2);
            output->append(header.second.c_str(), header.second.size());
            output->append("\r\n", 2);
        }

        // 读取文件的大小
        struct stat fileStat;  
        if(stat(fileName, &fileStat) < 0)  
        {  
            LOG_SYSERR << "HttpResponse::appendToBuffer " << strerror_tl(errno);
        }
        size_t size = static_cast<size_t>(fileStat.st_size);

        if (closeConnection_)
        {
            output->append("Connection: close\r\n", 19);
        }
        else
        {
            std::string contentLength = "Content-Length: " 
                            + std::to_string(size);
            // std::string str = "Content-Length: 11";
            output->append(contentLength.c_str(), contentLength.size());
            output->append("\r\n", 2);
            output->append("Connection: Keep-Alive\r\n", 24);
        }
        output->append("\r\n", 2);
        int saveErrno = 0;
        output->readFile(fileName, &saveErrno);
        // LOG_INFO << "HttpResponse::appendToBuffer completed!";
    }
    else
    {
        output->append("HTTP/1.1 404 Not Found\r\n\r\n", 26);
        setCloseConnection(true);
    }
}