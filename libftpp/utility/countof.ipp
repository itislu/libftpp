#pragma once

/**
 * Inspiration:
 * https://web.archive.org/web/20141223215212/http://www.drdobbs.com/cpp/counting-array-elements-at-compile-time/197800525?pgno=6
 */
// clang-format off
// NOLINTBEGIN
#define COUNTOF_IMPL(ARRAY)                                                                  \
	((0 * sizeof(reinterpret_cast<const volatile ft::_countof::Bad_arg_to_COUNTOF*>(ARRAY))) \
	 + (0 * sizeof(ft::_countof::Bad_arg_to_COUNTOF::check_type((ARRAY), &(ARRAY))))         \
	 + (sizeof(ARRAY) / sizeof((ARRAY)[0])))
// NOLINTEND
// clang-format on

namespace ft {
namespace _countof {

struct Bad_arg_to_COUNTOF {
public:
	struct IsPointer; // Intentionally incomplete type.
	struct IsArray {};

	template <typename T>
	static IsPointer check_type(T*, T* const volatile*);
	static IsArray check_type(const volatile void*, const volatile void*);
};

} // namespace _countof
} // namespace ft
