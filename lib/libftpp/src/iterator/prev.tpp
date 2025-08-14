#pragma once

#include "../../iterator.hpp"
#include <iterator>

namespace ft {

template <typename BidirIt>
BidirIt prev(BidirIt it,
             typename std::iterator_traits<BidirIt>::difference_type n /*= 1*/)
{
	std::advance(it, -n);
	return it;
}

} // namespace ft
