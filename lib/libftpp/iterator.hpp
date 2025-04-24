#pragma once

#include <cstddef>
#include <iterator>

namespace ft {

/* Range access */

/**
 * https://en.cppreference.com/w/cpp/iterator/begin
 */
template <typename C>
typename C::iterator begin(C& c);
template <typename C>
typename C::const_iterator begin(const C& c);
template <typename T, std::size_t N>
T* begin(T (&array)[N]);
template <typename C>
typename C::const_iterator cbegin(const C& c);

/**
 * https://en.cppreference.com/w/cpp/iterator/end
 */
template <typename C>
typename C::iterator end(C& c);
template <typename C>
typename C::const_iterator end(const C& c);
template <typename T, std::size_t N>
T* end(T (&array)[N]);
template <typename C>
typename C::const_iterator cend(const C& c);

/**
 * https://en.cppreference.com/w/cpp/iterator/rbegin
 */
template <typename C>
typename C::reverse_iterator rbegin(C& c);
template <typename C>
typename C::const_reverse_iterator rbegin(const C& c);
template <typename T, std::size_t N>
std::reverse_iterator<T*> rbegin(T (&array)[N]);
template <typename C>
typename C::const_reverse_iterator crbegin(const C& c);

/**
 * https://en.cppreference.com/w/cpp/iterator/rend
 */
template <typename C>
typename C::reverse_iterator rend(C& c);
template <typename C>
typename C::const_reverse_iterator rend(const C& c);
template <typename T, std::size_t N>
std::reverse_iterator<T*> rend(T (&array)[N]);
template <typename C>
typename C::const_reverse_iterator crend(const C& c);

/**
 * https://en.cppreference.com/w/cpp/iterator/size
 */
template <typename C>
typename C::size_type size(const C& c);
template <typename C>
typename C::difference_type ssize(const C& c);
template <typename T, std::size_t N>
std::size_t size(const T (&array)[N]) throw();
template <typename T, std::ptrdiff_t N>
std::ptrdiff_t ssize(const T (&array)[N]) throw();

/**
 * https://en.cppreference.com/w/cpp/iterator/empty
 */
template <typename C>
bool empty(const C& c);
template <typename T, std::size_t N>
bool empty(const T (&array)[N]) throw();

/**
 * https://en.cppreference.com/w/cpp/iterator/data
 */
template <typename C>
typename C::pointer data(C& c);
template <typename C>
typename C::const_pointer data(const C& c);
template <typename T, std::size_t N>
T* data(T (&array)[N]) throw();

} // namespace ft

#include "src/iterator/begin.tpp"  // IWYU pragma: export
#include "src/iterator/data.tpp"   // IWYU pragma: export
#include "src/iterator/empty.tpp"  // IWYU pragma: export
#include "src/iterator/end.tpp"    // IWYU pragma: export
#include "src/iterator/rbegin.tpp" // IWYU pragma: export
#include "src/iterator/rend.tpp"   // IWYU pragma: export
#include "src/iterator/size.tpp"   // IWYU pragma: export
