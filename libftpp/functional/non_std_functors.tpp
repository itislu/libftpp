// IWYU pragma: private; include "libftpp/functional.hpp"
#pragma once

#include "libftpp/functional.hpp"

namespace ft {

template <typename T>
bool Nth::operator()(const T& /*unused*/) throw()
{
	if (++_cur == _n) {
		_cur = 0;
		return true;
	}
	return false;
}

} // namespace ft
