#include "zbinbin/net/TcpServer.h"
#include "zbinbin/net/EventLoop.h"

int main()
{
    using namespace zbinbin;
    EventLoop loop;
    InetAddress listAddr(40000);
    TcpServer server(&loop, listAddr, "main server", TcpServer::kReusePort);
    server.start();

    loop.loop();


}