#pragma once

#include <cstddef>
#include <ios>
#include <string>

#define BOLD(msg)      (std::string("\033[1m") + msg + "\033[0m")
#define ITALIC(msg)    (std::string("\033[3m") + msg + "\033[0m")
#define UNDERLINE(msg) (std::string("\033[4m") + msg + "\033[0m")
#define RED(msg)       (std::string("\033[31m") + msg + "\033[0m")
#define GREEN(msg)     (std::string("\033[32m") + msg + "\033[0m")
#define YELLOW(msg)    (std::string("\033[33m") + msg + "\033[0m")
#define BLUE(msg)      (std::string("\033[34m") + msg + "\033[0m")
#define MAGENTA(msg)   (std::string("\033[35m") + msg + "\033[0m")
#define CYAN(msg)      (std::string("\033[36m") + msg + "\033[0m")
#define GRAY(msg)      (std::string("\033[37m") + msg + "\033[0m")

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

#if defined(__GNUC__) // GCC, Clang, ICC
#	define UNREACHABLE() (__builtin_unreachable())
#elif defined(_MSC_VER) // MSVC
#	define UNREACHABLE() (__assume(false))
#else
#	include <exception>
#	define UNREACHABLE() (std::terminate())
#endif

#define WHERE (ft::where(__FILE__, __LINE__, __FUNCTION__))

namespace ft {

std::string where(const char* file, size_t line, const char* function);

template <typename T>
void urandom(T* v, std::streamsize size);
template <typename T>
T urandom();

} // namespace ft

#include "src/common.tpp" // IWYU pragma: export
