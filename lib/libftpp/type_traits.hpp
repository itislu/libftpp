#pragma once

#include <cstddef>

namespace ft {

/**
 * @brief Helper types with distinct sizes for SFINAE `sizeof` tricks
 *
 * These types are commonly used in template metaprogramming as return types in
 * overloaded functions to determine which overload was selected at compile
 * time. An expression that resolves to one of these types is evaluated with
 * `sizeof`, and the result is compared against `sizeof(yes_type)` to produce a
 * compile-time boolean value.
 */
typedef char (&yes_type)[1];
typedef char (&no_type)[2];

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
template <typename T>
struct is_void;

/**
 * https://en.cppreference.com/w/cpp/types/is_integral
 */
template <typename T>
struct is_integral;

/**
 * https://en.cppreference.com/w/cpp/types/is_floating_point
 */
template <typename T>
struct is_floating_point;

/**
 * https://en.cppreference.com/w/cpp/types/is_array
 */
template <typename T>
struct is_array;

/**
 * https://en.cppreference.com/w/cpp/types/is_function
 */
template <typename T>
struct is_function;

/**
 * https://en.cppreference.com/w/cpp/types/is_pointer
 */
template <typename T>
struct is_pointer;

/**
 * https://en.cppreference.com/w/cpp/types/is_object
 */
template <typename T>
struct is_object;

/**
 * https://en.cppreference.com/w/cpp/types/is_reference
 */
template <typename T>
struct is_reference;

/**
 * https://en.cppreference.com/w/cpp/types/is_const
 */
template <typename T>
struct is_const;

/**
 * https://en.cppreference.com/w/cpp/types/is_volatile
 */
template <typename T>
struct is_volatile;

/**
 * https://en.cppreference.com/w/cpp/types/is_bounded_array
 */
template <typename T>
struct is_bounded_array;

/**
 * https://en.cppreference.com/w/cpp/types/is_unbounded_array
 */
template <typename T>
struct is_unbounded_array;

/* Property queries */

/**
 * https://en.cppreference.com/w/cpp/types/rank
 */
template <typename T>
struct rank;

/**
 * https://en.cppreference.com/w/cpp/types/extent
 */
template <typename T, unsigned N = 0>
struct extent;

/* Type relationships */

/**
 * https://en.cppreference.com/w/cpp/types/is_same
 */
template <typename T, typename U>
struct is_same;

/* Type transformations */

/**
 * https://en.cppreference.com/w/cpp/types/remove_cv
 */
template <typename T>
struct remove_cv;

/**
 * https://en.cppreference.com/w/cpp/types/remove_cv
 */
template <typename T>
struct remove_const;

/**
 * https://en.cppreference.com/w/cpp/types/remove_cv
 */
template <typename T>
struct remove_volatile;

/**
 * https://en.cppreference.com/w/cpp/types/add_cv
 */
template <typename T>
struct add_cv;

/**
 * https://en.cppreference.com/w/cpp/types/add_cv
 */
template <typename T>
struct add_const;

/**
 * https://en.cppreference.com/w/cpp/types/add_cv
 */
template <typename T>
struct add_volatile;

/**
 * https://en.cppreference.com/w/cpp/types/remove_extent
 */
template <typename T>
struct remove_extent;

/**
 * https://en.cppreference.com/w/cpp/types/remove_all_extents
 */
template <typename T>
struct remove_all_extents;

/**
 * https://en.cppreference.com/w/cpp/types/remove_pointer
 */
template <typename T>
struct remove_pointer;

/**
 * https://en.cppreference.com/w/cpp/types/enable_if
 */
template <bool B, typename T = void>
struct enable_if;

/**
 * https://en.cppreference.com/w/cpp/types/conditional
 */
template <bool B, typename T, typename F>
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
		template <typename ToCheck>                                          \
		static yes_type test(Sfinae<ToCheck, &ToCheck::METHOD_NAME>*);       \
		template <typename>                                                  \
		static no_type test(...);                                            \
                                                                             \
	public:                                                                  \
		enum {                                                               \
			value = sizeof(test<T>(NULL)) == sizeof(yes_type)                \
		};                                                                   \
	};

HAS_METHOD(void, swap, ToCheck&)

#undef HAS_METHOD

} // namespace ft

#include "src/type_traits/type_traits.tpp" // IWYU pragma: export
