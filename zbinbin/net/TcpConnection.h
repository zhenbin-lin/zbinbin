#ifndef __ZBINBIN_TCPCONNECTION_H_
#define __ZBINBIN_TCPCONNECTION_H_


#include "zbinbin/net/Callbacks.h"
#include "zbinbin/net/InetAddress.h"
#include "zbinbin/utility/noncopyable.h"

#include <memory>
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

    void setTcpNoDelay(bool on);

private:
    /// use by TcpServer only
    friend class TcpServer;

    void setConnectionCallback(const ConnectionCallback& cb)
    { connectionCallback_ = cb; }
    // set CloseCallback use by TcpServer only
    void setCloseCallback(const CloseCallback& cb)
    { closeCallback_ = cb; }
    // called when TcpServer accepts a new connection
    void connectEstablished();  // should be called only once
    // called when TcpServer has removed me from its map
    void connectDestroyed();    // should be called only once


    EventLoop* getLoop() const { return loop_; }
    int getIdx() const { return connIdx_; }
    void setIdx(int idx) { connIdx_ = idx; }

    void handleRead();  // message arrived
    void handleWrite(); // 
    void handleError(); // connection error
    void handleClose(); // peer close
    
    EventLoop* loop_;   // TcpServer所在的loop
    const std::string name_;
    StateE state_;              // 记录连接的状态
    bool reading_;
    mutable size_t connIdx_;               // use by TcpServer
    
    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;
    const InetAddress localAddr_;
    const InetAddress peerAddr_;

    ConnectionCallback connectionCallback_;
    // MessageCallback messageCallback_;
    // WriteCompleteCallback writeCompleteCallback_;
    // HighWaterMarkCallback highWaterMarkCallback_;
    CloseCallback closeCallback_;
};



}   // namespace zbinbin
#endif  // __ZBINBIN_TCPCONNECTION_H_