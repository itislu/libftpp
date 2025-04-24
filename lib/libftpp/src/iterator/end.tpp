#pragma once

#include "../../iterator.hpp"
#include <cstddef>

namespace ft {

template <typename C>
typename C::iterator end(C& c)
{
	c.end();
}

template <typename C>
typename C::const_iterator end(const C& c)
{
	c.end();
}

template <typename T, std::size_t N>
T* end(T (&array)[N])
{
	return array + N;
}

template <typename C>
typename C::const_iterator cend(const C& c)
{
	return ft::end(c);
}

} // namespace ft
