#pragma once

#include <iterator>

#ifndef MIN
#	define MIN(a, b) ((b) < (a) ? (b) : (a))
#endif
#ifndef MAX
#	define MAX(a, b) ((b) > (a) ? (b) : (a))
#endif

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
 * https://en.cppreference.com/w/cpp/algorithm/find_first_of
 */
template <typename InputIt, typename ForwardIt>
InputIt
find_first_of(InputIt first, InputIt last, ForwardIt s_first, ForwardIt s_last);
template <typename InputIt, typename ForwardIt, typename BinaryPred>
InputIt find_first_of(InputIt first,
                      InputIt last,
                      ForwardIt s_first,
                      ForwardIt s_last,
                      BinaryPred p);

/**
 * https://en.cppreference.com/w/cpp/algorithm/iota
 */
template <typename ForwardIt, typename T>
void iota(ForwardIt first, ForwardIt last, T value);

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
 * https://en.cppreference.com/w/cpp/algorithm/max
 */
template <typename T>
const T& max(const T& a, const T& b);

/**
 * Non-standard. Useful for assigning to the result.
 */
template <typename T>
T& max(T& a, T& b);

/**
 * https://en.cppreference.com/w/cpp/algorithm/min
 */
template <typename T>
const T& min(const T& a, const T& b);

/**
 * Non-standard. Useful for assigning to the result.
 */
template <typename T>
T& min(T& a, T& b);

/**
 * Generic swap implementation which always uses the type's internal swap, if
 * possible, otherwise falls back to copy-and-swap.
 *
 * https://en.cppreference.com/w/cpp/algorithm/swap
 */
template <typename T>
void swap(T& a, T& b);

/**
 * https://en.cppreference.com/w/cpp/algorithm/iter_swap
 */
template <typename ForwardIt1, typename ForwardIt2>
void iter_swap(ForwardIt1 a, ForwardIt2 b);

/**
 * https://en.cppreference.com/w/cpp/algorithm/swap_ranges
 */
template <typename ForwardIt1, typename ForwardIt2>
ForwardIt2 swap_ranges(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2);

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
#include "src/algorithm/find_first_of.tpp"           // IWYU pragma: export
#include "src/algorithm/iota.tpp"                    // IWYU pragma: export
#include "src/algorithm/lexicographical_compare.tpp" // IWYU pragma: export
#include "src/algorithm/min_max.tpp"                 // IWYU pragma: export
#include "src/algorithm/swap.tpp"                    // IWYU pragma: export
#include "src/algorithm/transform.tpp"               // IWYU pragma: export
