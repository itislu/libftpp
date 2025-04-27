#pragma once

#include <string>

/**
 * https://en.cppreference.com/w/cpp/utility/unreachable
 */
#if defined(__GNUC__) || defined(__clang__) // GCC, Clang, ICC
#	define UNREACHABLE() (__builtin_unreachable())
#elif defined(_MSC_VER) // MSVC
#	define UNREACHABLE() (__assume(false))
#else
#	include <exception>
#	define UNREACHABLE() (std::terminate())
#endif

/**
 * Macro to get the length of a C-array at compile time in a type-safe manner.
 * https://drdobbs.com/cpp/counting-array-elements-at-compile-time/197800525?pgno=6
 */
// clang-format off
// NOLINTBEGIN
#define COUNTOF(ARRAY)                                                                       \
	((0 * sizeof(reinterpret_cast<const volatile ft::_countof::Bad_arg_to_COUNTOF*>(ARRAY))) \
	 + (0 * sizeof(ft::_countof::Bad_arg_to_COUNTOF::check_type((ARRAY), &(ARRAY))))         \
	 + (sizeof(ARRAY) / sizeof((ARRAY)[0])))
// NOLINTEND
// clang-format on

namespace ft {
namespace _countof {

struct Bad_arg_to_COUNTOF {
public:
	struct IsPointer; // intentionally incomplete type
	struct IsArray {};

	template <typename T>
	static IsPointer check_type(const volatile T*, const volatile T**);
	static IsArray check_type(const volatile void*, const volatile void*);
};

} // namespace _countof
} // namespace ft

namespace ft {

std::string demangle(const char* mangled_name);

} // namespace ft
