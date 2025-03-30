#pragma once

#include "Optional.hpp"
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

} // namespace ft

#include "src/numeric/numeric_cast.tpp" // IWYU pragma: export
