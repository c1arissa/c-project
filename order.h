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

/*namespace Direction {
enum : char {
           Buy='B',
           Sell='S'
       };
}*/

class Order 
{
    //friend std::istream& operator>>( std::istream& in, Order& order );
        // Inputs values for the entire Order.

public:
    enum Direction : unsigned char {
        Buy = 'B',
        Sell = 'S',
    };
    //enum Direction { Buy, Sell };
    //enum Direction { Buy = 'B', Sell = 'S', };

    Order() = default;

    Order( const std::string& symbol, Direction direction, size_t quantity, double limitPrice );
        // Construct an order and initialize all data members.

    std::string serialise() const;
        // Returns entire order as a FIX protocol-encoded string.
    
    std::string toString() const;
        // Dumps the contents of an Order object to 
        // a string for debugging and/or logging.
    
    const std::string& getSymbol() const;
        // Returns a nonmodifiable string reference to the order's symbol.

    Direction getDirection() const;
        // Returns if the order is Buy side or Sell side.

    size_t getQuantity() const;
        // Returns the order quantity.

    double getPrice() const;
        // Returns the limit price of the order.
    
    friend std::istream& operator>>( std::istream& is, Order::Direction& direction );
    friend std::istream& operator>>( std::istream& in, Order& order );

    /*{
        char letter;
        is >> letter;
        direction = static_cast<Direction>( letter );
        return is;
    }*/
        // Defines overloaded input for enum class Direction.

private:
    std::string d_symbol;
    Direction   d_direction;
    size_t      d_quantity;
    double      d_limitPrice;
};

inline
Order::Order( const std::string& symbol, Direction direction, size_t quantity, double limitPrice )
    : d_symbol( symbol )
    , d_direction( direction )
    , d_quantity( quantity )
    , d_limitPrice( limitPrice )
{
}

inline std::istream& operator>>( std::istream& is, Order::Direction& direction ) {
    unsigned char ch;
    //is >> letter;
    
    if ( is >> ch ) {
        switch ( ch ) {
            case 'B': // case S:
                direction = Order::Buy;
                //direction = Order::Direction::Buy;
                break;
            case 'S':
                direction = Order::Sell;
                //direction = Order::Direction::Sell;
                break;
            default:
                throw std::runtime_error("Can't read a direction: it must be B or S");
        }
    }
    // direction = static_cast<Order::Direction>( letter );
    return is;
}

/*
 * Define getter functions
 */

inline const std::string& Order::getSymbol() const {
    return d_symbol;
}

inline Order::Direction Order::getDirection() const {
    return d_direction;
}

inline size_t Order::getQuantity() const {
    return d_quantity;
}

inline double Order::getPrice() const {
    return d_limitPrice;
}

#endif // Order_h_
