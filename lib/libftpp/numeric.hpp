#pragma once

#include "Exception.hpp"
#include "Expected.hpp"
#include "type_traits.hpp"
#include <limits>
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

/* Saturation arithmetic */

/**
 * https://en.cppreference.com/w/cpp/numeric/add_sat
 */
template <typename T>
typename ft::enable_if<std::numeric_limits<T>::is_integer, T>::type
add_sat(T x, T y) throw();

/**
 * https://en.cppreference.com/w/cpp/numeric/sub_sat
 */
template <typename T>
typename ft::enable_if<std::numeric_limits<T>::is_integer, T>::type
sub_sat(T x, T y) throw();

/**
 * https://en.cppreference.com/w/cpp/numeric/mul_sat
 */
template <typename T>
typename ft::enable_if<std::numeric_limits<T>::is_integer, T>::type
mul_sat(T x, T y) throw();

/**
 * https://en.cppreference.com/w/cpp/numeric/div_sat
 */
template <typename T>
typename ft::enable_if<std::numeric_limits<T>::is_integer, T>::type
div_sat(T x, T y) throw();

} // namespace ft

#include "src/numeric/numeric_cast.tpp"          // IWYU pragma: export
#include "src/numeric/saturation_arithmetic.tpp" // IWYU pragma: export
