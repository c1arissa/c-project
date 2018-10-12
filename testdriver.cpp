#include <TCPClient.h>
#include <TCPServer.h>
#include <Order.h>
#include <stdlib.h>
//#include <ctime>
//#include <cstdlib>

//std::string instruments[]{"VOD.L","HSBA.L"};

int main(int argc, char** argv) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <0|1> <host> <port> <clientid>\n"
            << "0 for server, 1 for client\n";
        return 1;
	}

    Order newOrder("SYM1", Order::Direction::Buy, 199998, 500.25);
    Order newOrder1("SYM2", Order::Direction::Sell, 123455, 1000.15);
    
    // io_service object provides access to I/O functionality.
    boost::asio::io_service io_service;

    switch (atoi(argv[1])) {
        case 0:
            // Create a TCP Server Object
            TCPServer server(io_service, argv[2], argv[3]);
            server.acceptConnection();
            server.handleConnection();
            break;
        case 1:
            // Create a TCP Client Object
            TCPClient client(io_service, argv[1], argv[2], argv[3]);
            client.connectToServer();
            // CALL SEND NEW ORDER FROM CLIENT DRIVER PROGRAM IN MAIN()
            client.sendNewOrder( newOrder );
            client.sendNewOrder( newOrder1 );
            break;
        default:
            break;
    }

    //client.teardown();
    //TASK have the server respond to the client with fill messages
    return 0;
}
