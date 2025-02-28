#pragma once

#include "string.hpp"
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
namespace string {

template <typename T>
T from_string(const std::string& str)
{
	T res;

	/* floating-point */
	if (std::numeric_limits<T>::is_specialized
	    && !std::numeric_limits<T>::is_integer) {
		const char* start = str.c_str();
		char* end = NULL;
		errno = 0;

		switch (std::numeric_limits<T>::max_exponent) {
		case FLT_MAX_EXP:
			res = strtof(start, &end);
			break;
		case DBL_MAX_EXP:
			res = strtod(start, &end);
			break;
		default:
			res = strtold(start, &end);
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

	/* every other type */
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

template <typename T>
std::string to_string(T v)
{
	std::ostringstream oss;
	oss << v;
	return oss.str();
}

template <typename T>
std::string to_string(T* v)
{
	if (v == NULL) {
		return "(null)";
	}
	std::ostringstream oss;
	oss << v;
	return oss.str();
}

template <>
inline std::string to_string(bool v)
{
	return v ? "true" : "false";
}

template <typename InputIterator,
          typename OutputIterator,
          typename UnaryOperator>
OutputIterator transform(InputIterator first,
                         InputIterator last,
                         OutputIterator result,
                         UnaryOperator op)
{
	while (first != last) {
		*result = op(*first);
		++result;
		++first;
	}
	return result;
}

} // namespace string
} // namespace utils
