#pragma once

#include "../../iterator.hpp"
#include <cstddef>
#include <iterator>

namespace ft {

template <typename C>
typename C::reverse_iterator rbegin(C& c)
{
	c.rbegin();
}

template <typename C>
typename C::const_reverse_iterator rbegin(const C& c)
{
	c.rbegin();
}

template <typename T, std::size_t N>
std::reverse_iterator<T*> rbegin(T (&array)[N])
{
	return std::reverse_iterator<T*>(array + N);
}

template <typename C>
typename C::const_reverse_iterator crbegin(const C& c)
{
	return ft::rbegin(c);
}

} // namespace ft
