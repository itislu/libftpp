#pragma once

#include "../../algorithm.hpp"
#include "../../type_traits.hpp"

namespace ft {

namespace _swap {
template <typename T, bool HasSwap>
struct Impl;
} // namespace _swap

template <typename T>
void swap(T& a, T& b)
{
	_swap::Impl<T, ft::has_swap<T>::value>::swap(a, b);
}

template <typename ForwardIt1, typename ForwardIt2>
void iter_swap(ForwardIt1 a, ForwardIt2 b)
{
	ft::swap(*a, *b);
}

template <typename ForwardIt1, typename ForwardIt2>
ForwardIt2 swap_ranges(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2)
{
	for (; first1 != last1; ++first1, ++first2) {
		ft::iter_swap(first1, first2);
	}
	return first2;
}

namespace _swap {

/**
 * Use the type's swap method.
 */
template <typename T>
struct Impl<T, true> {
	static void swap(T& a, T& b) { a.swap(b); }
};

/**
 * Manual swap implementation for types that do not have a swap method.
 */
template <typename T>
struct Impl<T, false> {
	static void swap(T& a, T& b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}
};

} // namespace _swap

} // namespace ft
