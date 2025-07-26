#pragma once

#include "../../type_traits.hpp"
#include "_type_traits.hpp"

namespace ft {
namespace _type_traits {

namespace _type_or_null {
template <typename T, typename = void>
struct Impl;
} // namespace _type_or_null

template <typename T>
struct type_or_null : _type_or_null::Impl<T> {};

namespace _type_or_null {

template <typename T, typename /*= void*/>
struct Impl : type_identity<null_type> {};

template <typename T>
struct Impl<T, typename voider<typename T::type>::type>
    : type_identity<typename T::type> {};

} // namespace _type_or_null

} // namespace _type_traits
} // namespace ft
