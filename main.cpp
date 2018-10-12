#include <TCPClient.h>
#include <TCPServer.h>
#include <Order.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    srand( std::time(0) );
    // process command-line args
    if (argc != 5) {
        std::cerr << "Usage:   " << argv[0] << " <socket> <host> <port> <id_num>\n"
            << "Options: \n"
            << "         <socket> = 0 (server) or 1 (client)\n"
            << "         <host>   = IP address of host/server\n"
            << "         <port>   = number of private port\n"
            << "         <id_num> = ID for client socket\n";
        exit(1);
	}

    // Create some Order objects to test the client's sendNewOrder() function.
    std::vector< Order > orders;
    Order newOrder0("SYM1", Order::Direction::Buy, 199998, 500.25);
    Order newOrder1("SYM2", Order::Direction::Sell, 123455, 1000.15);
    Order newOrder2("SYM3", Order::Buy, 100, 260.25);
    Order newOrder3("SYM4", Order::Sell, 1500, 8850.12);
    orders.push_back(newOrder0); orders.push_back(newOrder1); 
    orders.push_back(newOrder2); orders.push_back(newOrder3);
    
    // io_service object provides access to I/O functionality.
    boost::asio::io_service io_service;

    // Run application as a client OR server depending on the command-line
    // option.
    int socketType = atoi(argv[1]);

    if (socketType == 0) {
        // Create a TCP server socket, bind to host:port, and listen.
        TCPServer server(io_service, argv[2], argv[3]);

        // accept incoming clients and spawn threads to handle each connection.
        server.acceptConnection();

        server.handleConnection();
    }
    else if (socketType == 1) {
        // Create a TCP client socket.
        TCPClient client(io_service, argv[2], argv[3], argv[4]);

        // make connection to the server
        client.connectToServer();
        client.receive();

        // once connection is established, send new orders.
        for(size_t i = 0; i < 50; i++) {
            int randomIndex = rand() % 4;
            client.sendNewOrder( orders.at(randomIndex) );
            sleep(1);
            //client.receive();
            //sleep(1);
        }
        client.onExit();
    }
    else {
        std::cout << "Error: Please enter 0 for a server socket or 1 for a client socket.  Try again.\n";
        exit(1);
    }

    return 0;
}
