#ifndef __ZBINBIN_ACCEPTOR_H_
#define __ZBINBIN_ACCEPTOR_H_

#include "zbinbin/utility/copyable.h"
#include "zbinbin/net/InetAddress.h"


#include <string>
#include <functional>



namespace zbinbin
{
namespace net
{

class EventLoop;
class Channel;


class Acceptor
{
public:
    typedef std::function<void()> NewConnectionCallback;

    Acceptor();
    ~Acceptor();
private:

    bool listening_;

    EventLoop* loop_;
    Socket acceptSocket_;
    Channel acceptChannel_;
    NewConnectionCallback newConnectCallback_;

};


}   // namespace net
}   // namespace zbinbin

#endif