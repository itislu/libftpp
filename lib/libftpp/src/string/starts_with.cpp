#include "../../string.hpp"
#include <string>

namespace ft {

bool starts_with(const std::string& str, const std::string& prefix)
{
	if (str.length() < prefix.length()) {
		return false;
	}
	return str.compare(0, prefix.length(), prefix) == 0;
}

bool starts_with(const std::string& str, char prefix)
{
	return !str.empty() && str[0] == prefix;
}

bool starts_with(const std::string& str, unsigned char prefix)
{
	return !str.empty() && static_cast<unsigned char>(str[0]) == prefix;
}

} // namespace ft
