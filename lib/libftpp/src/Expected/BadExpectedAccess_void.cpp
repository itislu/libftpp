#include "../../Expected.hpp"

namespace ft {

const char* BadExpectedAccess<void>::what() const throw()
{
	return "bad access to ft::Expected without expected value";
}

BadExpectedAccess<void>::BadExpectedAccess() throw() {}

BadExpectedAccess<void>::BadExpectedAccess(const BadExpectedAccess& /*unused*/)
{}

BadExpectedAccess<void>::~BadExpectedAccess() throw() {}

BadExpectedAccess<void>&
BadExpectedAccess<void>::operator=(const BadExpectedAccess& /*unused*/)
{
	return *this;
}

} // namespace ft
