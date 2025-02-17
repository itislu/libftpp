#include "common.hpp"
#include <cstddef>
#include <sstream>
#include <string>

namespace utils {

std::string where(const char* file, size_t line, const char* function)
{
	std::ostringstream os;

	os << file << ":" << line << ": " << function;
	return os.str();
}

} // namespace utils
