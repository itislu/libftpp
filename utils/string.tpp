#pragma once

#include "string.hpp"
#include <cerrno>
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
float from_string(const std::string& str)
{
	const char* start = str.c_str();
	char* end = NULL;
	errno = 0;

	const float f = strtof(start, &end);
	if (errno == ERANGE) {
		throw std::out_of_range(strerror(ERANGE));
	}
	if (end == start) {
		throw std::invalid_argument(std::string("Cannot convert to ")
		                            + typeid(float).name() + ": " + str);
	}
	return f;
}

template <>
double from_string(const std::string& str)
{
	const char* start = str.c_str();
	char* end = NULL;
	errno = 0;

	const double d = strtod(start, &end);
	if (errno == ERANGE) {
		throw std::out_of_range(strerror(ERANGE));
	}
	if (end == start) {
		throw std::invalid_argument(std::string("Cannot convert to ")
		                            + typeid(double).name() + ": " + str);
	}
	return d;
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
