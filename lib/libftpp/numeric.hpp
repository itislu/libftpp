#pragma once

#include "Exception.hpp"
#include "Expected.hpp"
#include "type_traits.hpp"
#include <new>
#include <string>

namespace ft {

/* abs_diff */

unsigned char abs_diff(char a, char b) throw();
unsigned short abs_diff(short a, short b) throw();
unsigned int abs_diff(int a, int b) throw();
unsigned long abs_diff(long a, long b) throw();

/* numeric_cast */

class NumericCastException;
class NumericCastNegativeOverflowException;
class NumericCastPositiveOverflowException;

/**
 * @brief Safely converts numeric values between different types
 *
 * This function provides checked numeric conversions between different types,
 * similar to static_cast but with additional runtime checks to prevent
 * undefined behavior.
 *
 * @tparam To The target type to convert to
 * @tparam From The source type to convert from
 * @param from The value to be converted
 * @return The converted value
 *
 * @throws ft::NumericCastException When the conversion is invalid (e.g., NaN to
 * integer)
 * @throws ft::NumericCastNegativeOverflowException When a value is too low for
 * the target type
 * @throws ft::NumericCastPositiveOverflowException When a value is too high for
 * the target type
 */
template <typename To, typename From>
To numeric_cast(From from);

/**
 * @brief Safely converts numeric values between different types
 *
 * This function provides checked numeric conversions between different types,
 * similar to static_cast but with additional runtime checks to prevent
 * undefined behavior.
 *
 * This is the non-throwing version of the `numeric_cast` function.
 * Instead of throwing exceptions on failure, it returns a `ft::Expected`.
 * To use it, pass `std::nothrow` as a tag to indicate the non-throwing
 * behavior.
 *
 * @tparam To The target type to convert to
 * @tparam From The source type to convert from
 * @param from The value to be converted
 * @return A `ft::Expected<To, ft::NumericCastException>` with the converted
 * value on success, or a `ft::NumericCastException` on failure
 */
template <typename To, typename From>
ft::Expected<To, ft::NumericCastException>
numeric_cast(From from, std::nothrow_t /*nothrow*/);

class NumericCastException : public ft::Exception {
public:
	NumericCastException();
	explicit NumericCastException(const std::string& msg);
};

class NumericCastNegativeOverflowException : public NumericCastException {
public:
	NumericCastNegativeOverflowException();
};

class NumericCastPositiveOverflowException : public NumericCastException {
public:
	NumericCastPositiveOverflowException();
};

/* Arithmetic */

// https://wiki.sei.cmu.edu/confluence/display/c/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow

class ArithmeticException;
class ArithmeticNegativeOverflowException;
class ArithmeticPositiveOverflowException;
class ArithmeticDivisionByZeroException;

/**
 * @brief Checked integer addition, guaranteeing no undefined behavior
 *
 * @return A `ft::Expected<T, ft::ArithmeticException>` with the result of the
 * addition on success, or a `ft::ArithmeticException` if the addition would
 * overflow
 */
template <typename T>
REQUIRES(ft::is_integral<T>::value)
((ft::Expected<T, ArithmeticException>)) add_checked(T x, T y);
/**
 * @brief Checked integer subtraction, guaranteeing no undefined behavior
 *
 * @return A `ft::Expected<T, ft::ArithmeticException>` with the result of the
 * subtraction on success, or a `ft::ArithmeticException` if the subtraction
 * would overflow
 */
template <typename T>
REQUIRES(ft::is_integral<T>::value)
((ft::Expected<T, ArithmeticException>)) sub_checked(T x, T y);
/**
 * @brief Checked integer multiplication, guaranteeing no undefined behavior
 *
 * @return A `ft::Expected<T, ft::ArithmeticException>` with the result of the
 * multiplication on success, or a `ft::ArithmeticException` if the
 * multiplication would overflow
 */
template <typename T>
REQUIRES(ft::is_integral<T>::value)
((ft::Expected<T, ArithmeticException>)) mul_checked(T x, T y);
/**
 * @brief Checked integer division, guaranteeing no undefined behavior
 *
 * @return A `ft::Expected<T, ft::ArithmeticException>` with the result of the
 * division on success, or a `ft::ArithmeticException` if the division would
 * overflow or `y == 0`
 */
template <typename T>
REQUIRES(ft::is_integral<T>::value)
((ft::Expected<T, ArithmeticException>)) div_checked(T x, T y);

/**
 * https://en.cppreference.com/w/cpp/numeric/add_sat
 */
template <typename T>
REQUIRES(ft::is_integral<T>::value)
(T) add_sat(T x, T y) throw();
/**
 * https://en.cppreference.com/w/cpp/numeric/sub_sat
 */
template <typename T>
REQUIRES(ft::is_integral<T>::value)
(T) sub_sat(T x, T y) throw();
/**
 * https://en.cppreference.com/w/cpp/numeric/mul_sat
 */
template <typename T>
REQUIRES(ft::is_integral<T>::value)
(T) mul_sat(T x, T y) throw();
/**
 * https://en.cppreference.com/w/cpp/numeric/div_sat
 *
 * @note Unlike `std::div_sat()`, dividing by zero does not lead to undefined
 * behavior, but mimics the IEEE 754 standard for floating point types:
 * - If `x` is negative, returns the minimum representable value of `T`.
 * - If `x` is positive, returns the maximum representable value of `T`.
 * - If `x` is zero, returns zero.
 */
template <typename T>
REQUIRES(ft::is_integral<T>::value)
(T) div_sat(T x, T y) throw();

/**
 * @brief Throwing integer addition, guaranteeing no undefined behavior
 *
 * @throws ft::ArithmeticNegativeOverflowException When the result of the
 * addition would be lower than the lowest representable value of `T`
 * @throws ft::ArithmeticPositiveOverflowException When the result of the
 * addition would be greater than the highest representable value of `T`
 */
template <typename T>
REQUIRES(ft::is_integral<T>::value)
(T) add_throw(T x, T y);
/**
 * @brief Throwing integer subtraction, guaranteeing no undefined behavior
 *
 * @throws ft::ArithmeticNegativeOverflowException When the result of the
 * subtraction would be lower than the lowest representable value of `T`
 * @throws ft::ArithmeticPositiveOverflowException When the result of the
 * subtraction would be greater than the highest representable value of `T`
 */
template <typename T>
REQUIRES(ft::is_integral<T>::value)
(T) sub_throw(T x, T y);
/**
 * @brief Throwing integer multiplication, guaranteeing no undefined behavior
 *
 * @throws ft::ArithmeticNegativeOverflowException When the result of the
 * multiplication would be lower than the lowest representable value of `T`
 * @throws ft::ArithmeticPositiveOverflowException When the result of the
 * multiplication would be greater than the highest representable value of `T`
 */
template <typename T>
REQUIRES(ft::is_integral<T>::value)
(T) mul_throw(T x, T y);
/**
 * @brief Throwing integer division, guaranteeing no undefined behavior
 *
 * @throws ft::ArithmeticPositiveOverflowException When the result of the
 * division would be greater than the highest representable value of `T`
 * @throws ft::ArithmeticDivisionByZeroException When `y == 0`
 */
template <typename T>
REQUIRES(ft::is_integral<T>::value)
(T) div_throw(T x, T y);

class ArithmeticException : public ft::Exception {
public:
	ArithmeticException(const std::string& msg, const std::string& who);
};

class ArithmeticNegativeOverflowException : public ArithmeticException {
public:
	explicit ArithmeticNegativeOverflowException(const std::string& who);
};

class ArithmeticPositiveOverflowException : public ArithmeticException {
public:
	explicit ArithmeticPositiveOverflowException(const std::string& who);
};

class ArithmeticDivisionByZeroException : public ArithmeticException {
public:
	explicit ArithmeticDivisionByZeroException(const std::string& who);
};

/* Numeric algorithms */

/**
 * https://en.cppreference.com/w/cpp/algorithm/iota
 */
template <typename ForwardIt, typename T>
void iota(ForwardIt first, ForwardIt last, T value);

} // namespace ft

#include "src/numeric/arithmetic.tpp"   // IWYU pragma: export
#include "src/numeric/iota.tpp"         // IWYU pragma: export
#include "src/numeric/numeric_cast.tpp" // IWYU pragma: export
