// IWYU pragma: private; include "libftpp/utility.hpp"
#pragma once
#ifndef LIBFTPP_UTILITY_FORWARD_TPP
#	define LIBFTPP_UTILITY_FORWARD_TPP

#	include "libftpp/utility.hpp"
#	include "libftpp/assert.hpp"
#	include "libftpp/type_traits.hpp"

namespace ft {

template <typename T>
typename ft::conditional<
    ft::is_reference<T>::value,
    T,
    typename ft::conditional<
        ft::is_class_or_union<T>::value,
        typename ft::add_rvalue_reference<T>::type,
        typename ft::add_lvalue_reference<T>::type>::type>::type
forward(typename ft::add_lvalue_reference<T>::type t) throw()
{
	return static_cast<typename ft::conditional<
	    ft::is_reference<T>::value,
	    T,
	    typename ft::conditional<
	        ft::is_class_or_union<T>::value,
	        typename ft::add_rvalue_reference<T>::type,
	        typename ft::add_lvalue_reference<T>::type>::type>::type>(t);
}

template <typename T>
typename ft::add_rvalue_reference<T>::type
forward(typename ft::add_rvalue_reference<
        typename ft::remove_reference<T>::type>::type t) throw()
{
	FT_STATIC_ASSERT( // Cannot forward an rvalue as an lvalue.
	    !ft::is_lvalue_reference<T>::value);

	return static_cast<typename ft::add_rvalue_reference<T>::type>(t);
}

} // namespace ft

#endif // LIBFTPP_UTILITY_FORWARD_TPP
