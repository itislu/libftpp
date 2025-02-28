#include "string.hpp"
#include <cctype>
#include <string>

namespace utils {
namespace string {

std::string& trim(std::string& str)
{
	std::string::iterator start = str.begin();
	while (start != str.end() && std::isspace(*start) != 0) {
		++start;
	}
	str.erase(str.begin(), start);
	if (str.empty()) {
		return str;
	}
	std::string::iterator end = str.end() - 1;
	while (std::isspace(*end) != 0) {
		--end;
	}
	str.erase(end + 1, str.end());
	return str;
}

std::string trim(const std::string& str)
{
	std::string new_str(str);
	return trim(new_str);
}

} // namespace string
} // namespace utils

#ifdef TEST_STRING
#include "common.hpp"
#include <iostream>

int main()
{
	std::string tests[] = {"  Hello World  ",
	                       "   ",
	                       "Hello",
	                       "",
	                       " a ",
	                       "a ",
	                       " a",
	                       " ",
	                       "Hey there"};

	for (unsigned int i = 0; i < ARRAY_SIZE(tests); ++i) {
		std::cout << "'" << utils::string::trim(tests[i]) << "'" << '\n';
	}
}
#endif
