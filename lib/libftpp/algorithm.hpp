#pragma once

#include <iterator>

namespace ft {

/**
 * https://en.cppreference.com/w/cpp/algorithm/count
 */
template <typename InputIt, typename T>
typename std::iterator_traits<InputIt>::difference_type
count(InputIt first, InputIt last, const T& value);

/**
 * https://en.cppreference.com/w/cpp/algorithm/swap
 */
template <typename T>
void swap(T& a, T& b);

/**
 * https://en.cppreference.com/w/cpp/algorithm/transform
 */
template <typename InputIt, typename OutputIt, typename UnaryOp>
OutputIt
transform(InputIt first, InputIt last, OutputIt d_result, UnaryOp unary_op);

} // namespace ft

#include "src/algorithm/count.tpp"     // IWYU pragma: export
#include "src/algorithm/swap.tpp"      // IWYU pragma: export
#include "src/algorithm/transform.tpp" // IWYU pragma: export
