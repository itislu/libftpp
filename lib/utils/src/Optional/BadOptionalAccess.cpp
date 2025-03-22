#include "../../Optional.hpp"

namespace utils {

const char* BadOptionalAccess::what() const throw()
{
	return "bad optional access";
}

} // namespace utils
