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
    TCPClient(const std::string& server, const std::string& port, 
              const std::string& clientID, boost::asio::io_service& io);
        // Construct client TCP application and create a client socket.  Driver
        // program must provide the name of the server (hostname), a port
        // number, a client ID, and an io_service object.
    
    void connect();
        // Connects to the server
    
    void sendNewOrder( const Order& order );
        // Sends an Order to the server once connection is established
    
    std::string genOrderID();
        // (One of the tasks was to generate orderID's automatically)

    void clientMessageWriter(const std::string& message) const;
        // Sends the server a custom message.
    
    boost::array<char, 128> clientMessageReader();

    void teardown();

    void reportErrorMessage();
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
    // Creates socket and resolves server name.
}

inline std::string TCPClient::genOrderID() {
    std::ostringstream ostream;
    ostream << ++d_orderID;
    return ostream.str();
}

void TCPClient::clientMessageWriter(const std::string& message) const {
    boost::array<char, 128> buf;
    std::copy(message.begin(), message.end(), buf.begin());
    
    // TASK WAS TO ADD ERROR CHECKING.  Checking is added.  Just need to lookup
    // some of the error codes to throw etc.
    boost::system::error_code error;
    boost::asio::write(d_socket, boost::asio::buffer(message), error);
}

void TCPClient::connect() {
    //tcp::resolver resolver(io_service); // Turn the server name into a TCP endpoint.

    // Return list of TCP endpoints as an iterator.
    tcp::resolver::query query( d_server, d_port );
    tcp::resolver::iterator endpoint_iterator = d_resolver.resolve( query );

    // Connect the socket to the list of tcp endpoints.
    //tcp::socket socket(io_service);
    std::cout<< "[CLIENT] Connecting to server: " << d_server << ":" << d_port<< "\n";
    boost::asio::connect(d_socket, endpoint_iterator);

    boost::system::error_code error;
    if (!error) {
        // Established connection successfully.
        std::cout<< "[CLIENT] Connected.\n"
            << "[CLIENT] Logging in as " << d_clientID << " ...\n";
        
        // Send a custom greeting to the server.
        clientMessageWriter("HELLO_I_AM " + d_clientID);
    } 
    else {
        // An error occured. Not connected.
        std::cerr << error.message() << "\n";
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
}

boost::array<char, 128> TCPClient::clientMessageReader() {
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


void TCPClient::teardown() {
    std::cout<< "Logging out\n";
    clientMessageWriter("QUIT");
}

void TCPClient::sendNewOrder( const Order& order ) {    
    boost::system::error_code error;
        
    // Dumps the new Order object for logging/debugging.
    std::cout<< "[CLIENT] Sending order " << genOrderID() << " " << order.toString() << "\n";

    //[DONE] TASK change the protocol to include the order id     
    //[DONE] TASK change the protocol to FIX
    boost::asio::write(d_socket, boost::asio::buffer("NEW_ORDER" + order.serialise()), error);
}

#endif
