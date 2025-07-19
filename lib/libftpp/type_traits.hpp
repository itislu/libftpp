#pragma once

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

	operator value_type() const throw();
	value_type operator()() const throw();
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
 * https://en.cppreference.com/w/cpp/types/is_lvalue_reference
 */
template <typename T>
struct is_lvalue_reference;

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
 * https://en.cppreference.com/w/cpp/types/is_abstract
 */
template <typename T>
struct is_abstract;

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

/**
 * https://en.cppreference.com/w/cpp/types/is_convertible
 */
template <typename From, typename To>
struct is_convertible;

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
 * https://en.cppreference.com/w/cpp/types/remove_reference
 */
template <typename T>
struct remove_reference;

/**
 * https://en.cppreference.com/w/cpp/types/add_reference
 */
template <typename T>
struct add_lvalue_reference;

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
 * https://en.cppreference.com/w/cpp/types/void_t
 *
 * Variadic templates do not exist in C++98, so an arbitrary limit of 10
 * template parameters is set instead.
 *
 * It is not named `void_t` because `::type` is still required to use it.
 * The `_t` suffix is usually used for helper types that don't need `::type`.
 * The name `voider` is chosen because it is mentioned in N3911
 * (https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n3911.pdf).
 */
template <typename = void,
          typename = void,
          typename = void,
          typename = void,
          typename = void,
          typename = void,
          typename = void,
          typename = void,
          typename = void,
          typename = void>
struct voider;

/* Custom type traits */

/**
 * @brief Generates type traits that check if a class has a specific public
 * non-static member function.
 *
 * The generated type traits are named has_member_function_<name>.
 * There can only be 1 trait with the same function name.
 *
 * Usage example: `HAS_MEMBER_FUNCTION(void, swap, (T&))`
 */
// NOLINTBEGIN(bugprone-macro-parentheses)
#define HAS_MEMBER_FUNCTION(RETURN_TYPE, NAME, ARGS_IN_PARENS)                 \
	namespace _has_member_function_##NAME                                      \
	{                                                                          \
                                                                               \
		/* 2nd param: member-function pointer non-type template parameter */   \
		template <typename T, RETURN_TYPE(T::*) ARGS_IN_PARENS>                \
		struct Sfinae {};                                                      \
                                                                               \
		template <typename T, typename = void>                                 \
		struct Impl : ft::false_type {};                                       \
                                                                               \
		template <typename T>                                                  \
		struct Impl<T, typename ft::voider<Sfinae<T, &T::NAME> >::type>        \
		    : ft::true_type {};                                                \
                                                                               \
	} /* namespace _has_member_function_##NAME */                              \
                                                                               \
	template <typename T>                                                      \
	struct has_member_function_##NAME : _has_member_function_##NAME::Impl<T> { \
	};
// NOLINTEND(bugprone-macro-parentheses)

/* has_member_function_swap */
HAS_MEMBER_FUNCTION(void, swap, (T&))

/**
 * @brief Checks wether `T` is a non-const lvalue reference type
 *
 * Provides the member constant `value` which is equal to `true`, if `T` is a
 * non-const lvalue reference type. Otherwise, `value` is equal to `false`.
 *
 * This is useful because if `T` is a reference type then `is_const<T>::value`
 * is always `false`.
 */
template <typename T>
struct is_nonconst_lvalue_reference;

} // namespace ft

#include "src/type_traits/type_traits.tpp" // IWYU pragma: export
