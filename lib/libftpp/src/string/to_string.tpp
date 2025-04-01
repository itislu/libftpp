#pragma once

#include "../../string.hpp"
#include <cstddef>
#include <ios>
#include <sstream>
#include <string>

namespace ft {

template <typename T>
std::string to_string(T v, std::ios::fmtflags fmt /*= std::ios::fmtflags()*/)
{
	std::ostringstream oss;
	oss.flags(fmt);
	oss << v;
	return oss.str();
}

template <typename T>
std::string to_string(T* v, std::ios::fmtflags fmt /*= std::ios::fmtflags()*/)
{
	std::ostringstream oss;
	oss.flags(fmt);
	oss << (v == NULL ? "(null)" : v);
	return oss.str();
}

} // namespace ft
