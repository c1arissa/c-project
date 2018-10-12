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
