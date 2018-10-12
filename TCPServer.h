#ifndef INCLUDED_SERVERSOCKET
#define INCLUDED_SERVERSOCKET

#include <ctime>
#include <iostream>
#include <string>
//#include <memory>
//#include <boost/bind.hpp>
//#include <boost/shared_ptr.hpp>
//#include <boost/enabled_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <thread>
#include <vector>
#include <connectionhandler.h>

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
        // Create a TCPServer object and begin listening for incoming client
        // connections using the host and port passed in to the c'tor.

    void acceptConnection();
        // Accepts incoming connections and adds session to a thread handler vector.

    void handleConnection();
        // Handles active threads.

    void sendResponse(const std::string& message);
    
    std::string make_daytime_string();

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

//try{  //boost::asio::io_service io_service; //TASK make 3000 dynamic
		//tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 3000));
		//int clientNum=0;

void TCPServer::acceptConnection() {
    try {
        std::vector<std::thread>connectionHandlerThreads;
        
        for (;;) {
            // tcp::socket sock(io_service);
            d_acceptor.accept(d_socket);
            std::cout << "[SERVER] Client " << ++d_clientNum << " connected " << d_socket.local_endpoint() << " " << d_socket.remote_endpoint() << "\n";
            connectionHandlerThreads.push_back(std::thread(handleConnection(), std::move(d_socket)));
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

//void handleConnection(std::shared_ptr<tcp::socket>& socket) {
void TCPServer::handleConnection() {
    
    ConnectionHandler handler;
    handler.start();
    
    for (;;) {
        
        boost::array<char, 128> buf;
		boost::system::error_code error;
		
		size_t len = d_socket.read_some(boost::asio::buffer(buf), error);
		
		if (error == boost::asio::error::eof) {
		    std::cout << "[SERVER] Connection closed cleanly by peer." << std::endl;
			break; // Connection closed cleanly by peer.
		}
		else if (error)
		    throw boost::system::system_error(error); // Some other error.

		handler.queueMessage( buf.data(), len);

		if ( handler.quitReceived() ) {
			break;
		}
	}
	handler.join();
	
	std::string message = make_daytime_string();
	sendResponse(message);
	//	boost::system::error_code ignored_error;
	//	boost::asio::write(*socket, boost::asio::buffer(message), ignored_error);
	//	sleep(10);
	//	boost::asio::write(*socket, boost::asio::buffer(message), ignored_error);
}

void TCPServer::sendResponse(const std::string& message) {
    boost::system::error_code ignored_error;
    boost::asio::write(d_socket, boost::asio::buffer(message), ignored_error);
    sleep(10);
    boost::asio::write(d_socket, boost::asio::buffer(message), ignored_error);
}

inline std::string TCPServer::make_daytime_string(){
    std::time_t now = std::time(0);
    return std::ctime(&now);
}



/*class TcpConnection : public std::make_shared<TcpConnection> {
    tcp::socket d_socket;
    std::string d_message;

public:
    TcpConnection(boost::asio::io_service& io_service)
        : d_socket( io_service )
    
    }
    void handle_write(const boost::system::error_code& error, size_t bytes_transferred) {}

    typedef std::shared_ptr<TcpConnection> pointer;

    static pointer create(boost::asio::io_service& io_service) {
        return pointer(new TcpConnection(io_service));
    }

    tcp::socket& socket() { return d_socket; }

    void start() {
        d_message = make_string();

        boost::asio::async_write(d_socket, boost::asio::buffer(d_message),
                boost::bind(&TcpConnection::handle_write, shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
    }
}; 
    TCPServer(boost::asio::io_service& io_service)
        : d_acceptor(io_service, tcp::endpoint(tcp::v4(), 13))
    {
        start_accept();
    }
};


class TCPServer
{
public:
    void fillOrder;

public:
    ServerSocket() = delete;

    ServerSocket(const std::string& host, const std::string& port);

    void bind();

    void listen();

    void accept();

    // define function to create the string to be sent back to the client.
    const std::string make_string();
};

inline
TCPServer(const std::string& host, const std::string& port, boost::asio::io_service& io_service)
    : d_host( host )
    , d_port( port )
    , d_socket( io_service )
    , d_acceptor( io_service, tcp::endpoint( tcp::v4(), d_port) )
{
}

void TCPServer::listen() {
    try {
        boost::asio::io_service io_service;

        // listen for new connections (listen on TCP port 13 for IP v4)
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), d_port));

        acceptor acceptor(io_service, endpoint(v4(), d_port));

        // Iterative server will handle one connection at a time.
        for (;;) {
            // Create a socket that represents the connection to the client.
            tcp::socket socket(io_service);
            socket socket(io_service);
            
            // Wait for a connection.
            acceptor.accept(socket);

            // Client has access to service.  Transfer current time to client.
            std::string message = make_string();

            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    }
    // Handle any exceptions
    catch (std::exception& e) {
        std::cerr << e.what() << "\n";
    }
}

inline const std::string ServerSocket::make_string() {
    std::time_t now = std::time(0);
    return std::ctime(&now);
}
*/
#endif
