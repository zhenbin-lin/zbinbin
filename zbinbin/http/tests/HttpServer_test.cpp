#include "zbinbin/http/HttpServer.h"
#include "zbinbin/net/EventLoop.h"
#include "zbinbin/http/HttpRequest.h"
#include "zbinbin/http/HttpResponse.h"
#include "zbinbin/net/InetAddress.h"
#include "zbinbin/log/Logging.h"




using namespace zbinbin;

void getCallback(const HttpRequest& request, HttpResponse& response)
{
    if (request.getUrl() == "/")
    {

    }
}


int main()
{
    EventLoop loop;
    HttpServer server(&loop, InetAddress(80));

    server.setComputeThreadNum(8);
	server.setIoThreadNum(4);
    server.setGetCallback(getCallback);
    server.start();



    loop.loop();

    return 0;
}
