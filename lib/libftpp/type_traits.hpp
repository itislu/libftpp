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
#define HAS_METHOD(RETURN_TYPE, METHOD_NAME, ARGS)                           \
	template <typename T>                                                    \
	struct has_##METHOD_NAME {                                               \
	private:                                                                 \
		/* 2nd param: member-function pointer non-type template parameter */ \
		template <typename ToCheck, RETURN_TYPE (ToCheck::*)(ARGS)>          \
		struct Sfinae {};                                                    \
                                                                             \
		typedef char yes[1];                                                 \
		typedef char no[2];                                                  \
                                                                             \
		template <typename ToCheck>                                          \
		static yes& test(Sfinae<ToCheck, &ToCheck::METHOD_NAME>*);           \
		template <typename>                                                  \
		static no& test(...);                                                \
                                                                             \
	public:                                                                  \
		enum {                                                               \
			value = sizeof(test<T>(NULL)) == sizeof(yes)                     \
		};                                                                   \
	};

HAS_METHOD(void, swap, ToCheck&)

#undef HAS_METHOD

} // namespace ft
