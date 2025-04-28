#pragma once

#include "../../string.hpp"
#include <cstddef>
#include <ios>
#include <sstream>
#include <string>

namespace ft {

namespace _to_string {
template <typename T>
static std::string to_string(T v, std::ios::fmtflags fmt);
template <typename T>
static std::string to_string(T* v, std::ios::fmtflags fmt);
} // namespace _to_string

template <typename T>
std::string to_string(T v, std::ios::fmtflags fmt /*= std::ios::fmtflags()*/)
{
	return _to_string::to_string(v, fmt);
}

namespace _to_string {

template <typename T>
static std::string to_string(T v, std::ios::fmtflags fmt)
{
	std::ostringstream oss;
	oss.flags(fmt);
	oss << v;
	return oss.str();
}

template <typename T>
static std::string to_string(T* v, std::ios::fmtflags fmt)
{
	std::ostringstream oss;
	oss.flags(fmt);
	if (v == NULL) {
		oss << "(null)";
	}
	else {
		oss << v;
	}
	return oss.str();
}

} // namespace _to_string

} // namespace ft
