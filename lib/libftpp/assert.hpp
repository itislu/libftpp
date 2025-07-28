#pragma once

#include "preprocessor.hpp"

/**
 * @brief Performs a compile-time assertion that works in C++98
 *
 * This implementation enhances a common template technique to create an
 * assertion by making it work in all scopes.
 *
 * Usage: `STATIC_ASSERT(21 + 21 == 42);`
 * A comment in the same line as STATIC_ASSERT can be used as an error message.
 *
 * How it works:
 * 1. `ft::static_assert::Impl<bool(EXPR)>`: This template is intentionally left
 * incomplete for the false case. When `EXPR` is true, it resolves to a complete
 * type; when `EXPR` is false, it resolves to an incomplete type.
 *
 * 2. `sizeof(...)`: The `sizeof` operator is a compile-time construct.
 * Crucially, applying `sizeof` to an incomplete type is a compile-time error.
 * This provides the core assertion mechanism.
 *
 * 3. `APPEND_UNIQUE_NUM(...)`: Generates unique enum names, preventing
 * redefinition errors when multiple assertions are used in the same scope.
 *
 * 4. `enum { ... }`: The `enum` wrapper serves two purposes. First, it provides
 * a declaration context for the `sizeof` check, making the macro valid at file
 * scope (where statements are not allowed). Second, it naturally avoids any
 * "unused" warnings.
 *
 * The common `typedef char name[(EXPR) ? 1 : -1]` solution is avoided because
 * it can trigger "-Wunused-local-typedefs" warnings when used inside a
 * function.
 * Another common `1 / ((EXPR) ? 1 : 0)` technique, leveraging division by zero,
 * is also avoided because of its longer error messages.
 *
 * Helpful article: https://www.drdobbs.com/compile-time-assertions/184401873
 */
#define STATIC_ASSERT(EXPR)                              \
	enum {                                               \
		APPEND_UNIQUE_NUM(static_assert_) =              \
		    sizeof(ft::_static_assert::Impl<bool(EXPR)>) \
	}

#include "src/assert/static_assert.tpp" // IWYU pragma: export
