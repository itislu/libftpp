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

	/* bool */
	if (std::numeric_limits<T>::digits == 1) {
		if (!(std::istringstream(str) >> std::boolalpha >> res)
		    && !(std::istringstream(str) >> res)) {
			goto invalid_argument;
		}
		return res;
	}

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
			goto out_of_range;
		}
		if (end == start) {
			goto invalid_argument;
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
				goto out_of_range;
			}
		}
		goto invalid_argument;
	}
	return res;

out_of_range:
	throw std::out_of_range(strerror(ERANGE));

invalid_argument:
	throw std::invalid_argument(std::string("Cannot convert to ")
	                            + typeid(T).name() + ": " + str);
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
