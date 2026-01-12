// IWYU pragma: private; include "libftpp/functional.hpp"
#pragma once
#ifndef LIBFTPP_FUNCTIONAL_COMPARISONS_TPP
#	define LIBFTPP_FUNCTIONAL_COMPARISONS_TPP

#	include "libftpp/functional.hpp"
#	include <functional>

namespace ft {

namespace _comparisons {
template <template <typename> class Compare, typename T, typename U>
bool common_compare(T* lhs, U* rhs);
template <template <typename> class Compare, typename T>
bool common_compare(T* lhs, T* rhs);
} // namespace _comparisons

/* equal_to */

template <typename T /*= void*/>
bool equal_to<T>::operator()(const T& lhs, const T& rhs) const
{
	return std::equal_to<T>()(lhs, rhs);
}

template <typename T, typename U>
bool equal_to<void>::operator()(const T& lhs, const U& rhs) const
{
	return lhs == rhs;
}

/* not_equal_to */

template <typename T /*= void*/>
bool not_equal_to<T>::operator()(const T& lhs, const T& rhs) const
{
	return std::not_equal_to<T>()(lhs, rhs);
}

template <typename T, typename U>
bool not_equal_to<void>::operator()(const T& lhs, const U& rhs) const
{
	return lhs != rhs;
}

/* greater */

template <typename T /*= void*/>
bool greater<T>::operator()(const T& lhs, const T& rhs) const
{
	return std::greater<T>()(lhs, rhs);
}

template <typename T, typename U>
bool greater<void>::operator()(const T& lhs, const U& rhs) const
{
	return lhs > rhs;
}

template <typename T, typename U>
bool greater<void>::operator()(T* lhs, U* rhs) const
{
	return _comparisons::common_compare<std::greater>(lhs, rhs);
}

/* less */

template <typename T /*= void*/>
bool less<T>::operator()(const T& lhs, const T& rhs) const
{
	return std::less<T>()(lhs, rhs);
}

template <typename T, typename U>
bool less<void>::operator()(const T& lhs, const U& rhs) const
{
	return lhs < rhs;
}

template <typename T, typename U>
bool less<void>::operator()(T* lhs, U* rhs) const
{
	return _comparisons::common_compare<std::less>(lhs, rhs);
}

/* greater_equal */

template <typename T /*= void*/>
bool greater_equal<T>::operator()(const T& lhs, const T& rhs) const
{
	return std::greater_equal<T>()(lhs, rhs);
}

template <typename T, typename U>
bool greater_equal<void>::operator()(const T& lhs, const U& rhs) const
{
	return lhs >= rhs;
}

template <typename T, typename U>
bool greater_equal<void>::operator()(T* lhs, U* rhs) const
{
	return _comparisons::common_compare<std::greater_equal>(lhs, rhs);
}

/* less_equal */

template <typename T /*= void*/>
bool less_equal<T>::operator()(const T& lhs, const T& rhs) const
{
	return std::less_equal<T>()(lhs, rhs);
}

template <typename T, typename U>
bool less_equal<void>::operator()(const T& lhs, const U& rhs) const
{
	return lhs <= rhs;
}

template <typename T, typename U>
bool less_equal<void>::operator()(T* lhs, U* rhs) const
{
	return _comparisons::common_compare<std::less_equal>(lhs, rhs);
}

namespace _comparisons {

template <template <typename> class Compare, typename T, typename U>
bool common_compare(T* lhs, U* rhs)
{
	// Use conditional operator to get common type.
	return _comparisons::common_compare<Compare>(true ? lhs : rhs,
	                                             true ? rhs : lhs);
}

template <template <typename> class Compare, typename T>
bool common_compare(T* lhs, T* rhs)
{
	return Compare<T*>()(lhs, rhs);
}

} // namespace _comparisons

} // namespace ft

#endif // LIBFTPP_FUNCTIONAL_COMPARISONS_TPP
