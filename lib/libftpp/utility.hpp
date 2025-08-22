#pragma once

#include "src/utility/countof.ipp"
#include <string>

/**
 * https://en.cppreference.com/w/cpp/utility/unreachable
 */
#if defined(__GNUC__) || defined(__clang__)
#	define UNREACHABLE() (__builtin_unreachable())
#elif defined(_MSC_VER)
#	define UNREACHABLE() (__assume(false))
#else
#	include <exception>
#	define UNREACHABLE() (std::terminate())
#endif

/**
 * @brief Macro to get the length of a C-array at compile time in a type-safe
 * manner
 *
 * Inspiration:
 * https://drdobbs.com/cpp/counting-array-elements-at-compile-time/197800525?pgno=6
 */
#define COUNTOF(ARRAY) COUNTOF_IMPL(ARRAY)

namespace ft {

std::string demangle(const char* mangled_name);

} // namespace ft
