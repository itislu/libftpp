#pragma once

#include <iterator>
#include <utility>

#ifndef MIN
#	define MIN(a, b) ((b) < (a) ? (b) : (a))
#endif
#ifndef MAX
#	define MAX(a, b) ((b) > (a) ? (b) : (a))
#endif

namespace ft {

/**
 * https://en.cppreference.com/w/cpp/algorithm/copy
 */
template <typename InputIt, typename OutputIt, typename UnaryPred>
OutputIt copy_if(InputIt first, InputIt last, OutputIt d_first, UnaryPred pred);

/**
 * https://en.cppreference.com/w/cpp/algorithm/copy_n
 */
template <typename InputIt, typename Size, typename OutputIt>
OutputIt copy_n(InputIt first, Size count, OutputIt result);

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
 * https://en.cppreference.com/w/cpp/algorithm/is_sorted
 */
template <typename ForwardIt>
bool is_sorted(ForwardIt first, ForwardIt last);
template <typename ForwardIt, typename Compare>
bool is_sorted(ForwardIt first, ForwardIt last, Compare comp);

/**
 * https://en.cppreference.com/w/cpp/algorithm/is_sorted_until
 */
template <typename ForwardIt>
ForwardIt is_sorted_until(ForwardIt first, ForwardIt last);
template <typename ForwardIt, typename Compare>
ForwardIt is_sorted_until(ForwardIt first, ForwardIt last, Compare comp);

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
 * @brief Optimized version of `std::lower_bound` for non-random-access
 * iterators
 *
 * If the size of the range to search is already known, passing it to this
 * functions avoids one full iteration over the range, reducing the worst-case
 * iterations to exactly N.
 *
 * https://en.cppreference.com/w/cpp/algorithm/lower_bound
 */
template <typename ForwardIt, typename T>
ForwardIt
lower_bound(ForwardIt first,
            typename std::iterator_traits<ForwardIt>::difference_type count,
            const T& value);
template <typename ForwardIt, typename T, typename Compare>
ForwardIt
lower_bound(ForwardIt first,
            typename std::iterator_traits<ForwardIt>::difference_type count,
            const T& value,
            Compare comp);

/**
 * @brief Optimized version of `std::upper_bound` for non-random-access
 * iterators
 *
 * If the size of the range to search is already known, passing it to this
 * functions avoids one full iteration over the range, reducing the worst-case
 * iterations to exactly N.
 *
 * https://en.cppreference.com/w/cpp/algorithm/upper_bound
 */
template <typename ForwardIt, typename T>
ForwardIt
upper_bound(ForwardIt first,
            typename std::iterator_traits<ForwardIt>::difference_type count,
            const T& value);
template <typename ForwardIt, typename T, typename Compare>
ForwardIt
upper_bound(ForwardIt first,
            typename std::iterator_traits<ForwardIt>::difference_type count,
            const T& value,
            Compare comp);

/**
 * @brief Optimized version of `std::equal_range` for non-random-access
 * iterators
 *
 * If the size of the range to search is already known, passing it to this
 * functions avoids one full iteration over the range, reducing the worst-case
 * iterations to exactly N.
 *
 * https://en.cppreference.com/w/cpp/algorithm/equal_range
 */
template <typename ForwardIt, typename T>
std::pair<ForwardIt, ForwardIt>
equal_range(ForwardIt first,
            typename std::iterator_traits<ForwardIt>::difference_type count,
            const T& value);
template <typename ForwardIt, typename T, typename Compare>
std::pair<ForwardIt, ForwardIt>
equal_range(ForwardIt first,
            typename std::iterator_traits<ForwardIt>::difference_type count,
            const T& value,
            Compare comp);

/**
 * @brief Optimized version of `std::binary_search` for non-random-access
 * iterators
 *
 * If the size of the range to search is already known, passing it to this
 * functions avoids one full iteration over the range, reducing the worst-case
 * iterations to exactly N.
 *
 * https://en.cppreference.com/w/cpp/algorithm/binary_search
 */
template <typename ForwardIt, typename T>
bool
binary_search(ForwardIt first,
              typename std::iterator_traits<ForwardIt>::difference_type count,
              const T& value);
template <typename ForwardIt, typename T, typename Compare>
bool
binary_search(ForwardIt first,
              typename std::iterator_traits<ForwardIt>::difference_type count,
              const T& value,
              Compare comp);

/**
 * https://en.cppreference.com/w/cpp/algorithm/max
 */
template <typename T>
const T& max(const T& a, const T& b);

/**
 * @brief Non-standard version of `std::max` which allows assigning to the
 * result.
 */
template <typename T>
T& max(T& a, T& b);

/**
 * https://en.cppreference.com/w/cpp/algorithm/min
 */
template <typename T>
const T& min(const T& a, const T& b);

/**
 * @brief Non-standard version of `std::min` which allows assigning to the
 * result.
 */
template <typename T>
T& min(T& a, T& b);

/**
 * https://en.cppreference.com/w/cpp/algorithm/shift
 */
template <typename ForwardIt>
ForwardIt
shift_left(ForwardIt first,
           ForwardIt last,
           typename std::iterator_traits<ForwardIt>::difference_type n);

/**
 * https://en.cppreference.com/w/cpp/algorithm/shift
 */
template <typename ForwardIt>
ForwardIt
shift_right(ForwardIt first,
            ForwardIt last,
            typename std::iterator_traits<ForwardIt>::difference_type n);

/**
 * @brief Generic swap implementation which always uses the type's internal swap
 * function, if possible, otherwise falls back to using a temporary variable.
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

#include "src/algorithm/binary_search.tpp"           // IWYU pragma: export
#include "src/algorithm/copy.tpp"                    // IWYU pragma: export
#include "src/algorithm/count.tpp"                   // IWYU pragma: export
#include "src/algorithm/equal.tpp"                   // IWYU pragma: export
#include "src/algorithm/fill.tpp"                    // IWYU pragma: export
#include "src/algorithm/find_first_of.tpp"           // IWYU pragma: export
#include "src/algorithm/iota.tpp"                    // IWYU pragma: export
#include "src/algorithm/is_sorted.tpp"               // IWYU pragma: export
#include "src/algorithm/lexicographical_compare.tpp" // IWYU pragma: export
#include "src/algorithm/min_max.tpp"                 // IWYU pragma: export
#include "src/algorithm/shift.tpp"                   // IWYU pragma: export
#include "src/algorithm/swap.tpp"                    // IWYU pragma: export
#include "src/algorithm/transform.tpp"               // IWYU pragma: export
