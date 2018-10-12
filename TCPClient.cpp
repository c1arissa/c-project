#include <TCPClient.h>

void TCPClient::connectToServer() {
    // Resolve hostnames and return list of TCP endpoints as an iterator.
    tcp::resolver::query query(d_server, d_port);
    tcp::resolver::iterator endpoint_iterator = d_resolver.resolve(query);
    std::cout<< "[CLIENT] Connecting to server: " << d_server << ":" << d_port;
    
    // Connect the socket to the list of tcp endpoints.
    try {
        boost::asio::connect(d_socket, endpoint_iterator);    
        // Established connection successfully.
        std::cout << " ... Success.\n";
        onConnect();
    }
    catch (boost::system::system_error const& e) {
        std::cout << "Error: could not connect: " << e.what() << std::endl;
    }  
}

void TCPClient::sendMessage(const std::string& message) {
    boost::system::error_code error;
    boost::asio::write(d_socket, boost::asio::buffer(message), error);
    onError(error);
}

void TCPClient::sendNewOrder( const Order& order ) {
    // Dumps the new Order object for logging/debugging.
    std::cout<< "[CLIENT] Sending order " << genOrderID() << " " << order.toString() << "\n";
    
    // Sends serialized Order to server.
    boost::system::error_code error;
    boost::asio::write(d_socket, boost::asio::buffer("NEW_ORDER" + order.serialise()), error);
    onError(error);
}

void TCPClient::receive() {
    boost::system::error_code error;
    
    while (error != boost::asio::error::eof) {
        // Use a char boost::array to hold the received data.
        boost::array<char, 128> buf;
        
        // read_some() exits with boost::asio::error::eof when the
        // server closes the connection.
        size_t bufLen = d_socket.read_some(boost::asio::buffer(buf), error);

        if (bufLen > 0) {
            //std::cout.write(buf.data(), bufLen);
            std::cout << "[SERVER] " << buf.data() << "\n";
        }
    }
}

void TCPClient::onConnect() {
    std::cout << "[CLIENT] Logging in as " << d_clientID << "\n";
    // Send greeting message to the server.
    std::string message = "HELLO_I_AM " + d_clientID;
    sendMessage(message);
}

void TCPClient::onExit() {
    std::cout<< "[CLIENT] Logging out\n";
    // Send goodbye message to the server.
    sendMessage("QUIT");
}
