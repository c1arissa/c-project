#ifndef INCLUDED_SERVERSOCKET
#define INCLUDED_SERVERSOCKET

#include <ctime>
#include <iostream>
#include <string>
#include <memory>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enabled_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <thread>
#include <connectionhandler.h>

using boost::asio::ip::tcp;

class TcpConnection : public std::make_shared<TcpConnection> {
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

    tcp::socket& socket() {
        return d_socket;
    }

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
    std::string   d_host;
    std::string   d_port;
    tcp::acceptor d_acceptor;
    tcp::socket   d_socket;
    std::string   d_message;
    std::string   d_status;

public:
    TCPServer(const std::string& host, const std::string& port, boost::asio::io_service& io_service)
        : d_socket( io_service )
        , d_acceptor( io_service, tcp::endpoint( tcp::v4(), d_port) );

    {
    }
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

#endif
