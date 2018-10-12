#include <TCPClient.h>
using boost::asio::ip::tcp;

void TCPClient::connectToServer() {
    // Resolve hostnames and return list of TCP endpoints as an iterator.
    tcp::resolver resolver(d_io_service);
    tcp::resolver::query query(d_server, d_port);
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    // Connect the socket to the list of tcp endpoints.
    std::cout<< "[CLIENT] Connecting to server: " << d_server << ":" << d_port;
    boost::asio::connect(d_socket, endpoint_iterator);

    boost::system::error_code error;
    if (!error) {
        // Established connection successfully.
        std::cout << " ... Success.\n" << "[CLIENT] Logging in as " << d_clientID << "\n";
    } 
    else {
        // Connection failed.
        std::cout << " ... Failed.\n";  
        std::cerr << error.message() << "\n";
    }
    
    // Send a custom greeting to the server.
    //clientMessageWriter("HELLO_I_AM " + d_clientID);
    boost::system::error_code ignored_error; //TASK don't ignore errors
    boost::asio::write(d_socket, boost::asio::buffer(std::string("HELLO_I_AM ") + d_clientID), ignored_error);
}


//void TCPClient::sendMessage(const std::string& message) const {
    //boost::array<char, 128> buf;
    //std::copy(message.begin(), message.end(), buf.begin());
    
    // TASK WAS TO ADD ERROR CHECKING.  Checking is added.  Just need to lookup
    // some of the error codes to throw etc.
    //boost::system::error_code error;
    //boost::asio::write(d_socket, boost::asio::buffer(message), error);
//}

void TCPClient::sendNewOrder( const Order& order ) {    
    boost::system::error_code error;
        
    // Dumps the new Order object for logging/debugging.
    std::cout<< "[CLIENT] Sending order " << genOrderID() << " " << order.toString() << "\n";

    //[DONE] TASK change the protocol to include the order id     
    //[DONE] TASK change the protocol to FIX
    boost::asio::write(d_socket, boost::asio::buffer("NEW_ORDER" + order.serialise()), error);
}

