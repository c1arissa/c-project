#ifndef INCLUDED_CONNECTIONHANDLER
#define INCLUDED_CONNECTIONHANDLER

#include <thread>
#include <deque>
#include <string>
#include <mutex>

class ConnectionHandler {
    std::deque<std::string> d_queue;
    std::thread             d_thread;
    bool                    d_quitReceived;
    std::mutex              d_mutex;
    std::string             d_userIdentifiedAs;
    size_t                  d_numOfOrders;
    
    void processMessages();
        // Process messages from client based on the contents.
        
public:
    ConnectionHandler() = default;

    void start();
        // Spawn a new connection thread.
    
    void queueMessage( const char* buffer, size_t length );
        // Push a message onto the end of the queue.
    
    bool quitReceived() const;
        // Returns whether or not quit was received.
    
    void join();
        // Implements thread.join() function.
};

inline bool ConnectionHandler::quitReceived() const {
  return d_quitReceived;
}

#endif // ConnectionHandler_h_
