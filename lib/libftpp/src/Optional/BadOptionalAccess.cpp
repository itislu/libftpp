#include "../../Optional.hpp"

namespace ft {

const char* BadOptionalAccess::what() const throw()
{
	return "bad optional access";
}

} // namespace ft
