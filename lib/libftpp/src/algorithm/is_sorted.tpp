#pragma once

#include "../../algorithm.hpp"
#include "../../functional.hpp"

namespace ft {

template <typename ForwardIt>
bool is_sorted(ForwardIt first, ForwardIt last)
{
	return is_sorted_until(first, last) == last;
}

template <typename ForwardIt, typename Compare>
bool is_sorted(ForwardIt first, ForwardIt last, Compare comp)
{
	return is_sorted_until(first, last, comp) == last;
}

template <typename ForwardIt>
ForwardIt is_sorted_until(ForwardIt first, ForwardIt last)
{
	return is_sorted_until(first, last, ft::less<>());
}

template <typename ForwardIt, typename Compare>
ForwardIt is_sorted_until(ForwardIt first, ForwardIt last, Compare comp)
{
	if (first == last) {
		return last;
	}
	for (ForwardIt next = first; ++next != last; first = next) {
		if (comp(*next, *first)) {
			return next;
		}
	}
	return last;
}

} // namespace ft
