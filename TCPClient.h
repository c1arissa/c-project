#ifndef INCLUDED_CLIENTSOCKET
#define INCLUDED_CLIENTSOCKET

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <string>
#include <sstream>
#include <order.h>
#include <cstdlib>
using boost::asio::ip::tcp;


class TCPClient 
{
    std::string   d_server;
    std::string   d_port;
    std::string   d_clientID;
    tcp::socket   d_socket;
    tcp::resolver d_resolver;
    int           d_orderID;  // make static to preserve value ??

public:
    TCPClient(const std::string& server, const std::string& port, 
              const std::string& clientID, boost::asio::io_service& io);
    
    void connect();
        // Connects to the server.  Have function return error codes.
    
    void sendNewOrder( tcp::socket& socket, const Order& order );
        // Send data to server once connection is established.
    
    std::string genOrderID();

    void clientMessageWriter(const std::string& message) const;

};

inline
TCPClient::TCPClient(const std::string& server, const std::string& port, 
                     const std::string& clientID, boost::asio::io_service &io)
    : d_server( server )
    , d_port( port )
    , d_clientID( clientID )
    , d_socket( io )
    , d_resolver( io )
    , d_orderID( 0 )
{
}

inline std::string genOrderID () {
    std::stringstream stream;
    stream << ++d_orderID;
    return stream.str();
}

void TCPClient::clientMessageWriter(const std::string& message) const {
    // ADD ERROR CHECKING
    boost::system::error_code error;
    boost::asio::write(d_socket, boost::asio::buffer(message), error);
}

void TCPClient::connect() {
    // io_service object provides access to I/O functionality.
    //boost::asio::io_service io_service;
    // Turn the server name into a TCP endpoint.
    //tcp::resolver resolver(io_service);
    
    // Turn query into a list of endpoints using the name of
    // the server specified in c'tor.
    tcp::resolver::query query( d_server, d_port );
    // Return list of endpoints as an iterator.
    tcp::resolver::iterator endpoint_iterator = d_resolver.resolve(query);

    // Create and connect the socket to the list of endpoints.
    //tcp::socket socket(io_service);
    std::cout<< "Connecting to server: " << d_server << ":" << d_port<< "\n";
    boost::asio::connect(d_socket, endpoint_iterator);

    // The connection is open.  Now, read the response from the service.
    
    /* ------------------------ *
     * TASK don't ignore errors *
     * ------------------------ */
            
    std::cout<< "Logging in\n";
    clientMessageWriter("HELLO_I_AM " + d_clientID);

    //message = "HELLO_I_AM " + d_clientID;
    //boost::system::error_code ignored_error; //TASK don't ignore errors
    //boost::asio::write(socket, boost::asio::buffer(message), error);

    sendNewOrder(socket);

    boost::system::error_code error;
    while (error != boost::asio::error::eof) {
        // Use a char boost::array to hold the received data.
        boost::array<char, 128> buf;
        
        // read_some() exits with boost::asio::error::eof when the
        // server closes the connection.
        size_t bufLen = socket.read_some(boost::asio::buffer(buf), error);
        
        std::cout.write(buf.data(), bufLen);
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
    } */
    
    std::cout<<"Logging out\n";
    clientMessageWriter("QUIT");
    
    //message = "QUIT ";
    //boost::system::error_code ignored_error;
    //boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
}

void TCPClient::sendNewOrder( tcp::socket& socket, const Order& order ) { 
    
    // Automate client to send messages
	std::cout<<"sleep 5\n";
	sleep(5);
	for (int i = 0; i < (10+rand() % 100); ++i) { 
	    //TASK have the server respond to the client with fill messages
	    sendNewOrder( socket );
		sleep(10); //TASK make random between 0.1s and 3s
	}

    
    boost::system::error_code ignored_error;
        
    /* Provide Order as a parameter versus creating new object here ?? */

    // int instIndex=orderId%2;
    // Order newOrder( { instruments[instIndex], Order::Buy, sizes[instIndex], benchmarkPrices[instIndex]} ); //TODO make the numbers random
    
    std::cout<<"Sending order "<<orderId++<<" "<<newOrder.toString()<<"\n";

    //TASK change the protocol to include the order id
    //TASK change the protocol to FIX
    boost::asio::write(socket, boost::asio::buffer("NEW_ORDER" + newOrder.serialise()), ignored_error);
}

#endif