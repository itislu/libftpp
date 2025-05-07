#pragma once

#include "../../Expected.hpp"
#include "../../algorithm.hpp"
#include "../../string.hpp"
#include "../../type_traits.hpp"
#include <cctype>
#include <cerrno>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <new>
#include <sstream>
#include <string>

namespace ft {

namespace _from_string {
template <typename T>
static void check_unwanted_scientific_notation(const std::string& str,
                                               std::ios::fmtflags fmt,
                                               std::string::size_type& endpos);
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
	catch (const FromStringException&) {
		return from_string<bool>(str, std::ios::fmtflags(), endpos_out);
	}
}

template <typename T>
T from_string(const std::string& str,
              std::ios::fmtflags fmt,
              std::string::size_type* endpos_out /*= NULL*/)
{
	std::string::size_type _; // NOLINT(cppcoreguidelines-init-variables)
	std::string::size_type& endpos = endpos_out ? *endpos_out : _;
	endpos = 0;
	T res;
	std::istringstream iss(str);
	iss.flags(fmt);

	if (iss >> res) {
		endpos = ft::min(static_cast<std::string::size_type>(iss.tellg()),
		                 str.length());
		// Check for negative value for unsigned integer types
		if (std::numeric_limits<T>::is_integer && !ft::is_same<T, bool>::value
		    && std::numeric_limits<T>::min() == 0) {
			if (std::signbit(
			        from_string<float>(str, fmt, std::nothrow).value_or(-1))) {
				throw FromStringRangeException(str, typeid(T));
			}
		}
		else if (std::numeric_limits<T>::is_iec559) {
			_from_string::check_unwanted_scientific_notation<T>(
			    str, fmt, endpos);
		}
		return res;
	}

	/* Error handling */

	if (!(fmt & std::ios::skipws) && std::isspace(*str.c_str())) {
		throw FromStringInvalidException(str, typeid(T));
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
			if (end) {
				endpos = end - start;
			}
			throw FromStringRangeException(str, typeid(T));
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
		if (end) {
			endpos = end - start;
		}

		_from_string::check_unwanted_scientific_notation<T>(str, fmt, endpos);
		if (errno == ERANGE) {
			throw FromStringRangeException(str, typeid(T));
		}
		// stringstream does not detect special floating point values
		if (std::isinf(res) || std::isnan(res)) {
			return res;
		}
	}
	// Invalid string
	throw FromStringInvalidException(str, typeid(T));
}

template <typename T>
ft::Expected<T, ft::FromStringException>
from_string(const std::string& str,
            std::nothrow_t /*nothrow*/,
            std::string::size_type* endpos_out /*= NULL*/)
{
	try {
		return from_string<T>(str, endpos_out);
	}
	catch (const FromStringException& e) {
		return ft::Unexpected<FromStringException>(e);
	}
}

template <typename T>
ft::Expected<T, ft::FromStringException>
from_string(const std::string& str,
            std::ios::fmtflags fmt,
            std::nothrow_t /*nothrow*/,
            std::string::size_type* endpos_out /*= NULL*/)
{
	try {
		return from_string<T>(str, fmt, endpos_out);
	}
	catch (const FromStringException& e) {
		return ft::Unexpected<FromStringException>(e);
	}
}

namespace _from_string {

template <typename T>
static void check_unwanted_scientific_notation(const std::string& str,
                                               std::ios::fmtflags fmt,
                                               std::string::size_type& endpos)
{
	if (std::numeric_limits<T>::is_iec559
	    && (fmt & std::ios::floatfield) == std::ios::fixed) {
		const std::string unwanted("eEpP");
		const std::string::const_iterator end =
		    str.begin() + static_cast<std::string::difference_type>(endpos);

		if (ft::find_first_of(
		        str.begin(), end, unwanted.begin(), unwanted.end())
		    != end) {
			endpos = 0;
			throw FromStringInvalidException(str, typeid(T));
		}
	}
}

} // namespace _from_string

} // namespace ft
