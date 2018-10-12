#include <orderbook.h>
#include<Order.h>

void OrderBook::addOrder(const std::string& client, const Order& order)
{
    if (order.getDirection() == 'B'){
        buyOrders_.push_back(order);
    }
    else if (order.getDirection() == 'S') {
        sellOrders_.push_back(order);
    }
}

std::vector<Order> OrderBook::findAndExecuteMatches(const Order& order){
  
  std::vector<Order> results;

  if(order.getDirection() == 'B') {
    for(std::size_t i = 0; i < sellOrders_.size(); ++i) {
      if(order.getSymbol() == sellOrders_[i].getSymbol() &&
        order.getPrice() == sellOrders_[i].getPrice()){
        
         results.push_back(sellOrders_[i]);
      }
      return results;
    }
  }

  if(order.getDirection() == 'S') {
    for(std::size_t i = 0; i < buyOrders_.size(); ++i) {
      if( order.getSymbol() == buyOrders_[i].getSymbol() &&
         order.getPrice() == buyOrders_[i].getPrice() ) {
             
        results.push_back(buyOrders_[i]);
      }
    }
    return results;  
  }
}
