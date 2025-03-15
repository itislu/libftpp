#pragma once

#include "common.hpp"
#include "type_traits.hpp"
#include <cstddef>
#include <fstream>
#include <ios>

namespace utils {

namespace _detail {

/**
 * Use the type's swap method.
 */
template <typename T>
static void
swap(T& a,
     T& b,
     typename enable_if<has_swap<T>::value>::type* /*unused*/ = NULL)
{
	a.swap(b);
}

/**
 * Manual swap implementation for types that do not have a swap method.
 */
template <typename T>
static void
swap(T& a,
     T& b,
     typename enable_if<!has_swap<T>::value>::type* /*unused*/ = NULL)
{
	T tmp = a;
	a = b;
	b = tmp;
}

} // namespace _detail

template <typename T>
void swap(T& a, T& b)
{
	_detail::swap(a, b);
}

// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
template <typename T>
void rand(T* v, std::streamsize size)
{
	std::ifstream urandom;

	urandom.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	urandom.open("/dev/urandom", std::ios::binary);
	urandom.read(reinterpret_cast<char*>(v), size);
	urandom.close();
}
// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)

} // namespace utils
