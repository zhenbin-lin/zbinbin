#include "zbinbin/net/TcpServer.h"
#include "zbinbin/net/EventLoop.h"
#include "zbinbin/net/TcpConnection.h"
#include <iostream>

using namespace zbinbin;
using namespace std;


void onConnection(const TcpConnectionPtr& conn)
{
    if (conn->connected())
    {
        std::cout << "A new Tcp Connection " << conn->getName() << std::endl;
    } 
    else
    {
        std::cout << "Tcp Connection " << conn->getName() << " close" << std::endl;
    }
}




int main()
{
    EventLoop loop;
    InetAddress listAddr(40000);
    TcpServer server(&loop, listAddr, "main server", TcpServer::kReusePort);
    server.setConnectionCallback(onConnection);
    server.start();

    loop.loop();


}