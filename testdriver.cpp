#include <TCPClient.h>
//#include <TCPServer.h>
#include <Order.h>
#include <ctime>
#include <cstdlib>

/*
int orderId=0;
std::string instruments[]{"VOD.L","HSBA.L"};
size_t sizes[]{1763,2024};
double benchmarkPrices[]{1.23,2.76}; //[DONE] TODO change all floats to doubles
*/

int main(int argc, char** argv)
{
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <host> <port> <clientid>\n";
        return 1;
	}
    
    srand( std::time(0) );
    
    Order newOrder("SYM1", Order::Direction::Buy, 199998, 500.25);
    Order newOrder1("SYM2", Order::Direction::Sell, 123455, 1000.15); 
    
    // io_service object provides access to I/O functionality.
    // boost::asio::io_service io_service;

    // Create a TCP Server Object
    // TCPServer server(argv[1], argv[2], io_service);

    // Create a TCP Client Object
    TCPClient client(argv[1], argv[2], argv[3]);

    client.connectToServer();
    
    // CALL SEND NEW ORDER FROM CLIENT DRIVER PROGRAM IN MAIN()
    client.sendNewOrder( newOrder );
    client.sendNewOrder( newOrder1 );

    //client.teardown();
    //TASK have the server respond to the client with fill messages
    return 0;
}
