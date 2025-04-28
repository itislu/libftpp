#pragma once

#include "../../functional.hpp"
#include "../../string.hpp"
#include <ios>
#include <string>

namespace ft {
namespace functional {

template <typename T>
T FromString<T>::operator()(const std::string& str)
{
	return ft::from_string<T>(str);
}

template <typename T>
FromStringFmt<T>::FromStringFmt(std::ios::fmtflags fmt_)
    : fmt(fmt_)
{}

template <typename T>
T FromStringFmt<T>::operator()(const std::string& str)
{
	return ft::from_string<T>(str, fmt);
}

} // namespace functional
} // namespace ft
