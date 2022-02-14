#include "zbinbin/net/TcpServer.h"
#include "zbinbin/net/EventLoop.h"
#include "zbinbin/net/InetAddress.h"
#include "zbinbin/net/TcpConnection.h"
#include "zbinbin/thread/Thread.h"
#include "zbinbin/log/Logging.h"

#include <utility>
#include <stdio.h>
#include <unistd.h>

using namespace zbinbin;
using namespace std;


int numThreads = 0;

class EchoServer
{
 public:
  EchoServer(EventLoop* loop, const InetAddress& listenAddr)
    : loop_(loop),
      server_(loop, listenAddr, "EchoServer")
  {
    server_.setConnectionCallback(
        std::bind(&EchoServer::onConnection, this, _1));
    server_.setMessageCallback(
        std::bind(&EchoServer::onMessage, this, _1, _2));
    // server_.setThreadNum(numThreads);
  }

  void start()
  {
    server_.start();
  }
  // void stop();

 private:
  void onConnection(const TcpConnectionPtr& conn)
  {
    LOG_TRACE << conn->getPeerAdrr().getIpPortString() << " -> "
        << conn->getLocalAdrr().getIpPortString() << " is "
        << (conn->connected() ? "UP" : "DOWN"); 
    LOG_INFO << conn->getTcpInfoString();
    if (conn->connected())
        conn->send("hello\n");
  }

  void onMessage(const TcpConnectionPtr& conn, Buffer* buf)
  {
    string msg(102400, 'a'); 
    // string msg(buf->retrieveAllAsString());
    LOG_TRACE << conn->getName() << " recv " << msg.size() << " bytes";
    if (msg == "exit\n")
    {
      conn->send("bye\n");
      conn->shutdown();
    }
    if (msg == "quit\n")
    {
      loop_->quit();
    }

    conn->send(msg);
  }

  EventLoop* loop_;
  TcpServer server_;
};

int main(int argc, char* argv[])
{
  LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
  LOG_INFO << "sizeof TcpConnection = " << sizeof(TcpConnection);
  EventLoop loop;
  InetAddress listenAddr(40000);
  EchoServer server(&loop, listenAddr);

  server.start();

  loop.loop();
}

