#include "../common.hpp"
#include <cstddef>
#include <sstream>
#include <string>

namespace ft {

std::string where(const char* file, std::size_t line, const char* function)
{
	std::ostringstream os;

	os << file << ":" << line << ": " << function;
	return os.str();
}

} // namespace ft
