#pragma once

#include "../../algorithm.hpp"
#include <iterator>

namespace ft {

template <typename InputIt, typename T>
typename std::iterator_traits<InputIt>::difference_type
count(InputIt first, InputIt last, const T& value)
{
	typename std::iterator_traits<InputIt>::difference_type res = 0;

	for (; first != last; ++first) {
		if (*first == value) {
			++res;
		}
	}
	return res;
}

} // namespace ft
