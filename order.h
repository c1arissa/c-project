#ifndef Order_h_
#define Order_h_

#include <string>

class Order {
    friend std::istream& operator>>( std::istream&, Order& );

public:

    enum Direction { Buy = 'B', Sell = 'S' };

    Order( const std::string& symbol, Direction direction,
           size_t quantity, float limitPrice );

    std::string serialise() const;

    Order() = default;

    std::string toString() const;

private:
    std::string symbol_;
    Direction direction_;
    size_t quantity_;
    float limitPrice_;
};

std::istream& operator>>( std::istream&, Order& );

#endif // Order_h_
