#pragma once

#include "../../numeric.hpp"
#include "../../type_traits.hpp"
#include <limits>

namespace ft {

template <typename T>
typename ft::enable_if<std::numeric_limits<T>::is_integer, T>::type
add_sat(T x, T y) throw()
{
	const T max = std::numeric_limits<T>::max();
	if (std::numeric_limits<T>::is_signed) {
		// Check for overflow
		if (x > 0 && y > 0 && x > max - y) {
			return max;
		}
		const T min = std::numeric_limits<T>::min();
		// Check for underflow
		if (x < 0 && y < 0 && x < min - y) {
			return min;
		}
	}
	else {
		// For unsigned types, only overflow is possible
		if (y > max - x) {
			return max;
		}
	}
	return x + y;
}

template <typename T>
typename ft::enable_if<std::numeric_limits<T>::is_integer, T>::type
sub_sat(T x, T y) throw()
{
	if (std::numeric_limits<T>::is_signed) {
		const T max = std::numeric_limits<T>::max();
		const T min = std::numeric_limits<T>::min();
		// Check for overflow
		if (x > 0 && y < 0 && x > max + y) {
			return max;
		}
		// Check for underflow
		if (x < 0 && y > 0 && x < min + y) {
			return min;
		}
	}
	else {
		// For unsigned types, only underflow to 0 is possible
		if (x < y) {
			return 0;
		}
	}
	return x - y;
}

template <typename T>
typename ft::enable_if<std::numeric_limits<T>::is_integer, T>::type
mul_sat(T x, T y) throw()
{
	const T max = std::numeric_limits<T>::max();
	if (std::numeric_limits<T>::is_signed) {
		// Check for overflow
		if ((x > 0 && y > 0 && x > max / y)
		    || (x < 0 && y < 0 && x < max / y)) {
			return max;
		}
		const T min = std::numeric_limits<T>::min();
		// Check for underflow
		if ((x > 0 && y < 0 && y < min / x)
		    || (x < 0 && y > 0 && x < min / y)) {
			return min;
		}
	}
	else {
		// For unsigned types, only overflow is possible
		if (y > 0 && x > max / y) {
			return max;
		}
	}
	return x * y;
}

template <typename T>
typename ft::enable_if<std::numeric_limits<T>::is_integer, T>::type
div_sat(T x, T y) throw()
{
	if (y == 0) {
		// Division by zero
		if (x > 0) {
			return std::numeric_limits<T>::max();
		}
		if (x < 0) {
			return std::numeric_limits<T>::min();
		}
		return 0; // 0/0
	}

	if (std::numeric_limits<T>::is_signed) {
		const T min = std::numeric_limits<T>::min();
		// MIN / -1 overflow
		if (x == min && y == -1) {
			return std::numeric_limits<T>::max();
		}
	}
	return x / y;
}

} // namespace ft
