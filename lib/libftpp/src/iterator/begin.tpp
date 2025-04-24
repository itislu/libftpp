#pragma once

#include "../../iterator.hpp"
#include <cstddef>

namespace ft {

template <typename C>
typename C::iterator begin(C& c)
{
	c.begin();
}

template <typename C>
typename C::const_iterator begin(const C& c)
{
	c.begin();
}

template <typename T, std::size_t N>
T* begin(T (&array)[N])
{
	return array;
}

template <typename C>
typename C::const_iterator cbegin(const C& c)
{
	return ft::begin(c);
}

} // namespace ft
