#include "../../Exception.hpp"
#include "../../numeric.hpp"
#include <string>

namespace ft {

ArithmeticException::ArithmeticException(const std::string& msg,
                                         const std::string& who)
    : ft::Exception("arithmetic exception: " + msg, who)
{}

ArithmeticNegativeOverflowException::ArithmeticNegativeOverflowException(
    const std::string& who)
    : ArithmeticException("negative overflow", who)
{}

ArithmeticPositiveOverflowException::ArithmeticPositiveOverflowException(
    const std::string& who)
    : ArithmeticException("positive overflow", who)
{}

ArithmeticDivisionByZeroException::ArithmeticDivisionByZeroException(
    const std::string& who)
    : ArithmeticException("division by zero", who)
{}

} // namespace ft
