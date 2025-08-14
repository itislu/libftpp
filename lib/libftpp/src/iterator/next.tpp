#pragma once

#include "../../iterator.hpp"
#include <iterator>

namespace ft {

template <typename InputIt>
InputIt next(InputIt it,
             typename std::iterator_traits<InputIt>::difference_type n /*= 1*/)
{
	std::advance(it, n);
	return it;
}

} // namespace ft
