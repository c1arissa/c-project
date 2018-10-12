#include <TCPServer.h>

void TCPServer::acceptConnection() {
    try {
        //std::vector<std::thread>connectionHandlerThreads;
        // Accept incoming client connections and spawn a new worker thread.
        for (;;) {
            // Wait for a connection.
            d_acceptor.accept(d_socket);
            
            std::cout << "[SERVER] Client " << ++d_clientNum << " connected "
                << d_socket.local_endpoint() << " " << d_socket.remote_endpoint() << "\n";
            
            // Client has access to service.  Transfer current time to client.
            //std::string message = make_daytime_string();
            //sendResponse(message);
            //connectionHandlerThreads.push_back(std::thread(&TCPServer::handleConnection, this));
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void TCPServer::handleConnection() {
    ConnectionHandler handler;
    handler.start();
    
    for (;;) {
        boost::array<char, 128> buf;
		boost::system::error_code error;
		
		size_t len = d_socket.read_some(boost::asio::buffer(buf), error);
		
		if (error == boost::asio::error::eof) {
		    std::cout << "[SERVER] Connection closed cleanly by peer." << std::endl;
			break; 
		}
		else if (error)
		    throw boost::system::system_error(error); // Some other error.

        // Add data onto end of queue
		handler.queueMessage( buf.data(), len);

		if ( handler.quitReceived() )
		    break;
	}
	handler.join();
	
	//std::string message = make_daytime_string();
	//sendResponse("[SERVER] " + message);
}

void TCPServer::sendResponse(const std::string& message) {
    // Don't ignore errors.
    boost::system::error_code error;
    boost::asio::write(d_socket, boost::asio::buffer(message), error);
    if (error) {
        std::cout << "[SERVER] Error: " <<  error.message() << std::endl;
        return;
    }
    //sleep(10);
    //boost::asio::write(d_socket, boost::asio::buffer(message), error);
}
