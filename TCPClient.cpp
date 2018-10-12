#include <TCPClient.h>

void TCPClient::connectToServer() {
    // Resolve hostnames and return list of TCP endpoints as an iterator.
    tcp::resolver::query query(d_server, d_port);
    tcp::resolver::iterator endpoint_iterator = d_resolver.resolve(query);

    // Connect the socket to the list of tcp endpoints.
    std::cout<< "[CLIENT] Connecting to server: " << d_server << ":" << d_port;

    try {
        boost::asio::connect(d_socket, endpoint_iterator);
    }
    catch (boost::system::system_error const& e) {
        std::cout << "Error: could not connect: " << e.what() << std::endl;
    }
    
    // Established connection successfully.
    std::cout << " ... Success.\n" << "[CLIENT] Logging in as " << d_clientID << "\n";

    // Send greeting to server.
    sendMessage("[CLIENT] HELLO_I_AM " + d_clientID);
    //boost::asio::write(d_socket, boost::asio::buffer(std::string("HELLO_I_AM ") + d_clientID));
}

void TCPClient::sendMessage(const std::string& message) {
    boost::system::error_code error;
    boost::asio::write(d_socket, boost::asio::buffer(message), error);
}

void TCPClient::sendNewOrder( const Order& order ) {    
    boost::system::error_code error;
        
    // Dumps the new Order object for logging/debugging.
    std::cout<< "[CLIENT] Sending order " << genOrderID() << " " << order.toString() << "\n";

    //[DONE] TASK change the protocol to include the order id     
    //[DONE] TASK change the protocol to FIX
    boost::asio::write(d_socket, 
            boost::asio::buffer("[CLIENT] NEW_ORDER" + order.serialise()), 
            error);
}

