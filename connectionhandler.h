#ifndef ConnectionHandler_h_
#define ConnectionHandler_h_

#include <thread>
#include <deque>
#include <string>
#include <mutex>

class ConnectionHandler {
private:
  std::deque< std::string > queue_;
  std::thread thread_;
  bool quitReceived_;
  std::mutex mutex_;
  std::string userIdentifiedAs_;

        
  void processMessages();
public:
  //Starts a new connection by spawning a new thread
  void start();
  
  //Pushes a message onto the end of the queue
  void queueMessage( const char* buffer, size_t length );
  
  //Returns whether or not quit was received
  bool quitReceived() const;
  
  
  void join();
};

#endif // ConnectionHandler_h_
