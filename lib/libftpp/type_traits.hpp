#pragma once

#include <cstddef>

namespace ft {

/**
 * https://en.cppreference.com/w/cpp/types/enable_if
 */
template <bool B, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
	typedef T type;
};

/**
 * Generates type traits that check if a class has a specific method.
 * The generated type traits are named has_<method_name>.
 */
#define HAS_METHOD(NAME, SIGNATURE)                      \
	template <typename T>                                \
	struct has_##NAME {                                  \
	private:                                             \
		template <typename U, SIGNATURE>                 \
		struct Sfinae {};                                \
                                                         \
		typedef char yes[1];                             \
		typedef char no[2];                              \
                                                         \
		template <typename U>                            \
		static yes& test(Sfinae<U, &U::NAME>*);          \
		template <typename U>                            \
		static no& test(...);                            \
                                                         \
	public:                                              \
		enum {                                           \
			value = sizeof(test<T>(NULL)) == sizeof(yes) \
		};                                               \
	};

HAS_METHOD(swap, void (U::*)(U&))

#undef HAS_METHOD

} // namespace ft
