#include "../../Exception.hpp"
#include "../../numeric.hpp"
#include <string>

namespace ft {

NumericCastException::NumericCastException()
    : ft::Exception("bad numeric conversion", "ft::numeric_cast")
{}

NumericCastException::NumericCastException(const std::string& msg)
    : ft::Exception(msg, "ft::numeric_cast")
{}

NumericCastNegativeOverflowException::NumericCastNegativeOverflowException()
    : NumericCastException("bad numeric conversion: negative overflow")
{}

NumericCastPositiveOverflowException::NumericCastPositiveOverflowException()
    : NumericCastException("bad numeric conversion: positive overflow")
{}

} // namespace ft
