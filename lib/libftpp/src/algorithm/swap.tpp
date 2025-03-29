#pragma once

#include "../../algorithm.hpp"
#include "../../type_traits.hpp"
#include <cstddef>

namespace ft {
namespace _swap {
template <typename T>
static void
swap(T& a,
     T& b,
     typename enable_if<has_swap<T>::value>::type* /*unused*/ = NULL);
template <typename T>
static void
swap(T& a,
     T& b,
     typename enable_if<!has_swap<T>::value>::type* /*unused*/ = NULL);
} // namespace _swap

template <typename T>
void swap(T& a, T& b)
{
	_swap::swap(a, b);
}

namespace _swap {

/**
 * Use the type's swap method.
 */
template <typename T>
static void
swap(T& a, T& b, typename enable_if<has_swap<T>::value>::type* /*unused*/)
{
	a.swap(b);
}

/**
 * Manual swap implementation for types that do not have a swap method.
 */
template <typename T>
static void
swap(T& a, T& b, typename enable_if<!has_swap<T>::value>::type* /*unused*/)
{
	T tmp = a;
	a = b;
	b = tmp;
}

} // namespace _swap

} // namespace ft
