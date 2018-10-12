#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <thread>
#include <deque>
#include <string>
#include <mutex>
#include <order.h>
#include <vector>

class OrderBook {

    private:
      std::vector<Order> buyOrders_;
      std::vector<Order> sellOrders_;

    public:
      void addOrder(const std::string& client, const Order& order);

      // Look for matches, execute the matches, and return the fills
      std::vector<Order> findAndExecuteMatches(const Order& order);

};

std::istream& operator>>(std::istream&, Order&);

#endif
