#pragma once

#include "Optional.hpp"
#include "type_traits.hpp"
#include <limits>
#include <new>
#include <typeinfo>

namespace ft {

class BadNumericCast : public std::bad_cast {
public:
	const char* what() const throw();
};

class NegativeOverflow : public BadNumericCast {
public:
	const char* what() const throw();
};

class PositiveOverflow : public BadNumericCast {
public:
	const char* what() const throw();
};

/* numeric_cast */

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
 * @throws ft::BadNumericCast When the conversion is invalid (e.g., NaN to
 * integer)
 * @throws ft::NegativeOverflow When a negative value cannot be represented in
 * the target type
 * @throws ft::PositiveOverflow When a value is too large for the target type
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
 * Instead of throwing exceptions on failure, it returns an empty
 * `ft::Optional`.
 * To use it, pass a tag (f.e. `std::nothrow`) to indicate the non-throwing
 * behavior.
 *
 * @tparam To The target type to convert to
 * @tparam From The source type to convert from
 * @param from The value to be converted
 * @return The converted value
 *
 * @throws ft::BadNumericCast When the conversion is invalid (e.g., NaN to
 * integer)
 * @throws ft::NegativeOverflow When a negative value cannot be represented in
 * the target type
 * @throws ft::PositiveOverflow When a value is too large for the target type
 */
template <typename To, typename From>
ft::Optional<To> numeric_cast(From from, std::nothrow_t /*nothrow*/);

/* Saturation arithmetic */

/**
 * https://en.cppreference.com/w/cpp/numeric/add_sat
 */
template <class T>
typename ft::enable_if<std::numeric_limits<T>::is_integer, T>::type
add_sat(T x, T y) throw();

/**
 * https://en.cppreference.com/w/cpp/numeric/sub_sat
 */
template <class T>
typename ft::enable_if<std::numeric_limits<T>::is_integer, T>::type
sub_sat(T x, T y) throw();

/**
 * https://en.cppreference.com/w/cpp/numeric/mul_sat
 */
template <class T>
typename ft::enable_if<std::numeric_limits<T>::is_integer, T>::type
mul_sat(T x, T y) throw();

/**
 * https://en.cppreference.com/w/cpp/numeric/div_sat
 */
template <class T>
typename ft::enable_if<std::numeric_limits<T>::is_integer, T>::type
div_sat(T x, T y) throw();

} // namespace ft

#include "src/numeric/numeric_cast.tpp"          // IWYU pragma: export
#include "src/numeric/saturation_arithmetic.tpp" // IWYU pragma: export
