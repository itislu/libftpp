#pragma once

#include "../../assert.hpp"

namespace ft {
namespace _static_assert {

template <bool>
struct Impl;

template <>
struct Impl<true> {
	static const bool static_assertion_failed = false;
};

} // namespace _static_assert
} // namespace ft
