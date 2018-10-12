ALL: server client
TESTS: orderbook.t

GTESTDIRECTORY=/home/ibutt/googletest-master/googletest
GTESTMAIN=gtest_main.a
CPP11=-std=c++11 
COMPILE_FOR_DEBUG=-Og -g
LIBRARIES= /usr/lib/libboost_system-mt.so.1.53.0 

CPPFLAGSWITHGTEST=$(CPP11) $(COMPILE_FOR_DEBUG) -I$(GTESTDIRECTORY)/include $(GTESTDIRECTORY)/make/$(GTESTMAIN)

clean:
	-rm -f server client *.o *.gch

ConnectionHandler.o: ConnectionHandler.cpp ConnectionHandler.h
	g++ -I. $(CPP11) $(COMPILE_FOR_DEBUG) -c $^

Order.o: Order.cpp Order.h
	g++ -I. $(CPP11) $(COMPILE_FOR_DEBUG) -c $^

orderbook.o: orderbook.cpp orderbook.h
	g++ -I. $(CPP11) $(COMPILE_FOR_DEBUG) -c $^

server: server.cpp ConnectionHandler.o Order.o orderbook.o
	g++ -I. $(CPP11) $(COMPILE_FOR_DEBUG) -o $@ server.cpp Order.o orderbook.o ConnectionHandler.o $(LIBRARIES) -lpthread

client: client.cpp Order.o
	g++ -I. $(CPP11) $(COMPILE_FOR_DEBUG) -o $@ $^ $(LIBRARIES) -lpthread

TCPClient.o: TCPClient.cpp TCPClient.h
	g++ -I. $(CPP11) $(COMPILE_FOR_DEBUG) -c $^

TCPServer.o: TCPServer.cpp TCPServer.h
	g++ -I. $(CPP11) $(COMPILE_FOR_DEBUG) -c $^

orderbook.t: orderbook.t.cpp orderbook.o
	g++ -I. $(CPP11) $(CPPFLAGSWITHGTEST) -o $@ orderbook.t.cpp orderbook.o $(LIBRARIES)

main : main.cpp Order.o TCPClient.o TCPServer.o ConnectionHandler.o orderbook.o
	g++ -I. $(CPP11) -pthread $(COMPILE_FOR_DEBUG) -o $@ $^ $(LIBRARIES)
