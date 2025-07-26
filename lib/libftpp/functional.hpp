#pragma once

namespace ft {

/**
 * @brief Provides a uniform way to query properties of function types
 *
 * Supports functions with up to 10 parameters, including variadic functions
 * and "abominable" function types.
 * No members are defined for non-function types (SFINAE-friendly).
 * Pointers and references to functions are not function types.
 *
 * Available members for function types:
 * - `arity`: number of parameters (excluding variadic part)
 * - `result_type`: return type
 * - `argument_type<N>::type`: type of the Nth parameter (0-indexed)
 *   - Only available when `N` >= `arity` - except for functions with no
 *     parameters, then `argument_type<0>::type` is `void`.
 *
 * Conceptually similar to `std::numeric_limits` and `std::iterator_traits`.
 * Member names are chosen to fit in with `<functional>`.
 * Non-standard.
 */
template <typename F>
struct function_traits;

} // namespace ft

#include "src/functional/function_traits.tpp" // IWYU pragma: export
