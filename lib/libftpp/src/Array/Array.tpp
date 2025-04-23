#pragma once

#include "../../Array.hpp"
#include "../../algorithm.hpp"
#include "../../assert.hpp"
#include "../../string.hpp"
#include "../../type_traits.hpp"
#include <cassert>
#include <cstddef>
#include <stdexcept>

namespace ft {

namespace _array {

template <typename T, std::size_t N>
T& Impl<T, N>::ref(const Type& t, std::size_t n) throw()
{
	STATIC_ASSERT(N > 0); // Cannot index into a zero-sized array
	/*
	The const_cast only removes const-ness temporarily added by the parameter
	type, not from truly const objects. When called from a const member
	function, the result is implicitly converted back to const before exposure
	to the caller.
	*/
	return const_cast<T&>(t[n]);
}

template <typename T, std::size_t N>
T* Impl<T, N>::ptr(const Type& t) throw()
{
	if (N == 0) {
		return NULL;
	}
	/*
	The const_cast only removes const-ness temporarily added by the parameter
	type, not from truly const objects. When called from a const member
	function, the result is implicitly converted back to const before exposure
	to the caller.
	*/
	return const_cast<T*>(t); // NOLINT(cppcoreguidelines-pro-type-const-cast)
}

} // namespace _array

/* Element access */

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::at(size_type pos)
{
	if (pos >= N) {
		throw std::out_of_range("out-of-bounds access in ft::Array: index ("
		                        + ft::to_string(pos) + ") >= array size ("
		                        + ft::to_string(N) + ")");
	}
	return _array::Impl<T, MAX(N, 1)>::ref(_elems, pos);
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reference Array<T, N>::at(size_type pos) const
{
	if (pos >= N) {
		throw std::out_of_range("out-of-bounds access in ft::Array: index ("
		                        + ft::to_string(pos) + ") >= array size ("
		                        + ft::to_string(N) + ")");
	}
	return _array::Impl<T, MAX(N, 1)>::ref(_elems, pos);
}

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::operator[](size_type pos)
{
	assert(pos < N);
	return _array::Impl<T, N>::ref(_elems, pos);
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reference
Array<T, N>::operator[](size_type pos) const
{
	assert(pos < N);
	return _array::Impl<T, N>::ref(_elems, pos);
}

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::front()
{
	return _array::Impl<T, N>::ref(_elems, 0);
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reference Array<T, N>::front() const
{
	return _array::Impl<T, N>::ref(_elems, 0);
}

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::back()
{
	return N > 0 ? _array::Impl<T, N>::ref(_elems, N - 1)
	             : _array::Impl<T, N>::ref(_elems, 0);
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reference Array<T, N>::back() const
{
	return N > 0 ? _array::Impl<T, N>::ref(_elems, N - 1)
	             : _array::Impl<T, N>::ref(_elems, 0);
}

template <typename T, std::size_t N>
T* Array<T, N>::data() throw()
{
	return _array::Impl<T, N>::ptr(_elems);
}

template <typename T, std::size_t N>
const T* Array<T, N>::data() const throw()
{
	return _array::Impl<T, N>::ptr(_elems);
}

/* Iterators */

template <typename T, std::size_t N>
typename Array<T, N>::iterator Array<T, N>::begin() throw()
{
	return iterator(data());
}

template <typename T, std::size_t N>
typename Array<T, N>::const_iterator Array<T, N>::begin() const throw()
{
	return const_iterator(data());
}

template <typename T, std::size_t N>
typename Array<T, N>::const_iterator Array<T, N>::cbegin() const throw()
{
	return const_iterator(data());
}

template <typename T, std::size_t N>
typename Array<T, N>::iterator Array<T, N>::end() throw()
{
	return iterator(data() + N);
}

template <typename T, std::size_t N>
typename Array<T, N>::const_iterator Array<T, N>::end() const throw()
{
	return const_iterator(data() + N);
}

template <typename T, std::size_t N>
typename Array<T, N>::const_iterator Array<T, N>::cend() const throw()
{
	return const_iterator(data() + N);
}

template <typename T, std::size_t N>
typename Array<T, N>::reverse_iterator Array<T, N>::rbegin() throw()
{
	return reverse_iterator(end());
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reverse_iterator Array<T, N>::rbegin() const throw()
{
	return const_reverse_iterator(end());
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reverse_iterator Array<T, N>::crbegin() const
    throw()
{
	return const_reverse_iterator(end());
}

template <typename T, std::size_t N>
typename Array<T, N>::reverse_iterator Array<T, N>::rend() throw()
{
	return reverse_iterator(begin());
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reverse_iterator Array<T, N>::rend() const throw()
{
	return const_reverse_iterator(begin());
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reverse_iterator Array<T, N>::crend() const throw()
{
	return const_reverse_iterator(begin());
}

/* Capacity */

template <typename T, std::size_t N>
bool Array<T, N>::empty() const throw()
{
	return size() == 0;
}

template <typename T, std::size_t N>
typename Array<T, N>::size_type Array<T, N>::size() const throw()
{
	return N;
}

template <typename T, std::size_t N>
typename Array<T, N>::size_type Array<T, N>::max_size() const throw()
{
	return N;
}

/* Operations */

template <typename T, std::size_t N>
void Array<T, N>::fill(const T& value)
{
	ft::fill(begin(), end(), value);
}

template <typename T, std::size_t N>
void Array<T, N>::swap(Array& other)
{
	ft::swap_ranges(begin(), end(), other.begin());
}

/* Non-member functions */

template <typename T, std::size_t N>
bool operator==(const Array<T, N>& lhs, const Array<T, N>& rhs)
{
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T, std::size_t N>
bool operator!=(const Array<T, N>& lhs, const Array<T, N>& rhs)
{
	return !(lhs == rhs);
}

template <typename T, std::size_t N>
bool operator<(const Array<T, N>& lhs, const Array<T, N>& rhs)
{
	return ft::lexicographical_compare(
	    lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, std::size_t N>
bool operator<=(const Array<T, N>& lhs, const Array<T, N>& rhs)
{
	return rhs < lhs;
}

template <typename T, std::size_t N>
bool operator>(const Array<T, N>& lhs, const Array<T, N>& rhs)
{
	return !(lhs > rhs);
}

template <typename T, std::size_t N>
bool operator>=(const Array<T, N>& lhs, const Array<T, N>& rhs)
{
	return !(lhs < rhs);
}

template <std::size_t I, typename T, std::size_t N>
T& get(Array<T, N>& a)
{
	STATIC_ASSERT(I < N); // Index out of bounds in ft::get
	return a[I];
}

template <std::size_t I, typename T, std::size_t N>
const T& get(const Array<T, N>& a)
{
	STATIC_ASSERT(I < N); // Index out of bounds in ft::get
	return a[I];
}

template <typename T, std::size_t N>
void swap(Array<T, N>& lhs, Array<T, N>& rhs)
{
	lhs.swap(rhs);
}

template <typename T, std::size_t N>
Array<typename ft::remove_cv<T>::type, N> to_array(T (&a)[N])
{
	Array<typename ft::remove_cv<T>::type, N> arr;
	for (std::size_t i = 0; i < N; ++i) {
		arr[i] = a[i];
	}
	return arr;
}

} // namespace ft
