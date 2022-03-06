#ifndef __ZBINBIN_TCPCONNECTION_H_
#define __ZBINBIN_TCPCONNECTION_H_


#include "zbinbin/net/Buffer.h"
#include "zbinbin/net/Callbacks.h"
#include "zbinbin/net/InetAddress.h"
#include "zbinbin/utility/noncopyable.h"

#include <memory>
#include <atomic>
#include <string>

struct tcp_info;

namespace zbinbin
{
class Socket;
class Channel;
class EventLoop;

class TcpConnection : noncopyable
                    , public std::enable_shared_from_this<TcpConnection>
{
private:
    enum StateE { kDisconnected, kConnecting, kConnected, kDisconnecting };

public:
    TcpConnection(EventLoop* loop,
                  const std::string& name,
                  int sockfd,
                  size_t connIdx,
                  const InetAddress& localAddr,
                  const InetAddress& peerAddr);
    ~TcpConnection();

    
    
    bool connected() const { return state_ == kConnected; }
    bool disconnected() const { return state_ == kDisconnected; }

    const std::string getName() const { return name_; }
    /// return a unqiue_ptr, if success
    /// reurn nullptr if failure
    const std::unique_ptr<struct tcp_info> getTcpInfo() const;
    const std::string getTcpInfoString() const;

    const InetAddress& getLocalAdrr() const { return peerAddr_; }
    const InetAddress& getPeerAdrr() const { return peerAddr_; }

    const StateE getState() const { return state_; }
    const std::string getStateString() const;

    void send(const void* message, size_t len);
    void send(std::shared_ptr<Buffer> message);
    void send(const std::string& message);

    void startRead();
    void stopRead();

    /// Nagle: Delay Ack
    void setTcpNoDelay(bool on);
    void sethighWaterMark(size_t mark) const { highWaterMark_ = mark; }

    // NOT thread safe, no simultaneous calling
    void shutdown();
    void forceClose();

private:
    /// use by TcpServer only
    friend class TcpServer;

    void setConnectionCallback(const ConnectionCallback& cb)
    { connectionCallback_ = cb; }
    void setMessageCallback(const MessageCallback& cb)
    { messageCallback_ = cb; }
    void setWriteCompleteCallback(const WriteCompleteCallback& cb)
    { writeCompleteCallback_ = cb; }
    // set CloseCallback use by TcpServer only
    void setCloseCallback(const CloseCallback& cb)
    { closeCallback_ = cb; }
    void setHighWaterMarkCallback(const HighWaterMarkCallback& cb, size_t highWaterMark)
    { highWaterMarkCallback_ = cb; highWaterMark_ = highWaterMark; }
    // called when TcpServer accepts a new connection
    void connectEstablished();  // should be called only once
    // called when TcpServer has removed me from its map
    void connectDestroyed();    // should be called only once


    EventLoop* getLoop() const { return loop_; }
    int getIdx() const { return connIdx_; }
    void setIdx(int idx) { connIdx_ = idx; }

    void startReadInLoop();
    void stopReadInLoop();
    void shutdownInLoop();
    void forceCloseInLoop();
    void sendInLoop(const void* message, size_t len);
    void sendInLoop(std::shared_ptr<Buffer> message);

    void handleRead();  // message arrived
    void handleWrite(); // writable
    void handleError(); // connection error
    void handleClose(); // peer close
    
    EventLoop* loop_;   // IO线程所在的loop
    const std::string name_;
    StateE state_;              // 记录连接的状态
    bool reading_;
    mutable size_t connIdx_;               // use by TcpServer
    
    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;
    const InetAddress localAddr_;
    const InetAddress peerAddr_;
    mutable size_t highWaterMark_;
    Buffer outputBuffer_;
    Buffer inputBuffer_;

    ConnectionCallback connectionCallback_;
    MessageCallback messageCallback_;
    WriteCompleteCallback writeCompleteCallback_;
    HighWaterMarkCallback highWaterMarkCallback_;
    CloseCallback closeCallback_;
};



}   // namespace zbinbin
#endif  // __ZBINBIN_TCPCONNECTION_H_