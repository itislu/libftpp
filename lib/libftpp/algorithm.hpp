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
 * https://en.cppreference.com/w/cpp/algorithm/equal
 */
template <typename InputIt1, typename InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2);
template <typename InputIt1, typename InputIt2, typename BinaryPred>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPred p);
template <typename InputIt1, typename InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2);
template <typename InputIt1, typename InputIt2, typename BinaryPred>
bool equal(InputIt1 first1,
           InputIt1 last1,
           InputIt2 first2,
           InputIt2 last2,
           BinaryPred p);

/**
 * https://en.cppreference.com/w/cpp/algorithm/fill
 */
template <typename ForwardIt, typename T>
void fill(ForwardIt first, ForwardIt last, const T& value);

/**
 * https://en.cppreference.com/w/cpp/algorithm/fill_n
 */
template <typename OutputIt, typename Size, typename T>
OutputIt fill_n(OutputIt first, Size count, const T& value);

/**
 * https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
 */
template <typename InputIt1, typename InputIt2>
bool lexicographical_compare(InputIt1 first1,
                             InputIt1 last1,
                             InputIt2 first2,
                             InputIt2 last2);
template <typename InputIt1, typename InputIt2, typename Compare>
bool lexicographical_compare(InputIt1 first1,
                             InputIt1 last1,
                             InputIt2 first2,
                             InputIt2 last2,
                             Compare comp);

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

#include "src/algorithm/count.tpp"                   // IWYU pragma: export
#include "src/algorithm/equal.tpp"                   // IWYU pragma: export
#include "src/algorithm/fill.tpp"                    // IWYU pragma: export
#include "src/algorithm/lexicographical_compare.tpp" // IWYU pragma: export
#include "src/algorithm/swap.tpp"                    // IWYU pragma: export
#include "src/algorithm/transform.tpp"               // IWYU pragma: export
