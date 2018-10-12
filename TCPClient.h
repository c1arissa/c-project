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

public:
    TCPClient(boost::asio::io_service& io_service, const std::string& server, 
              const std::string& port, const std::string& clientID);
        // Construct client TCP application and create a client socket.  Driver
        // program must provide the name of the server (hostname), a port
        // number, a client ID, and an io_service object.
    
    void connectToServer();
        // Connects to the server
    
    //void receiveData();
    
    void sendMessage(const std::string& message);
        // Sends the server a custom message.
    
    void sendNewOrder( const Order& order );
        // Sends an Order to the server once connection is established
    
    std::string genOrderID();
        // (One of the tasks was to generate orderID's automatically)
    
    //void teardown();
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

inline std::string TCPClient::genOrderID() {
    std::ostringstream ostream;
    ostream << ++d_orderID;
    return ostream.str();
}

    /** WHILE LOOP INSTEAD OF INFINITE FOR + BREAK **
    for (;;) {
        boost::array<char, 128> buf;
        boost::system::error_code error;
        size_t bufLen = socket.read_some(boost::asio::buffer(buf), error);
        // Exit the loop when read_some() exits with the boost::asio::error::eof
        // error when the server closes the connection.
        if (error == boost::asio::error::eof)
            break; // Connection closed cleanly by peer.
        else if (error)
            throw boost::system::system_error(error); // Other error.
        std::cout.write(buf.data(), bufLen);
    } 

void TCPClient::receiveData() {
    // Reads a response from the server.
    boost::system::error_code error;
    
    while (error != boost::asio::error::eof) {
        // Use a char boost::array to hold the received data.
        boost::array<char, 128> buf;
        
        // read_some() exits with boost::asio::error::eof when the
        // server closes the connection.
        size_t bufLen = d_socket.read_some(boost::asio::buffer(buf), error);
        
        std::cout.write(buf.data(), bufLen);
    }
}
*/
/*void TCPClient::teardown() {
    std::cout<< "Logging out\n";
    clientMessageWriter("QUIT");
}
*/
#endif
