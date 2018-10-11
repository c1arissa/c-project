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
