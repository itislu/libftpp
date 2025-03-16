#include "Optional.hpp"

namespace utils {

const char* BadOptionalAccess::what() const throw()
{
	return "bad optional access";
}

nullopt_t::nullopt_t(int /*unused*/) throw() {}

const nullopt_t nullopt(0);

} // namespace utils
