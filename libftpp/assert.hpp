#pragma once

#include "libftpp/assert/static_assert.ipp"

/**
 * @brief Performs a compile-time assertion that works in C++98
 *
 * Usage: `FT_STATIC_ASSERT(21 + 21 == 42);`
 * A comment in the same line as FT_STATIC_ASSERT can be used as an error
 * message.
 *
 * Inspiration:
 * https://web.archive.org/web/20130323104707/https://www.drdobbs.com/compile-time-assertions/184401873
 */
#define FT_STATIC_ASSERT(EXPR) LIBFTPP_STATIC_ASSERT_IMPL(EXPR)
