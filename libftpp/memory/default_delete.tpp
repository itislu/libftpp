#pragma once
#ifndef LIBFTPP_MEMORY_DEFAULT_DELETE_TPP
#	define LIBFTPP_MEMORY_DEFAULT_DELETE_TPP

#	include "libftpp/memory.hpp"
#	include "libftpp/assert.hpp"

namespace ft {

/* default_delete<T> */

template <typename T>
default_delete<T>::default_delete() throw()
{}

template <typename T>
template <typename U>
default_delete<T>::default_delete(const default_delete<U>& /*unused*/) throw()
{}

template <typename T>
void default_delete<T>::operator()(T* ptr) const
{
	// TODO msgs maybe better.
	FT_STATIC_ASSERT( // Can't delete pointer to incomplete type.
	    sizeof(T) != 0);

	delete ptr;
}

/* default_delete<T[]> */

template <typename T>
default_delete<T[]>::default_delete() throw()
{}

template <typename T>
template <typename U>
default_delete<T[]>::default_delete(
    const default_delete<U[]>& /*unused*/) throw()
{}

template <typename T>
template <typename U>
void default_delete<T[]>::operator()(U* ptr) const
{
	// TODO msgs maybe better.
	FT_STATIC_ASSERT( // Can't delete pointer to incomplete type.
	    sizeof(T) != 0);

	delete[] ptr;
}

} // namespace ft

#endif // LIBFTPP_MEMORY_DEFAULT_DELETE_TPP
