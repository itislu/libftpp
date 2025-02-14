#pragma once

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#define BOLD(str)  std::string() + "\033[1m" + str + "\033[0m"
#define RED(str)   std::string() + "\033[31m" + str + "\033[0m"
#define GREEN(str) std::string() + "\033[32m" + str + "\033[0m"

#define WHERE(msg) utils::where(__FILE__, __LINE__, (msg))

namespace utils {

template <typename T>
void swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template <typename T>
std::string where(const char* file, size_t line, const T& msg)
{
	std::ostringstream os;
	std::ostringstream os_msg;

	os << file << ":" << line;
	os_msg << msg;
	if (!os_msg.str().empty()) {
		os << ": " << os_msg.str();
	}
	return os.str();
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

namespace log {

	const size_t g_label_width = 25;

	template <typename T>
	std::string error(const T& msg)
	{
		std::ostringstream os;
		os << std::left << std::setw(g_label_width) << BOLD(RED("[ERROR]"))
		   << msg;
		return os.str();
	}

	template <typename T>
	std::string ok(const T& msg)
	{
		std::ostringstream os;
		os << std::left << std::setw(g_label_width) << BOLD(GREEN("[OK]"))
		   << msg;
		return os.str();
	}

} // namespace log

} // namespace utils
