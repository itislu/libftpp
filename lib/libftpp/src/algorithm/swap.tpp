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
	_swap::Impl<T, has_swap<T>::value>::swap(a, b);
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
