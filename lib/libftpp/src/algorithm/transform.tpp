#pragma once

#include "../../algorithm.hpp"

namespace ft {

template <typename InputIt, typename OutputIt, typename UnaryOp>
OutputIt
transform(InputIt first, InputIt last, OutputIt d_result, UnaryOp unary_op)
{
	for (; first != last; ++d_result, ++first) {
		*d_result = unary_op(*first);
	}
	return d_result;
}

} // namespace ft
