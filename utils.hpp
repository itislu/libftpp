#ifndef SWAP_HPP
#define SWAP_HPP

#include <cstddef>
#include <sstream>
#include <string>

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

} // namespace utils

#endif
