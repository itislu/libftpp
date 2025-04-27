#pragma once

#include "../../Optional.hpp"
#include "../../string.hpp"
#include "../../utility.hpp"
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
template <typename T>
static std::out_of_range out_of_range(const std::string& str);
template <typename T>
static std::invalid_argument invalid_argument(const std::string& str);
} // namespace _string

template <typename T>
T from_string(const std::string& str)
{
	return from_string<T>(str, std::ios::fmtflags());
}

template <typename T>
ft::Optional<T> from_string(const std::string& str, std::nothrow_t /*nothrow*/)
{
	return from_string<T>(str, std::ios::fmtflags(), std::nothrow);
}

template <typename T>
T from_string(const std::string& str, std::ios::fmtflags fmt)
{
	T res;
	std::istringstream iss(str);
	iss.flags(fmt);

	if (iss >> res) {
		return res;
	}

	if (std::numeric_limits<T>::is_integer) {
		const char* start = str.c_str();
		char* end = NULL;

		(void)std::strtol(start, &end, 0);
		if (end != start) {
			throw _string::out_of_range<T>(str);
		}
	}
	throw _string::invalid_argument<T>(str);
}

template <typename T>
ft::Optional<T> from_string(const std::string& str,
                            std::ios::fmtflags fmt,
                            std::nothrow_t /*nothrow*/)
{
	try {
		return from_string<T>(str, fmt);
	}
	catch (const std::logic_error&) {
		return ft::nullopt;
	}
}

template <>
inline bool from_string<bool>(const std::string& str)
{
	bool b; // NOLINT(cppcoreguidelines-init-variables)

	if ((std::istringstream(str) >> std::boolalpha >> b).good()
	    || (std::istringstream(str) >> b).good()) {
		return b;
	}
	throw _string::invalid_argument<bool>(str);
}

template <>
inline float from_string<float>(const std::string& str)
{
	return _string::from_string_floating_point<float>(str);
}

template <>
inline double from_string<double>(const std::string& str)
{
	return _string::from_string_floating_point<double>(str);
}

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
		throw _string::out_of_range<T>(str);
	}
	if (end == start) {
		throw _string::invalid_argument<T>(str);
	}
	return res;
}

template <typename T>
static std::out_of_range out_of_range(const std::string& str)
{
	return std::out_of_range(std::string(std::strerror(ERANGE)) + " ("
	                         + ft::demangle(typeid(T).name()) + "): \"" + str
	                         + "\"");
}

template <typename T>
static std::invalid_argument invalid_argument(const std::string& str)
{
	return std::invalid_argument(std::string("Cannot convert to ")
	                             + ft::demangle(typeid(T).name()) + ": \"" + str
	                             + "\"");
}

} // namespace _string

} // namespace ft
