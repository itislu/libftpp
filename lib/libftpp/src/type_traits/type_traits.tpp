#pragma once

#include "../../type_traits.hpp"
#include <cstddef>

namespace ft {

/* Unary type traits */

/* is_void */
template <typename T>
struct is_void : is_same<typename remove_cv<T>::type, void> {};

/* is_array */
template <typename T>
struct is_array : false_type {};

template <typename T>
struct is_array<T[]> : true_type {};

template <typename T, std::size_t N>
struct is_array<T[N]> : true_type {};

/* is_pointer */
template <typename T>
struct is_pointer : conditional<is_const<T>::value || is_volatile<T>::value,
                                is_pointer<typename remove_cv<T>::type>,
                                false_type>::type {};

template <typename T>
struct is_pointer<T*> : true_type {};

/* is_reference */
template <typename>
struct is_reference : false_type {};

template <typename T>
struct is_reference<T&> : true_type {};

/* is_const */
template <typename>
struct is_const : false_type {};

template <typename T>
struct is_const<const T> : true_type {};

/* is_volatile */
template <typename>
struct is_volatile : false_type {};

template <typename T>
struct is_volatile<volatile T> : true_type {};

/* is_bounded_array */
template <typename>
struct is_bounded_array : false_type {};

template <typename T, std::size_t N>
struct is_bounded_array<T[N]> : true_type {};

/* is_unbounded_array */
template <typename>
struct is_unbounded_array : false_type {};

template <typename T>
struct is_unbounded_array<T[]> : true_type {};

/* Property queries */

/* rank */
template <typename>
struct rank : integral_constant<std::size_t, 0> {};

template <typename T>
struct rank<T[]> : integral_constant<std::size_t, 1 + rank<T>::value> {};

template <typename T, std::size_t N>
struct rank<T[N]> : integral_constant<std::size_t, 1 + rank<T>::value> {};

/* extent */
template <typename T, unsigned N>
struct extent : integral_constant<std::size_t, 0> {};

template <typename T, unsigned N>
struct extent<T[], N>
    : integral_constant<std::size_t, N == 0 ? 0 : extent<T, N - 1>::value> {};

template <typename T, std::size_t I, unsigned N>
struct extent<T[I], N>
    : integral_constant<std::size_t, N == 0 ? I : extent<T, N - 1>::value> {};

/* Type relationships */

/* is_same */
template <typename T, typename U>
struct is_same : false_type {};

template <typename T>
struct is_same<T, T> : true_type {};

/* Type transformations */

/* remove_cv */
template <typename T>
struct remove_cv
    : type_identity<
          typename remove_volatile<typename remove_const<T>::type>::type> {};

/* remove_cv */
template <typename T>
struct remove_const : type_identity<T> {};

template <typename T>
struct remove_const<const T> : type_identity<T> {};

/* remove_cv */
template <typename T>
struct remove_volatile : type_identity<T> {};

template <typename T>
struct remove_volatile<volatile T> : type_identity<T> {};

/* add_cv */
template <typename T>
struct add_cv
    : type_identity<typename add_volatile<typename add_const<T>::type>::type> {
};

/* add_cv */
template <typename T>
struct add_const : type_identity<const T> {};

/* add_cv */
template <typename T>
struct add_volatile : type_identity<volatile T> {};

/* remove_extent */
template <typename T>
struct remove_extent : type_identity<T> {};

template <typename T>
struct remove_extent<T[]> : type_identity<T> {};

template <typename T, std::size_t N>
struct remove_extent<T[N]> : type_identity<T> {};

/* remove_all_extents */
template <typename T>
struct remove_all_extents : type_identity<T> {};

template <typename T>
struct remove_all_extents<T[]> : remove_all_extents<T> {};

template <typename T, std::size_t N>
struct remove_all_extents<T[N]> : remove_all_extents<T> {};

/* remove_pointer */
template <typename T>
struct remove_pointer : conditional<is_pointer<T>::value,
                                    remove_pointer<typename remove_cv<T>::type>,
                                    type_identity<T> >::type {};

template <typename T>
struct remove_pointer<T*> : type_identity<T> {};

/* enable_if */
template <bool, typename T>
struct enable_if : type_identity<T> {};

template <typename T>
struct enable_if<false, T> {};

/* conditional */
template <bool, typename T, typename>
struct conditional : type_identity<T> {};

template <typename T, typename F>
struct conditional<false, T, F> : type_identity<F> {};

} // namespace ft
