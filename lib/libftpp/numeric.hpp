#pragma once

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

} // namespace ft

#include "src/numeric/numeric_cast.tpp" // IWYU pragma: export
