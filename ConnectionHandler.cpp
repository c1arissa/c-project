#include <ConnectionHandler.h>
#include <Order.h>
#include <iostream>
#include <sstream>

void ConnectionHandler::queueMessage(const char* buffer, size_t len)
{
    std::cout << "queueMessage called";
    std::string message(buffer, len);
    std::lock_guard<std::mutex> lock(d_mutex);
    d_queue.push_back(message);
    std::cout << "leaving queueMessage\n";
}

void ConnectionHandler::processMessages() 
{
    d_numOfOrders++;
    
    std::cout << "processMessages called\n" << std::endl;
    while (!d_quitReceived) {
        {
            std::lock_guard<std::mutex> lock(d_mutex);
	    
            if (d_queue.empty()) {
                //std::cout << "[SERVER] the queue is empty" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
	        }
	        else {
	            std::cout << "[SERVER] got a message, so far we have " << d_numOfOrders << " orders\n";
	            const std::string message = d_queue.front();
	            
	            if ("QUIT" == message.substr(0, 4)) {
	                d_quitReceived = true;
	                std::cout << "[CLIENT] QUIT was received\n";
	                d_queue.pop_front();
	            }
	            else if ("HELLO_I_AM" == message.substr(0, 10)) {
	                d_userIdentifiedAs = message.substr(10);
	                std::cout << "[CLIENT] HELLO_I_AM was received '" <<d_userIdentifiedAs << "'\n";
	                d_queue.pop_front();
	            } 
	            else if ("NEW_ORDER" == message.substr(0, 9)) {
	                std::string remainder = message.substr(9);
	                std::cout << "[CLIENT] NEW_ORDER was received '" <<remainder << "'\n";
	                //std::stringstream ss(remainder, std::ios::binary);
	                std::stringstream ss( remainder );
	                Order order;
	                ss >> order;
	                std::streampos tellg = ss.tellg();
	                std::cout << "[SERVER] tellg says size of message " << tellg << "\n";
	                d_queue.pop_front();
	                //ss.ignore(ss.tellg());
	                
	                if (tellg == -1) {
	                    std::ios::iostate ios = ss.rdstate();
	                    if (ss.eof()) {
	                        std::cout << "[SERVER] we reached end of file\n";
			    /*std::string newmessage;
			    if (d_queue.empty()) {
			        newmessage = message;
			    }
                            else {
			        newmessage = message + d_queue.front();
				d_queue.pop_front();
			    }
			    d_queue.push_front(newmessage);*/
		        }
		    } 
            else {
                d_numOfOrders++;
                std::cout << "[CLIENT] The order was " << order.toString() << "\n";
                remainder = remainder.substr(ss.tellg());
		        std::cout << "new remainder is '" << remainder << "'\n";
		        if (!remainder.empty()) 
		            d_queue.push_front(remainder);
		    }
		}
		else {
		    std::cout << "[SERVER] Got a partial message which was '" << message << "'\n";
		    d_queue.pop_front();
		    std::string newmessage;
		    if (d_queue.empty()) {
		        newmessage = message;
		    }
		    else {
		        newmessage = message + d_queue.front();
		        d_queue.pop_front();
		    }
		    d_queue.push_front( newmessage );
		}
		    }
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << " leaving processMessages\n";
}

void ConnectionHandler::start() 
{
    d_quitReceived = false;
    d_numOfOrders  = 0;
    d_thread = std::thread(&ConnectionHandler::processMessages, this);
}

void ConnectionHandler::join()
{
    d_thread.join();
}
