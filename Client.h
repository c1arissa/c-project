#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "order.h"
#include <cstdlib>
using boost::asio::ip::tcp;


class Client {
    std::string d_hostname;
    std::string d_port;
    std::string d_clientID;
    static int  d_orderID;  // make static to preserve value ??

public:
    Client(const std::string& host, const std::string& port, const std::string& clientID);

    void connect();
        // Connects to the server

    void sendNewOrder( tcp::socket& socket, const Order& order );
        // Send data to server once connection is established.

};

inline
Client::Client(const std::string& host, const std::string& port, const std::string& clientID)
    : d_hostname( host )
    , d_port( port )
    , d_clientID( clientID )
    , d_orderID( d_orderID++ );
{
}

void Client::connect() {
    
    boost::asio::io_service io_service;
    tcp::resolver resolver(io_service);
    
    tcp::resolver::query query( d_hostname, d_port );
    
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    tcp::socket socket(io_service);
    std::cout<< "Connecting to server: " << d_hostname << ":" << d_port<< "\n";
    boost::asio::connect(socket, endpoint_iterator);

	{
	    std::string message = "HELLO_I_AM " + d_clientID;
	    boost::system::error_code ignored_error; //TASK don't ignore errors
	    std::cout<< "Logging in\n";
	    boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
	}
	
	// Automate client to send messages 
	//
	std::cout<<"sleep 5\n";
	sleep(5);
	for (int i = 0; i < (10+rand() % 100); ++i) { 
	    //TASK have the server respond to the client with fill messages
	    sendNewOrder( socket );
		sleep(10); //TASK make random between 0.1s and 3s
	}
	std::cout<<"Logging out\n";
	{
	    std::string message = "QUIT ";
		boost::system::error_code ignored_error;
		boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
	}


}

void Client::sendNewOrder( tcp::socket& socket, const Order& order ) { 
    
    boost::system::error_code ignored_error;
        
    /* Provide Order as a parameter versus creating new object here ?? */

    // int instIndex=orderId%2;
    // Order newOrder( { instruments[instIndex], Order::Buy, sizes[instIndex], benchmarkPrices[instIndex]} ); //TODO make the numbers random
    
    std::cout<<"Sending order "<<orderId++<<" "<<newOrder.toString()<<"\n";

    //TASK change the protocol to include the order id
    //TASK change the protocol to FIX
    boost::asio::write(socket, boost::asio::buffer("NEW_ORDER" + newOrder.serialise()), ignored_error);
}
