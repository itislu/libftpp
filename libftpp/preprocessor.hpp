#pragma once

/* Preprocessor Metaprogramming - Macros for manipulating code as text */

/**
 * @brief Append a unique number to `NAME`
 *
 * This macro uses the common predefined `__COUNTER__` macro, which guarantees a
 * new number every time it is used.
 * In the rare case that `__COUNTER__` is not supported, `__LINE__` is used as a
 * fallback, which can lead to duplicate names.
 *
 * Inspiration: https://stackoverflow.com/a/71899854
 */
#ifdef __COUNTER__
#	define APPEND_UNIQUE_NUM(NAME) CONCAT_EXPANDED(NAME, __COUNTER__)
#else
#	define APPEND_UNIQUE_NUM(NAME) CONCAT_EXPANDED(NAME, __LINE__)
#endif

/**
 * @brief Concatenate `PREFIX` and `SUFFIX` into `PREFIXSUFFIX`
 *
 * Inspiration: https://stackoverflow.com/a/71899854
 */
#define CONCAT(PREFIX, SUFFIX) PREFIX##SUFFIX

/**
 * @brief Expand `PREFIX` and `SUFFIX` before concatenating
 *
 * Inspiration: https://stackoverflow.com/a/71899854
 */
#define CONCAT_EXPANDED(PREFIX, SUFFIX) CONCAT(PREFIX, SUFFIX)
