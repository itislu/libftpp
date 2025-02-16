#pragma once

#include <cstddef>
#include <string>

#define BOLD(str)  std::string() + "\033[1m" + str + "\033[0m"
#define RED(str)   std::string() + "\033[31m" + str + "\033[0m"
#define GREEN(str) std::string() + "\033[32m" + str + "\033[0m"
#define BLUE(str)  std::string() + "\033[34m" + str + "\033[0m"
#define GRAY(str)  std::string() + "\033[37m" + str + "\033[0m"

#define WHERE utils::where(__FILE__, __LINE__, __FUNCTION__)

namespace utils {

std::string where(const char* file, size_t line, const char* function);

template <typename T>
void swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

} // namespace utils
