#pragma once

#include "../../operators.hpp"

namespace ft {
namespace operators {

template <typename T, typename U>
bool operator==(const T& lhs, const U& rhs)
{
	return !(lhs < rhs) && !(rhs < lhs);
}

template <typename T, typename U>
bool operator!=(const T& lhs, const U& rhs)
{
	return !(lhs == rhs);
}

template <typename T, typename U>
bool operator>(const T& lhs, const U& rhs)
{
	return rhs < lhs;
}

template <typename T, typename U>
bool operator<=(const T& lhs, const U& rhs)
{
	return !(lhs > rhs);
}

template <typename T, typename U>
bool operator>=(const T& lhs, const U& rhs)
{
	return !(lhs < rhs);
}

} // namespace operators
} // namespace ft
