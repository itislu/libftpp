#pragma once

#include "../../Optional.hpp"
#include "../../string.hpp"
#include <cerrno>
#include <cfloat>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <new>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace ft {
namespace _string {
template <typename T>
static T from_string_floating_point(const std::string& str);
} // namespace _string

/**
 * @brief Converts a string to a specified type
 *
 * @tparam T The type to convert to
 * @param str The string to convert
 * @return T The converted value
 *
 * @throws std::out_of_range When the value is out of the representable range
 * @throws std::invalid_argument When the string cannot be converted to the type
 */
template <typename T>
T from_string(const std::string& str)
{
	return from_string<T>(str, std::ios::fmtflags());
}

/**
 * @brief Converts a string to a specified type without throwing exceptions
 *
 * This is the non-throwing version of the `from_string` function.
 * Instead of throwing exceptions on failure, it returns an empty
 * `ft::Optional`.
 * To use it, pass a tag (f.e. `std::nothrow`) to indicate the non-throwing
 * behavior.
 *
 * @tparam T The type to convert to
 * @param str The string to convert
 * @return ft::Optional<T> The converted value wrapped in an `ft::Optional`, or
 * an empty `ft::Optional` if the conversion fails
 */
template <typename T>
ft::Optional<T> from_string(const std::string& str, std::nothrow_t /*unused*/)
{
	return from_string<T>(str, std::ios::fmtflags(), std::nothrow);
}

/**
 * @brief Converts a string to a specified type
 *
 * @tparam T The type to convert to
 * @param str The string to convert
 * @param fmt Stream formatting flags that determine how the string is
 * interpreted
 * @return T The converted value
 *
 * @throws std::out_of_range When the value is out of the representable range
 * @throws std::invalid_argument When the string cannot be converted to the type
 */
template <typename T>
T from_string(const std::string& str, std::ios::fmtflags fmt)
{
	T res;
	std::istringstream iss(str);
	iss.flags(fmt);

	if (!(iss >> res)) {
		if (std::numeric_limits<T>::is_integer) {
			const char* start = str.c_str();
			char* end = NULL;

			(void)std::strtol(start, &end, 0);
			if (end != start) {
				throw std::out_of_range(std::string(strerror(ERANGE)) + " ("
				                        + typeid(T).name() + "): " + str);
			}
		}
		throw std::invalid_argument(std::string("Cannot convert to ")
		                            + typeid(T).name() + ": " + str);
	}
	return res;
}

/**
 * @brief Converts a string to a specified type without throwing exceptions
 *
 * This is the non-throwing version of the `from_string` function.
 * Instead of throwing exceptions on failure, it returns an empty
 * `ft::Optional`.
 * To use it, pass a tag (f.e. `std::nothrow`) to indicate the non-throwing
 * behavior.
 *
 * @tparam T The type to convert to
 * @param str The string to convert
 * @param fmt Stream formatting flags that determine how the string is
 * interpreted
 * @return ft::Optional<T> The converted value wrapped in an `ft::Optional`, or
 * an empty `ft::Optional` if the conversion fails
 */
template <typename T>
ft::Optional<T> from_string(const std::string& str,
                            std::ios::fmtflags fmt,
                            std::nothrow_t /*unused*/)
{
	try {
		return from_string<T>(str, fmt);
	}
	catch (const std::logic_error&) {
		return ft::nullopt;
	}
}

/**
 * @brief Converts a string to a boolean.
 *
 * Accepts both alpha (true/false) and numeric (1/0) formats.
 *
 * @param str The string to convert
 * @return bool The converted boolean value
 *
 * @throws std::invalid_argument When the string neither starts with true/false
 * nor 1/0
 */
template <>
inline bool from_string<bool>(const std::string& str)
{
	bool b; // NOLINT(cppcoreguidelines-init-variables)

	if (!(std::istringstream(str) >> std::boolalpha >> b)
	    && !(std::istringstream(str) >> b)) {
		throw std::invalid_argument(std::string("Cannot convert to ")
		                            + typeid(bool).name() + ": " + str);
	}
	return b;
}

/**
 * @brief Converts a string to a float
 *
 * @param str The string to convert
 * @return float The converted floating-point value
 *
 * @throws std::out_of_range When the value is out of the representable range
 * @throws std::invalid_argument When the string cannot be converted to a float
 */
template <>
inline float from_string<float>(const std::string& str)
{
	return _string::from_string_floating_point<float>(str);
}

/**
 * @brief Converts a string to a double
 *
 * @param str The string to convert
 * @return double The converted floating-point value
 *
 * @throws std::out_of_range When the value is out of the representable range
 * @throws std::invalid_argument When the string cannot be converted to a double
 */
template <>
inline double from_string<double>(const std::string& str)
{
	return _string::from_string_floating_point<double>(str);
}

/**
 * @brief Converts a string to a long double
 *
 * @param str The string to convert
 * @return long double The converted floating-point value
 *
 * @throws std::out_of_range When the value is out of the representable range
 * @throws std::invalid_argument When the string cannot be converted to a long
 * double
 */
template <>
inline long double from_string<long double>(const std::string& str)
{
	return _string::from_string_floating_point<long double>(str);
}

namespace _string {

/**
 * Uses strto* functions for floating-point types because stringstream does not
 * support nan or inf.
 */
template <typename T>
static T from_string_floating_point(const std::string& str)
{
	T res;
	const char* start = str.c_str();
	char* end = NULL;
	errno = 0;

	switch (std::numeric_limits<T>::max_exponent) {
	case FLT_MAX_EXP:
		res = std::strtof(start, &end);
		break;
	case DBL_MAX_EXP:
		res = std::strtod(start, &end);
		break;
	default:
		res = std::strtold(start, &end);
		break;
	}

	if (errno == ERANGE) {
		throw std::out_of_range(std::string(strerror(ERANGE)) + " ("
		                        + typeid(T).name() + "): " + str);
	}
	if (end == start) {
		throw std::invalid_argument(std::string("Cannot convert to ")
		                            + typeid(T).name() + ": " + str);
	}
	return res;
}

} // namespace _string

} // namespace ft
