#pragma once

#include "common.hpp"
#include <fstream>
#include <ios>

namespace utils {

template <typename T>
void swap(T& a, T& b) throw()
{
	T tmp = a;
	a = b;
	b = tmp;
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
