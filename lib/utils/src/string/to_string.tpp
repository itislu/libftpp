#pragma once

#include "../../string.hpp"
#include <cerrno>
#include <cfloat>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>

namespace utils {

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

} // namespace utils
