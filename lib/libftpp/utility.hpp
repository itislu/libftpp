#pragma once

/**
 * https://en.cppreference.com/w/cpp/utility/unreachable
 */
#if defined(__GNUC__) // GCC, Clang, ICC
#	define UNREACHABLE() (__builtin_unreachable())
#elif defined(_MSC_VER) // MSVC
#	define UNREACHABLE() (__assume(false))
#else
#	include <exception>
#	define UNREACHABLE() (std::terminate())
#endif
