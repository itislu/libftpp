#include "../../string.hpp"
#include <string>

namespace ft {

bool ends_with(const std::string& str, const std::string& suffix)
{
	if (str.length() < suffix.length()) {
		return false;
	}
	return str.compare(str.length() - suffix.length(), suffix.length(), suffix)
	       == 0;
}

bool ends_with(const std::string& str, char suffix)
{
	return !str.empty() && str[str.length() - 1] == suffix;
}

bool ends_with(const std::string& str, unsigned char suffix)
{
	return !str.empty()
	       && static_cast<unsigned char>(str[str.length() - 1]) == suffix;
}

} // namespace ft
