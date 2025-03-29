#include "../../numeric.hpp"

namespace ft {

const char* BadNumericCast::what() const throw()
{
	return "bad numeric conversion";
}

const char* NegativeOverflow::what() const throw()
{
	return "bad numeric conversion: negative overflow";
}

const char* PositiveOverflow::what() const throw()
{
	return "bad numeric conversion: positive overflow";
}

} // namespace ft
