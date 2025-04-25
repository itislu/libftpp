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
	if (v == NULL) {
		oss << "(null)";
	}
	else {
		oss << v;
	}
	return oss.str();
}

} // namespace ft
