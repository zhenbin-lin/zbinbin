#ifndef __ZBINBIN_CHANNEL_H_
#define __ZBINBIN_CHANNEL_H_

#include <memory>
#include <functional>

namespace zbinbin
{

class EventLoop; 

class Channel
{
public:
    using EventCallback = std::function<void()>;

    Channel(EventLoop* loop, int fd);

    void enableReading();
    void enableWriting();

    void disableReading();
    void disableWriting();

    void disableAll();

    void handleEvent();

    bool isNoneEvents() const { return events_ == kNoneEvent; }
    // return channel is writing
    bool isWriting() const { return events_ & kWriteEvent; }
    // return channel is reading
    bool isReading() const { return events_ & kReadEvent; }
    // bool isWritable() const { return revents_ & kWriteEvent; }
    // bool isReadable() const { return revents_ & kWriteEvent; }

    int getFd() const { return fd_; }
    int getEvents() const { return events_; }
    int getIndex() const { return index_; }
    const EventLoop* getOwerLoop() const { return loop_; }

    void setIndex(int index) { index_ = index; }
    void setRevents(int revents) { revents_ = revents; }

    void setReadCallback(const EventCallback& cb) { readCallback_ = cb; }
    void setWriteCallback(const EventCallback& cb) { writeCallback_ = cb; }
    void setErrorCallback(const EventCallback& cb) { errorCallback_ = cb; }
    void setCloseCallback(const EventCallback& cb) { closeCallback_ = cb; }

    void remove();

    ~Channel();

private:

    void update();

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;


    bool eventHandling_;
    bool addedToLoop_;

    EventLoop* loop_;
    const int fd_;
    int events_;
    int revents_;
    int index_;                 // used by Poller

    EventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;
    EventCallback closeCallback_;
};


inline void Channel::enableReading() 
{ 
    events_ |= kReadEvent; 
    addedToLoop_ = true;
    update();
    
}

inline void Channel::disableReading() 
{ 
    events_ &= ~kReadEvent; 
    update();
}

inline void Channel::disableWriting() 
{ 
    events_ &= ~kWriteEvent; 
    update();
}

inline void Channel::enableWriting() 
{ 
    events_ |= kWriteEvent; 
    addedToLoop_ = true;
    update();
}

inline void Channel::disableAll() 
{ 
    events_ = kNoneEvent; 
    update();
}


}   // namespace zbinbin
#endif  //__ZBINBIN_CHANNEL_H_