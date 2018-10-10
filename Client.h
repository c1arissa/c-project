#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "order.h"
#include <cstdlib>
using boost::asio::ip::tcp;


class Client {
    unsigned clientID;
    std::string host;
    unsigned port;

public:
    Client();

    void connect();

    void sendNewOrder( tcp::socket& socket, const Order& order );

};

void Client::sendNewOrder( tcp::socket& socket ) { 
    
    boost::system::error_code ignored_error;
    int instIndex=orderId%2;
    
    Order newOrder( { instruments[instIndex], Order::Buy, sizes[instIndex], benchmarkPrices[instIndex]} ); //TODO make the numbers random
    std::cout<<"Sending order "<<orderId++<<" "<<newOrder.toString()<<"\n";
    //TASK change the protocol to include the order id
    //TASK change the protocol to FIX
    boost::asio::write(socket, boost::asio::buffer("NEW_ORDER" + newOrder.serialise()), ignored_error);
}
