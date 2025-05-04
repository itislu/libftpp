#pragma once

#include "../../algorithm.hpp"

namespace ft {

template <typename T>
const T& max(const T& a, const T& b)
{
	return (a < b) ? b : a;
}

template <typename T>
T& max(T& a, T& b)
{
	return (a < b) ? b : a;
}

template <typename T>
const T& min(const T& a, const T& b)
{
	return (b < a) ? b : a;
}

template <typename T>
T& min(T& a, T& b)
{
	return (b < a) ? b : a;
}

} // namespace ft
