#pragma once

#include "../../algorithm.hpp"

namespace ft {

template <typename ForwardIt, typename T>
void fill(ForwardIt first, ForwardIt last, const T& value)
{
	for (; first != last; ++first) {
		*first = value;
	}
}

template <typename OutputIt, typename Size, typename T>
OutputIt fill_n(OutputIt first, Size count, const T& value)
{
	for (Size i = 0; i < count; ++first, ++i) {
		*first = value;
	}
	return first;
}

} // namespace ft
