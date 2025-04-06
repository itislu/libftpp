#pragma once

#include <cstddef>
#include <ios>
#include <string>

#define BOLD(MSG)      (std::string("\033[1m") + MSG + "\033[0m")
#define ITALIC(MSG)    (std::string("\033[3m") + MSG + "\033[0m")
#define UNDERLINE(MSG) (std::string("\033[4m") + MSG + "\033[0m")
#define RED(MSG)       (std::string("\033[31m") + MSG + "\033[0m")
#define GREEN(MSG)     (std::string("\033[32m") + MSG + "\033[0m")
#define YELLOW(MSG)    (std::string("\033[33m") + MSG + "\033[0m")
#define BLUE(MSG)      (std::string("\033[34m") + MSG + "\033[0m")
#define MAGENTA(MSG)   (std::string("\033[35m") + MSG + "\033[0m")
#define CYAN(MSG)      (std::string("\033[36m") + MSG + "\033[0m")
#define GRAY(MSG)      (std::string("\033[37m") + MSG + "\033[0m")

#define ARRAY_SIZE(ARRAY) (sizeof(ARRAY) / sizeof(ARRAY[0]))

#if defined(__GNUC__) // GCC, Clang, ICC
#	define WHERE (ft::where(__FILE__, __LINE__, __PRETTY_FUNCTION__))
#elif defined(_MSC_VER) // MSVC
#	define WHERE (ft::where(__FILE__, __LINE__, __FUNCSIG__))
#else
#	define WHERE (ft::where(__FILE__, __LINE__, __func__))
#endif

namespace ft {

std::string where(const char* file, std::size_t line, const char* function);

template <typename T>
void urandom(T* v, std::streamsize size);
template <typename T>
T urandom();

} // namespace ft

#include "src/common.tpp" // IWYU pragma: export
