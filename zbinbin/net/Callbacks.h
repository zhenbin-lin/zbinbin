#ifndef __ZBINBIN_CALLBACKS_H_
#define __ZBINBIN_CALLBACKS_H_
#include <functional>
#include <memory>

namespace zbinbin
{
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

// All client visible callbacks go here.

class Buffer;
class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

typedef std::function<void()> TimerCallback;
typedef std::function<void (const TcpConnectionPtr&)> ConnectionCallback;
// typedef std::function<void ()> ConnectionCallback;
typedef std::function<void (const TcpConnectionPtr&)> CloseCallback;
// typedef std::function<void (const TcpConnectionPtr&)> WriteCompleteCallback;
// typedef std::function<void (const TcpConnectionPtr&, size_t)> HighWaterMarkCallback;

// // the data has been read to (buf, len)
// typedef std::function<void (const TcpConnectionPtr&,
//                             Buffer*,
//                             Timestamp)> MessageCallback;

// void defaultConnectionCallback(const TcpConnectionPtr& conn);
// void defaultMessageCallback(const TcpConnectionPtr& conn,
//                             Buffer* buffer,
//                             Timestamp receiveTime);

}  // namespace zbinbin

#endif  // __ZBINBIN_CALLBACKS_H_