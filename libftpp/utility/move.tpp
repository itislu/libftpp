// IWYU pragma: private; include "libftpp/utility.hpp"
#pragma once
#ifndef LIBFTPP_UTILITY_MOVE_TPP
#	define LIBFTPP_UTILITY_MOVE_TPP

#	include "libftpp/utility.hpp"
#	include "libftpp/type_traits.hpp"

namespace ft {

template <typename T>
typename ft::conditional<ft::is_class_or_union<T>::value,
                         typename ft::add_rvalue_reference<T>::type,
                         T&>::type
move(T& t) throw()
{
	return static_cast<
	    typename ft::conditional<ft::is_class_or_union<T>::value,
	                             typename ft::add_rvalue_reference<T>::type,
	                             T&>::type>(t);
}

} // namespace ft

#endif // LIBFTPP_UTILITY_MOVE_TPP
