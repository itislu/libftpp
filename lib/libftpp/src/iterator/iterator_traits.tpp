#pragma once

#include "../../type_traits.hpp"
#include <iterator>

namespace ft {

/* is_iterator */
namespace _is_iterator {
template <typename T, typename = void>
struct Impl;
} // namespace _is_iterator

template <typename T>
struct is_iterator : _is_iterator::Impl<T> {};

namespace _is_iterator {

template <typename, typename /*= void*/>
struct Impl : ft::false_type {};

template <typename T>
struct Impl<T, typename ft::voider<typename T::iterator_category>::type>
    : ft::bool_constant<
          ft::is_same<typename std::iterator_traits<T>::iterator_category,
                      std::input_iterator_tag>::value
          || ft::is_same<typename std::iterator_traits<T>::iterator_category,
                         std::output_iterator_tag>::value
          || ft::is_same<typename std::iterator_traits<T>::iterator_category,
                         std::forward_iterator_tag>::value
          || ft::is_same<typename std::iterator_traits<T>::iterator_category,
                         std::bidirectional_iterator_tag>::value
          || ft::is_same<typename std::iterator_traits<T>::iterator_category,
                         std::random_access_iterator_tag>::value> {};

} // namespace _is_iterator

/* is_input_iterator */
namespace _is_input_iterator {
template <typename T>
struct Impl;
} // namespace _is_input_iterator

template <typename T>
struct is_input_iterator
    : ft::conjunction<is_iterator<T>, _is_input_iterator::Impl<T> > {};

namespace _is_input_iterator {

template <typename T>
struct Impl
    : ft::is_convertible<typename std::iterator_traits<T>::iterator_category,
                         std::input_iterator_tag> {};

} // namespace _is_input_iterator

/* is_output_iterator */
namespace _is_output_iterator {
template <typename T>
struct Impl;
} // namespace _is_output_iterator

template <typename T>
struct is_output_iterator
    : ft::conjunction<is_iterator<T>, _is_output_iterator::Impl<T> > {};

namespace _is_output_iterator {

template <typename T>
struct Impl
    : ft::is_convertible<typename std::iterator_traits<T>::iterator_category,
                         std::output_iterator_tag> {};

} // namespace _is_output_iterator

/* is_forward_iterator */
namespace _is_forward_iterator {
template <typename T>
struct Impl;
} // namespace _is_forward_iterator

template <typename T>
struct is_forward_iterator
    : ft::conjunction<is_iterator<T>, _is_forward_iterator::Impl<T> > {};

namespace _is_forward_iterator {

template <typename T>
struct Impl
    : ft::is_convertible<typename std::iterator_traits<T>::iterator_category,
                         std::forward_iterator_tag> {};

} // namespace _is_forward_iterator

/* is_bidirectional_iterator */
namespace _is_bidirectional_iterator {
template <typename T>
struct Impl;
} // namespace _is_bidirectional_iterator

template <typename T>
struct is_bidirectional_iterator
    : ft::conjunction<is_iterator<T>, _is_bidirectional_iterator::Impl<T> > {};

namespace _is_bidirectional_iterator {

template <typename T>
struct Impl
    : ft::is_convertible<typename std::iterator_traits<T>::iterator_category,
                         std::bidirectional_iterator_tag> {};

} // namespace _is_bidirectional_iterator

/* is_random_access_iterator */
namespace _is_random_access_iterator {
template <typename T>
struct Impl;
} // namespace _is_random_access_iterator

template <typename T>
struct is_random_access_iterator
    : ft::conjunction<is_iterator<T>, _is_random_access_iterator::Impl<T> > {};

namespace _is_random_access_iterator {

template <typename T>
struct Impl
    : ft::is_convertible<typename std::iterator_traits<T>::iterator_category,
                         std::random_access_iterator_tag> {};

} // namespace _is_random_access_iterator

} // namespace ft
