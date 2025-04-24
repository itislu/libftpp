#pragma once

#include "../../iterator.hpp"
#include <cstddef>

namespace ft {

template <typename C>
bool empty(const C& c)
{
	return c.empty();
}

template <typename T, std::size_t N>
bool empty(const T (& /*unused*/)[N]) throw()
{
	return false;
}

} // namespace ft
