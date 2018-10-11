#ifndef INCLUDED_ORDER
#define INCLUDED_ORDER

#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

// WHAT'S WRONG HERE???
// ANSWER: INCORRECT HEADERS FOR THIS FILE
//#include <thread>
//#include <deque>
//#include <string>
//#include <mutex>

enum class Direction : char {
    Buy = 'B',
    Sell = 'S',
};

class Order 
{
    std::string d_symbol;
    Direction   d_direction;
    size_t      d_quantity;
    double      d_limitPrice;

public:
    Order() = default;

    Order( const std::string& symbol, Direction direction, size_t quantity, double limitPrice );
        // Construct an order and initialize all data members.

    std::string serialise() const;
        // Returns entire order as a FIX protocol-encoded string.
    
    std::string toString() const;
        // Dump an Order object and return it as a string.
    
    const std::string& getSymbol() const;
        // Returns a nonmodifiable string reference to the order's symbol.

    Direction getDirection() const;
        // Returns if the order is Buy side or Sell side.

    size_t getQuantity() const;
        // Returns the order quantity.

    double getPrice() const;
        // Returns the limit price of the order.
    
    friend std::istream& operator>>( std::istream& in, Direction& direction );
        // Defines overloaded input for enum class Direction.

    friend std::istream& operator>>( std::istream& in, Order& order );
        // Inputs values for the entire Order.    
};

inline
Order::Order( const std::string& symbol, Direction direction, size_t quantity, double limitPrice )
    : d_symbol( symbol )
    , d_direction( direction )
    , d_quantity( quantity )
    , d_limitPrice( limitPrice )
{
}

inline std::istream& operator>>( std::istream& is, Direction& direction ) {
	std::string d;
	is >> d;

	if ( d == "B" )
	    direction = Direction::Buy;
	else if ( d == "S" )
	    direction = Direction::Sell;
	else
	    throw std::runtime_error("Can't read a direction: it must be B or S");

	return is;
}

inline std::istream& operator>>( std::istream& is, Order& order ) {
    is >> order.d_symbol;
    is >> order.d_direction;
    is >> order.d_quantity;
    is >> order.d_limitPrice;
    return is;

	/*
	 * OLD CODE BELOW.  LEAVE IT THERE IN CASE NEW CODE GIVES UNEXPECTED
	 * FUNCTIONALITY
	 */

	//std::string symbol;
	//Direction direction;
	//size_t quantity;
	//float limitPrice;
	//is >> symbol;
	//if ( is.eof() ) return is;
	//is >> direction;
	//is >> quantity;
	//is >> limitPrice;
	//order = Order(symbol, direction, quantity, limitPrice);
}

/*
 * Define getter functions
 */

inline const std::string& Order::getSymbol() const {
    return d_symbol;
}

inline Direction Order::getDirection() const {
    return d_direction;
}

inline size_t Order::getQuantity() const {
    return d_quantity;
}

inline double Order::getPrice() const {
    return d_limitPrice;
}

#endif // Order_h_
