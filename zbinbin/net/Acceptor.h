#ifndef __ZBINBIN_ACCEPTOR_H_
#define __ZBINBIN_ACCEPTOR_H_

#include "zbinbin/utility/noncopyable.h"
#include "zbinbin/net/Channel.h"
#include "zbinbin/net/Socket.h"

#include <string>
#include <functional>

namespace zbinbin
{
class EventLoop;
class InetAddress;

class Acceptor : public noncopyable
{
public:
    using NewConnectionCallback = std::function<void(int sockfd, const InetAddress&)> ;

    Acceptor(EventLoop* loop, const InetAddress& listenAdrr, bool resuseport);
    ~Acceptor();

    void setNewConnectionCallback(const NewConnectionCallback& cb) { newConnectCallback_ = cb; }

    void listen();

    bool listening() const { return listening_; }

private:

    void handleRead();

    bool listening_;

    EventLoop* loop_;
    Socket acceptSocket_;
    Channel acceptChannel_;
    NewConnectionCallback newConnectCallback_;
    int idleFd_;
};


}   // namespace zbinbin

#endif