#pragma once

#include "../../SafeBool.hpp"
#include "SafeBoolBase.hpp"
#include <cstddef>

namespace ft {

template <typename Derived>
SafeBool<Derived>::operator safe_bool_t() const
{
	return (static_cast<const Derived*>(this))->boolean_test()
	           ? &SafeBoolBase::this_type_does_not_support_comparisons
	           : NULL;
}

template <typename Derived>
SafeBool<Derived>::SafeBool()
{}

template <typename Derived>
SafeBool<Derived>::~SafeBool()
{}

template <typename T>
bool operator==(const SafeBool<T>& lhs, bool b)
{
	return b == static_cast<bool>(lhs);
}

template <typename T>
bool operator==(bool b, const SafeBool<T>& rhs)
{
	return b == static_cast<bool>(rhs);
}

template <typename T>
bool operator!=(const SafeBool<T>& lhs, bool b)
{
	return b != static_cast<bool>(lhs);
}

template <typename T>
bool operator!=(bool b, const SafeBool<T>& rhs)
{
	return b != static_cast<bool>(rhs);
}

template <typename T, typename U>
bool operator==(const SafeBool<T>& lhs, const U& /*rhs*/)
{
	lhs.this_type_does_not_support_comparisons();
	return false;
}

template <typename T, typename U>
bool operator==(const U& /*lhs*/, const SafeBool<T>& rhs)
{
	rhs.this_type_does_not_support_comparisons();
	return false;
}

template <typename T, typename U>
bool operator!=(const SafeBool<T>& lhs, const U& /*rhs*/)
{
	lhs.this_type_does_not_support_comparisons();
	return false;
}

template <typename T, typename U>
bool operator!=(const U& /*lhs*/, const SafeBool<T>& rhs)
{
	rhs.this_type_does_not_support_comparisons();
	return false;
}

} // namespace ft
