#pragma once

#include "../../functional.hpp"
#include <iostream>
#include <ostream>

namespace ft {
namespace functional {

template <typename T>
Print<T>::Print(std::ostream& os)
    : ostream(os)
{}

template <typename T>
void Print<T>::operator()(const T& v)
{
	ostream << v;
}

} // namespace functional
} // namespace ft
