#ifndef INCLUDED_SERVERSOCKET
#define INCLUDED_SERVERSOCKET

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>
//#include <boost/thread.hpp>
#include <thread>
#include <vector>
#include <ConnectionHandler.h>

using boost::asio::ip::tcp;

class TCPServer 
{
    std::string   d_host;
    std::string   d_port;
    tcp::socket   d_socket;
    tcp::acceptor d_acceptor;
    int           d_clientNum;
    
public:
    TCPServer(boost::asio::io_service& io_service, const std::string& host, const std::string& port);
        // Creates a TCP server socket with the parameters passed to the c'tor.
        // Socket binds to the 'host':'port' and begins listening for incoming
        // client connections. Client program must pass an io_service object.

    void acceptConnection();
        // Accepts incoming connections and adds session to a thread handling vector.
    
    void sendResponse(const std::string& message);
        // Send a message to the client program.
    
    std::string make_daytime_string();
        // Constructs a response with the current time.
    
    void handleConnection();
        // Handles active threads.
};

inline
TCPServer::TCPServer(boost::asio::io_service& io_service, const std::string& host, 
                     const std::string& port)
  : d_host( host )
  , d_port( port )
  , d_socket( io_service )
  , d_acceptor( io_service, tcp::endpoint(tcp::v4(), 3000) )
  , d_clientNum( 0 )
{
    std::cout << "[SERVER] Started server listening on localhost:3000\n"; 
}

inline std::string TCPServer::make_daytime_string() {
    std::time_t now = std::time(0);
    return std::ctime(&now);
}

#endif
