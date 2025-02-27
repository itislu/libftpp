#pragma once

#include "string.hpp"
#include <cstddef>
#include <iostream>
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
