#include <Order.h>

std::string Order::serialise() const {
	std::ostringstream oss;
	oss << getSymbol() << " " 
	    << static_cast<char>(getDirection()) << " " 
	    << getQuantity() << " " 
	    << getPrice();
	
	return oss.str();
}

std::string Order::toString() const {
	std::ostringstream oss;
	oss << "{ Order symbol '" << getSymbol()
		<< "' direction '" << static_cast<char>(getDirection())
		<< "' quantity '" << getQuantity()
		<< "' limit price '" << getPrice()
		<< "' }";
	return oss.str();
}

std::istream& operator>>( std::istream& is, Order& order ) {
    /*s >> order.d_symbol;
    is >> order.d_direction;
    is >> order.d_quantity;
    is >> order.d_limitPrice;
    return is;*/
	std::string symbol;
    Order::Direction direction;
	size_t quantity;
	float limitPrice;
	is >> symbol;
	if ( is.eof() ) return is;
	is >> direction;
	is >> quantity;
	is >> limitPrice;
	order = Order(symbol, direction, quantity, limitPrice);
	return is;
}
/*
std::istream& operator>>( std::istream& is, Direction& direction ) {
	std::string d;
	is >> d;

	if ( d == "B" )
	    direction = Order::Direction::Buy;
	else if ( d == "S" )
	    direction = Order::Direction::Sell;
	else
	    throw std::runtime_error("Can't read a direction: it must be B or S");

	return is;
}
*/
