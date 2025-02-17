#pragma once

#include <cstddef>
#include <fstream>
#include <ios>
#include <string>

#define BOLD(str)   std::string() + "\033[1m" + str + "\033[0m"
#define RED(str)    std::string() + "\033[31m" + str + "\033[0m"
#define GREEN(str)  std::string() + "\033[32m" + str + "\033[0m"
#define YELLOW(str) std::string() + "\033[33m" + str + "\033[0m"
#define BLUE(str)   std::string() + "\033[34m" + str + "\033[0m"
#define GRAY(str)   std::string() + "\033[37m" + str + "\033[0m"

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
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

// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
template <typename T>
void rand(T* v, std::streamsize size)
{
	std::ifstream urandom;

	urandom.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	urandom.open("/dev/urandom", std::ios::binary);
	urandom.read(reinterpret_cast<char*>(v), size);
	urandom.close();
}
// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)

} // namespace utils
