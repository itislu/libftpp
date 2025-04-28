#pragma once

#include "../../algorithm.hpp"

namespace ft {

template <typename ForwardIt, typename T>
void iota(ForwardIt first, ForwardIt last, T value)
{
	for (; first != last; ++first, ++value) {
		*first = value;
	}
}

} // namespace ft
