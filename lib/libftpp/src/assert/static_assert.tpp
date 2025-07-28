#pragma once

#include "../../assert.hpp"

namespace ft {
namespace _static_assert {

template <bool>
struct Impl;

template <>
struct Impl<true> {};

} // namespace _static_assert
} // namespace ft
