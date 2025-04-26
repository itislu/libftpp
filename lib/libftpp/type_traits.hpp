#pragma once

#include <cstddef>

namespace ft {

/* Base classes */

/**
 * https://en.cppreference.com/w/cpp/types/integral_constant
 */
template <typename T, T v>
struct integral_constant {
	static const T value = v;
	typedef T value_type;
	typedef integral_constant type;

	operator value_type() const throw() { return value; }
	value_type operator()() const throw() { return value; }
};

template <bool B>
struct bool_constant : integral_constant<bool, B> {};

typedef bool_constant<true> true_type;
typedef bool_constant<false> false_type;

/**
 * https://en.cppreference.com/w/cpp/types/type_identity
 */
template <typename T>
struct type_identity {
	typedef T type;
};

/* Unary type traits */

/**
 * https://en.cppreference.com/w/cpp/types/is_void
 */
template <typename>
struct is_void;

/**
 * https://en.cppreference.com/w/cpp/types/is_array
 */
template <typename>
struct is_array;

/**
 * https://en.cppreference.com/w/cpp/types/is_pointer
 */
template <typename>
struct is_pointer;

/**
 * https://en.cppreference.com/w/cpp/types/is_reference
 */
template <typename>
struct is_reference;

/**
 * https://en.cppreference.com/w/cpp/types/is_const
 */
template <typename>
struct is_const;

/**
 * https://en.cppreference.com/w/cpp/types/is_volatile
 */
template <typename>
struct is_volatile;

/**
 * https://en.cppreference.com/w/cpp/types/is_bounded_array
 */
template <typename>
struct is_bounded_array;

/**
 * https://en.cppreference.com/w/cpp/types/is_unbounded_array
 */
template <typename>
struct is_unbounded_array;

/* Property queries */

/**
 * https://en.cppreference.com/w/cpp/types/rank
 */
template <typename>
struct rank;

/**
 * https://en.cppreference.com/w/cpp/types/extent
 */
template <typename, unsigned N = 0>
struct extent;

/* Type relationships */

/**
 * https://en.cppreference.com/w/cpp/types/is_same
 */
template <typename, typename>
struct is_same;

/* Type transformations */

/**
 * https://en.cppreference.com/w/cpp/types/remove_cv
 */
template <typename>
struct remove_cv;

/**
 * https://en.cppreference.com/w/cpp/types/remove_cv
 */
template <typename>
struct remove_const;

/**
 * https://en.cppreference.com/w/cpp/types/remove_cv
 */
template <typename>
struct remove_volatile;

/**
 * https://en.cppreference.com/w/cpp/types/add_cv
 */
template <typename>
struct add_cv;

/**
 * https://en.cppreference.com/w/cpp/types/add_cv
 */
template <typename>
struct add_const;

/**
 * https://en.cppreference.com/w/cpp/types/add_cv
 */
template <typename>
struct add_volatile;

/**
 * https://en.cppreference.com/w/cpp/types/remove_extent
 */
template <typename>
struct remove_extent;

/**
 * https://en.cppreference.com/w/cpp/types/remove_all_extents
 */
template <typename>
struct remove_all_extents;

/**
 * https://en.cppreference.com/w/cpp/types/remove_pointer
 */
template <typename>
struct remove_pointer;

/**
 * https://en.cppreference.com/w/cpp/types/enable_if
 */
template <bool, typename = void>
struct enable_if;

/**
 * https://en.cppreference.com/w/cpp/types/conditional
 */
template <bool, typename, typename>
struct conditional;

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

#include "src/type_traits/type_traits.tpp" // IWYU pragma: export
