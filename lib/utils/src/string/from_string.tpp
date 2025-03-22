#pragma once

#include "../../string.hpp"
#include <cerrno>
#include <cfloat>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace utils {
namespace _string {

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
		throw std::out_of_range(strerror(ERANGE));
	}
	if (end == start) {
		throw std::invalid_argument(std::string("Cannot convert to ")
		                            + typeid(T).name() + ": " + str);
	}
	return res;
}

} // namespace _string

template <typename T>
T from_string(const std::string& str)
{
	T res;

	if (!(std::istringstream(str) >> res)) {
		if (std::numeric_limits<T>::is_integer) {
			const char* start = str.c_str();
			char* end = NULL;

			(void)strtol(start, &end, 0);
			if (end != start) {
				throw std::out_of_range(strerror(ERANGE));
			}
		}
		throw std::invalid_argument(std::string("Cannot convert to ")
		                            + typeid(T).name() + ": " + str);
	}
	return res;
}

template <>
inline bool from_string<bool>(const std::string& str)
{
	bool b = false;

	if (!(std::istringstream(str) >> std::boolalpha >> b)
	    && !(std::istringstream(str) >> b)) {
		throw std::invalid_argument(std::string("Cannot convert to ")
		                            + typeid(bool).name() + ": " + str);
	}
	return b;
}

template <>
float from_string<float>(const std::string& str)
{
	return _string::from_string_floating_point<float>(str);
}

template <>
double from_string<double>(const std::string& str)
{
	return _string::from_string_floating_point<double>(str);
}

template <>
long double from_string<long double>(const std::string& str)
{
	return _string::from_string_floating_point<long double>(str);
}

} // namespace utils
