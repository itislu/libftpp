#pragma once

/**
 * Performs compile-time assertion checking.
 *
 * Usage: `STATIC_ASSERT(21 + 21 == 42);`
 *
 * A comment in the same line as STATIC_ASSERT can be used as an error message.
 */
#define STATIC_ASSERT(expr) (ft::StaticAssert<(expr)>())

namespace ft {

/**
 * Performs compile-time assertion checking.
 *
 * Usage: `ft::StaticAssert<21 + 21 == 42>();`
 *
 * A comment in the same line as ft::StaticAssert can be used as an error
 * message.
 */
template <bool>
struct StaticAssert;
template <>
struct StaticAssert<true> {};

} // namespace ft
