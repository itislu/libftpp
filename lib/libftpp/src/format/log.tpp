#pragma once

#include "../../format.hpp"
#include <iomanip>
#include <ios>
#include <sstream>
#include <string>

namespace ft {
namespace log {

template <typename T>
std::string ok(const T& msg)
{
	std::ostringstream os;
	os << std::left << std::setw(label_width_colored) << BOLD(GREEN("[OK]"))
	   << msg;
	return os.str();
}

template <typename T>
std::string info(const T& msg)
{
	std::ostringstream os;
	os << std::left << std::setw(label_width_colored) << BOLD(BLUE("[INFO]"))
	   << msg;
	return os.str();
}

template <typename T>
std::string warn(const T& msg)
{
	std::ostringstream os;
	os << std::left << std::setw(label_width_colored) << BOLD(YELLOW("[WARN]"))
	   << msg;
	return os.str();
}

template <typename T>
std::string error(const T& msg)
{
	std::ostringstream os;
	os << std::left << std::setw(label_width_colored) << BOLD(RED("[ERROR]"))
	   << msg;
	return os.str();
}

template <typename T>
std::string line(const T& msg)
{
	std::ostringstream os;
	os << '\n' << std::left << std::setw(label_width_text) << "" << msg;
	return os.str();
}

} // namespace log
} // namespace ft
