#pragma once

#include "../../Expected.hpp"
#include "../../algorithm.hpp"
#include "../../iterator.hpp"
#include "../../string.hpp"
#include "../../type_traits.hpp"
#include <algorithm>
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
template <typename To>
static void
check_negative_unsigned_integral(const std::string& str,
                                 const std::string::size_type& endpos);
template <typename To>
static void check_unwanted_scientific_notation(const std::string& str,
                                               std::ios::fmtflags fmt,
                                               std::string::size_type& endpos);
} // namespace _from_string

template <typename To>
To from_string(const std::string& str,
               std::string::size_type* endpos_out /*= NULL*/)
{
	return from_string<To>(str, std::ios::fmtflags(), endpos_out);
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

template <typename To>
To from_string(const std::string& str,
               std::ios::fmtflags fmt,
               std::string::size_type* endpos_out /*= NULL*/)
{
	// NOLINTNEXTLINE: Let endpos always be a valid reference
	std::string::size_type _, &endpos = (endpos_out ? *endpos_out : _) = 0;
	To res;
	std::istringstream iss(str);
	iss.flags(fmt);

	if (iss >> res) {
		endpos = ft::min(static_cast<std::string::size_type>(iss.tellg()),
		                 str.length());
		if (ft::is_integral<To>::value) {
			// stringstream wraps negative values for unsigend integer types
			_from_string::check_negative_unsigned_integral<To>(str, endpos);
		}
		else if (ft::is_floating_point<To>::value) {
			_from_string::check_unwanted_scientific_notation<To>(
			    str, fmt, endpos);
		}
		return res;
	}

	/* Error handling */

	if (ft::is_same<To, bool>::value && fmt & std::ios::boolalpha) {
		throw FromStringInvalidException(str, typeid(To));
	}
	if (!(fmt & std::ios::skipws) && std::isspace(*str.c_str())) {
		throw FromStringInvalidException(str, typeid(To));
	}

	// Check if integer type out of range
	if (ft::is_integral<To>::value) {
		const char* const start = str.c_str();
		char* end = NULL;

		// strtol works even for unsigned long since valid numbers between
		// LONG_MAX and ULONG_MAX would not get here
		errno = 0;
		const long test = std::strtol(start, &end, 0);
		if (errno == ERANGE
		    || test < static_cast<long>(std::numeric_limits<To>::min())
		    || static_cast<unsigned long>(test) > static_cast<unsigned long>(
		           std::numeric_limits<To>::max())) {
			if (end != NULL) {
				endpos = end - start;
			}
			throw FromStringRangeException(str, typeid(To));
		}
	}
	// Check if floating point type out of range
	else if (ft::is_floating_point<To>::value) {
		const char* const start = str.c_str();
		char* end = NULL;

		errno = 0;
		if (ft::is_same<To, float>::value) {
			res = std::strtof(start, &end);
		}
		else if (ft::is_same<To, double>::value) {
			res = std::strtod(start, &end);
		}
		else {
			res = std::strtold(start, &end);
		}
		if (end != NULL) {
			endpos = end - start;
		}

		_from_string::check_unwanted_scientific_notation<To>(str, fmt, endpos);
		if (errno == ERANGE) {
			throw FromStringRangeException(str, typeid(To));
		}
		// stringstream does not detect special floating point values
		if (std::isinf(res) || std::isnan(res)) {
			return res;
		}
	}
	// Invalid string
	throw FromStringInvalidException(str, typeid(To));
}

template <typename To>
ft::Expected<To, ft::FromStringException>
from_string(const std::string& str,
            std::nothrow_t /*nothrow*/,
            std::string::size_type* endpos_out /*= NULL*/)
{
	try {
		return from_string<To>(str, endpos_out);
	}
	catch (const FromStringException& e) {
		return ft::Unexpected<FromStringException>(e);
	}
}

template <typename To>
ft::Expected<To, ft::FromStringException>
from_string(const std::string& str,
            std::ios::fmtflags fmt,
            std::nothrow_t /*nothrow*/,
            std::string::size_type* endpos_out /*= NULL*/)
{
	try {
		return from_string<To>(str, fmt, endpos_out);
	}
	catch (const FromStringException& e) {
		return ft::Unexpected<FromStringException>(e);
	}
}

namespace _from_string {

template <typename To>
static void
check_negative_unsigned_integral(const std::string& str,
                                 const std::string::size_type& endpos)
{
	if (ft::is_integral<To>::value && !ft::is_same<To, bool>::value
	    && std::numeric_limits<To>::min() == 0) {
		const std::string::const_iterator end =
		    str.begin() + static_cast<std::string::difference_type>(endpos);
		const std::string::const_iterator minus =
		    std::find(str.begin(), end, '-');
		if (minus == end) {
			return;
		}

		const char not_zero[] = "123456789abcdefABCDEF";
		if (ft::find_first_of(
		        minus, end, ft::begin(not_zero), ft::prev(ft::end(not_zero)))
		    != end) {
			throw FromStringRangeException(str, typeid(To));
		}
	}
}

template <typename To>
static void check_unwanted_scientific_notation(const std::string& str,
                                               std::ios::fmtflags fmt,
                                               std::string::size_type& endpos)
{
	if (ft::is_floating_point<To>::value
	    && (fmt & std::ios::floatfield) == std::ios::fixed) {
		const std::string::const_iterator end =
		    str.begin() + static_cast<std::string::difference_type>(endpos);

		const char scientific_notation[] = "eEpP";
		if (ft::find_first_of(str.begin(),
		                      end,
		                      ft::begin(scientific_notation),
		                      ft::prev(ft::end(scientific_notation)))
		    != end) {
			endpos = 0; // For consistency with other invalid cases
			throw FromStringInvalidException(str, typeid(To));
		}
	}
}

} // namespace _from_string

} // namespace ft
