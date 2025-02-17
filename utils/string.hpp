#pragma once

#include <cstddef>
#include <sstream>
#include <string>

namespace utils {
namespace string {

std::string& trim(std::string& str);
std::string trim(const std::string& str);

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

} // namespace string
} // namespace utils
