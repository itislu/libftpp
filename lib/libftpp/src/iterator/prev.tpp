#pragma once

#include "../../assert.hpp"
#include "../../iterator.hpp"
#include "../../type_traits.hpp"
#include <iterator>

namespace ft {

template <typename BidirIt>
BidirIt prev(BidirIt it)
{
	typedef typename std::iterator_traits<BidirIt>::difference_type
	    BidirIt_must_be_an_iterator_type;
	// Use to avoid unused typedef warnings.
	STATIC_ASSERT((ft::is_same<BidirIt_must_be_an_iterator_type,
	                           BidirIt_must_be_an_iterator_type>::value));

	--it;
	return it;
}

template <typename BidirIt>
BidirIt prev(BidirIt it,
             typename std::iterator_traits<BidirIt>::difference_type n)
{
	ft::advance(it, -n);
	return it;
}

template <typename BidirIt>
BidirIt prev(BidirIt it,
             typename std::iterator_traits<BidirIt>::difference_type n,
             BidirIt bound)
{
	ft::advance(it, -n, bound);
	return it;
}

} // namespace ft
