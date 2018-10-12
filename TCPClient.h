#ifndef INCLUDED_CLIENTSOCKET
#define INCLUDED_CLIENTSOCKET

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <string>
#include <sstream>
#include <Order.h>
#include <cstdlib>

using boost::asio::ip::tcp;

class TCPClient 
{
    std::string   d_server;
    std::string   d_port;
    std::string   d_clientID;
    tcp::socket   d_socket;
    tcp::resolver d_resolver;
    int           d_orderID;
    
    void onConnect();
        // Utility function prints a message and sends a greeting identification
        // to the server if the connection is successful.
    
    const std::string& onError(boost::system::error_code &ec) const;
        // Provides error handling on boost/asio socket functions.

public:
    TCPClient(boost::asio::io_service& io_service, const std::string& server, 
              const std::string& port, const std::string& clientID);
        // Creates a TCP client socket with the arguments given to the c'tor.
        // Client program must provide the name of server, port number, client 
        // ID, and an io_service object.
    
    void connectToServer();
        // Connects to the server
    
    void sendMessage(const std::string& message);
        // Sends the server a custom message.
    
    void sendNewOrder( const Order& order );
        // Sends an Order to the server once connection is established
    
    void receive();
        // Reads a response from the server.
    
    void onExit();
        // Sends a quit message to the server when client is finished sending
        // data.

    std::string genOrderID();
        // (One of the tasks was to generate orderID's automatically)
};

inline
TCPClient::TCPClient(boost::asio::io_service& io_service, const std::string& server,
                     const std::string& port, const std::string& clientID)
  : d_server( server )
  , d_port( port )
  , d_clientID( clientID )
  , d_socket( io_service )
  , d_resolver( io_service )
  , d_orderID( 0 )
{ // Creates socket and resolves server name.
}

inline const std::string& TCPClient::onError(boost::system::error_code &ec) const {
    std::string errorMsg;
    if (ec) {
        errorMsg = ec.message();
        std::cerr << "[CLIENT] Error: " << errorMsg << std::endl;
    }
    else
        errorMsg = "None";
    
    return errorMsg;
}

inline std::string TCPClient::genOrderID() {
    std::ostringstream ostream;
    ostream << ++d_orderID;
    return ostream.str();
}

#endif
