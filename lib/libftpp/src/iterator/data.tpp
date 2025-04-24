#pragma once

#include "../../iterator.hpp"
#include <cstddef>

namespace ft {

template <typename C>
typename C::pointer data(C& c)
{
	return c.data();
}

template <typename C>
typename C::const_pointer data(const C& c)
{
	return c.data();
}

template <typename T, std::size_t N>
T* data(T (&array)[N]) throw()
{
	return array;
}

} // namespace ft
