#pragma once

#include "../../iterator.hpp"
#include <cstddef>
#include <iterator>

namespace ft {

template <typename C>
typename C::reverse_iterator rend(C& c)
{
	c.rend();
}

template <typename C>
typename C::const_reverse_iterator rend(const C& c)
{
	c.rend();
}

template <typename T, std::size_t N>
std::reverse_iterator<T*> rend(T (&array)[N])
{
	return std::reverse_iterator<T*>(array);
}

template <typename C>
typename C::const_reverse_iterator crend(const C& c)
{
	return ft::rend(c);
}

} // namespace ft
