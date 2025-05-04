#pragma once

#include "../../Optional.hpp"
#include "../../algorithm.hpp"
#include "../../string.hpp"
#include "../../type_traits.hpp"
#include "../../utility.hpp"
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <cmath>
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

namespace _from_string {
template <typename T>
static std::out_of_range out_of_range(const std::string& str);
template <typename T>
static std::invalid_argument invalid_argument(const std::string& str);
} // namespace _from_string

template <typename T>
T from_string(const std::string& str,
              std::string::size_type* endpos_out /*= NULL*/)
{
	return from_string<T>(str, std::ios::fmtflags(), endpos_out);
}

template <>
inline bool from_string<bool>(const std::string& str,
                              std::string::size_type* endpos_out /*= NULL*/)
{
	try {
		return from_string<bool>(str, std::ios::boolalpha, endpos_out);
	}
	catch (const std::logic_error&) {
		return from_string<bool>(str, std::ios::fmtflags(), endpos_out);
	}
}

template <typename T>
ft::Optional<T> from_string(const std::string& str,
                            std::nothrow_t /*nothrow*/,
                            std::string::size_type* endpos_out /*= NULL*/)
{
	try {
		return from_string<T>(str, endpos_out);
	}
	catch (const std::logic_error&) {
		return ft::nullopt;
	}
}

template <typename T>
T from_string(const std::string& str,
              std::ios::fmtflags fmt,
              std::string::size_type* endpos_out /*= NULL*/)
{
	if (endpos_out) {
		*endpos_out = 0;
	}
	T res;
	std::istringstream iss(str);
	iss.flags(fmt);

	if (iss >> res) {
		if (endpos_out) {
			*endpos_out = ft::min(
			    static_cast<std::string::size_type>(iss.tellg()), str.length());
		}
		// Check for negative value for unsigned integer types
		if (std::numeric_limits<T>::is_integer && !ft::is_same<T, bool>::value
		    && std::numeric_limits<T>::min() == 0) {
			if (std::signbit(
			        from_string<float>(str, fmt, std::nothrow).value_or(-1))) {
				throw _from_string::out_of_range<T>(str);
			}
		}
		return res;
	}

	/* Error handling */

	if (!(fmt & std::ios::skipws) && std::isspace(*str.c_str())) {
		throw _from_string::invalid_argument<T>(str);
	}

	// Check if integer type out of range
	if (std::numeric_limits<T>::is_integer) {
		const char* const start = str.c_str();
		char* end = NULL;

		// strtol works even for unsigned long since valid numbers between
		// LONG_MAX and ULONG_MAX would not get here
		errno = 0;
		const long test = std::strtol(start, &end, 0);
		if (errno == ERANGE
		    || test < static_cast<long>(std::numeric_limits<T>::min())
		    || static_cast<unsigned long>(test) > static_cast<unsigned long>(
		           std::numeric_limits<T>::max())) {
			if (endpos_out && end) {
				*endpos_out = end - start;
			}
			throw _from_string::out_of_range<T>(str);
		}
	}
	// Check if floating point type out of range
	else if (std::numeric_limits<T>::is_iec559) {
		const char* const start = str.c_str();
		char* end = NULL;

		errno = 0;
		if (ft::is_same<T, float>::value) {
			res = std::strtof(start, &end);
		}
		else if (ft::is_same<T, double>::value) {
			res = std::strtod(start, &end);
		}
		else {
			res = std::strtold(start, &end);
		}
		if (endpos_out && end) {
			*endpos_out = end - start;
		}
		if (errno == ERANGE) {
			throw _from_string::out_of_range<T>(str);
		}
		// stringstream does not detect special floating point values
		if (std::isinf(res) || std::isnan(res)) {
			return res;
		}
	}
	// Invalid string
	throw _from_string::invalid_argument<T>(str);
}

template <typename T>
ft::Optional<T> from_string(const std::string& str,
                            std::ios::fmtflags fmt,
                            std::nothrow_t /*nothrow*/,
                            std::string::size_type* endpos_out /*= NULL*/)
{
	try {
		return from_string<T>(str, fmt, endpos_out);
	}
	catch (const std::logic_error&) {
		return ft::nullopt;
	}
}

namespace _from_string {

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

} // namespace _from_string

} // namespace ft
