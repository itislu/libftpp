#pragma once

#include "../../algorithm.hpp"

namespace ft {

template <class InputIt, class ForwardIt>
InputIt
find_first_of(InputIt first, InputIt last, ForwardIt s_first, ForwardIt s_last)
{
	for (; first != last; ++first) {
		for (ForwardIt it = s_first; it != s_last; ++it) {
			if (*first == *it) {
				return first;
			}
		}
	}
	return last;
}

template <typename InputIt, typename ForwardIt, typename BinaryPred>
InputIt find_first_of(InputIt first,
                      InputIt last,
                      ForwardIt s_first,
                      ForwardIt s_last,
                      BinaryPred p)
{
	for (; first != last; ++first) {
		for (ForwardIt it = s_first; it != s_last; ++it) {
			if (p(*first, *it)) {
				return first;
			}
		}
	}
	return last;
}

} // namespace ft
