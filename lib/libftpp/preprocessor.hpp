#pragma once

/* Preprocessor Metaprogramming - Macros for manipulating code as text */

/**
 * Append the line number of the invocation of this macro.
 * Example: `int APPEND_LINE_NUM(counter) = 0;` would produce `int counter7 = 0`
 * if the call is on line 7.
 *
 * https://stackoverflow.com/a/71899854/24880406
 */
#define APPEND_LINE_NUM(NAME) CONCAT_EXPANDED(NAME, __LINE__)

/**
 * Concatenate `PREFIX` and `SUFFIX` into `PREFIXSUFFIX`.
 *
 * https://stackoverflow.com/a/71899854/24880406
 */
#define CONCAT(PREFIX, SUFFIX) PREFIX##SUFFIX

/**
 * Expand `PREFIX` and `SUFFIX` before concatenating.
 *
 * https://stackoverflow.com/a/71899854/24880406
 */
#define CONCAT_EXPANDED(PREFIX, SUFFIX) CONCAT(PREFIX, SUFFIX)
