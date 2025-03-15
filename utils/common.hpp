#pragma once

#include <cstddef>
#include <ios>
#include <string>

#define BOLD(msg)   (std::string("\033[1m") + msg + "\033[0m")
#define RED(msg)    (std::string("\033[31m") + msg + "\033[0m")
#define GREEN(msg)  (std::string("\033[32m") + msg + "\033[0m")
#define YELLOW(msg) (std::string("\033[33m") + msg + "\033[0m")
#define BLUE(msg)   (std::string("\033[34m") + msg + "\033[0m")
#define GRAY(msg)   (std::string("\033[37m") + msg + "\033[0m")

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define WHERE             (utils::where(__FILE__, __LINE__, __FUNCTION__))

namespace utils {

std::string where(const char* file, size_t line, const char* function);

template <typename T>
void swap(T& a, T& b);

template <typename T>
void rand(T* v, std::streamsize size);

} // namespace utils

#include "common.tpp" // IWYU pragma: export
