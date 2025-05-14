#pragma once

#include "Exception.hpp"
#include "Expected.hpp"
#include <cstddef>
#include <ios>
#include <new>
#include <string>
#include <typeinfo>

namespace ft {

/* starts_with */

/**
 * https://en.cppreference.com/w/cpp/string/basic_string/starts_with
 */
bool starts_with(const std::string& str, const std::string& prefix);
bool starts_with(const std::string& str, char prefix);
bool starts_with(const std::string& str, unsigned char prefix);

/* ends_with */

/**
 * https://en.cppreference.com/w/cpp/string/basic_string/ends_with
 */
bool ends_with(const std::string& str, const std::string& suffix);
bool ends_with(const std::string& str, char suffix);
bool ends_with(const std::string& str, unsigned char suffix);

/* from_string */

class FromStringException;
class FromStringRangeException;
class FromStringInvalidException;

/**
 * @brief Parses a string and converts it to a value of the specified type `To`
 *
 * Default rules (when `fmt` is not provided):
 * - Leading whitespace is *not* skipped. Use `std::ios::skipws` in `fmt` to
 * enable skipping.
 * - For integral types, the base is auto-detected from prefixes: `0` for octal,
 *   `0x` or `0X` for hexadecimal. If no prefix is present, base 10 is assumed.
 *   A standalone hex-prefix is considered invalid. The base can be explicitly
 *   set using `std::ios::dec`, `std::ios::oct`, `std::ios::hex` in `fmt`.
 * - For `bool`, accepts alphabetic ("true", "false") and numeric ("1", "0")
 *   representations. `std::ios::boolalpha` in `fmt` restricts parsing to
 *   alphabetic only.
 *
 * Parsing stops at the first invalid character for the expected format, target
 * type or base.
 *
 * Overloads with the `nothrow` parameter return a `ft::Expected` and do not
 * throw exceptions on conversion errors.
 *
 * @return For throwing overloads: The converted value of type `To`
 * @return For non-throwing overloads: A `ft::Expected<To,
 * ft::FromStringException>` containing the converted value on success, or a
 * `ft::FromStringException` on failure
 *
 * @throws ft::FromStringInvalidException (Throwing overloads only) If the
 * string `str` does not represent a valid value for type `To` according to the
 * specified format (e.g., non-numeric characters for an integer, invalid base
 * prefix, or non-boolean string for `bool`)
 * @throws ft::FromStringRangeException (Throwing overloads only) If the parsed
 * value is valid but falls outside the representable range of type `To`. For
 * `bool` using numeric format, this is thrown if the value is numeric but not 1
 * or 0
 *
 * @tparam To The target type to convert the string to
 * @param str The input string to parse
 * @param endpos_out (optional) Out-parameter which, if not null, is set to the
 * number of characters processed from `str`, even if an error occurs
 */
template <typename To>
To from_string(const std::string& str,
               std::string::size_type* endpos_out = NULL);
/**
 * @copydoc from_string(const std::string&, std::string::size_type*)
 */
template <>
inline bool from_string<bool>(const std::string& str,
                              std::string::size_type* endpos_out /*= NULL*/);
/**
 * @copydoc from_string(const std::string&, std::string::size_type*)
 *
 * @param fmt (optional) Stream format flags (`std::ios::fmtflags`) to control
 * parsing behavior (e.g., base, skipping whitespace, scientific notation)
 */
template <typename To>
To from_string(const std::string& str,
               std::ios::fmtflags fmt,
               std::string::size_type* endpos_out = NULL);
/**
 * @copydoc from_string(const std::string&, std::string::size_type*)
 *
 * @param nothrow (optional) A tag (`std::nothrow`) selecting the non-throwing
 * overload
 */
template <typename To>
ft::Expected<To, ft::FromStringException>
from_string(const std::string& str,
            std::nothrow_t nothrow,
            std::string::size_type* endpos_out = NULL);
/**
 * @copydoc from_string(const std::string&, std::string::size_type*)
 *
 * @param fmt (optional) Stream format flags (`std::ios::fmtflags`) to control
 * parsing behavior (e.g., base, skipping whitespace, scientific notation)
 * @param nothrow (optional) A tag (`std::nothrow`) selecting the non-throwing
 * overload
 */
template <typename To>
ft::Expected<To, ft::FromStringException>
from_string(const std::string& str,
            std::ios::fmtflags fmt,
            std::nothrow_t nothrow,
            std::string::size_type* endpos_out = NULL);

class FromStringException : public ft::Exception {
public:
	FromStringException(const std::string& msg,
	                    const std::string& input,
	                    const std::type_info& type_id);
	FromStringException(const FromStringException& other) throw();
	~FromStringException() throw();
	FromStringException& operator=(FromStringException other) throw();

	const std::string& input() const throw();
	const std::type_info& type_id() const throw();
	void swap(FromStringException& other) throw();

private:
	FromStringException();

	std::string _input;
	const std::type_info* _type_id;
};

class FromStringRangeException : public FromStringException {
public:
	FromStringRangeException(const std::string& input,
	                         const std::type_info& type_id);
};

class FromStringInvalidException : public FromStringException {
public:
	FromStringInvalidException(const std::string& input,
	                           const std::type_info& type_id);
};

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)

// Functor
template <typename T>
struct FromString {
	T operator()(const std::string& str);
};

// Functor
template <typename T>
struct FromStringFmt {
	explicit FromStringFmt(std::ios::fmtflags fmt_);

	T operator()(const std::string& str);

	std::ios::fmtflags fmt;
};

// NOLINTEND(misc-non-private-member-variables-in-classes)

/* to_string */

/**
 * https://en.cppreference.com/w/cpp/string/basic_string/to_string
 */
template <typename T>
std::string to_string(T v, std::ios::fmtflags fmt = std::ios::fmtflags());
std::string to_string(bool v, std::ios::fmtflags fmt = std::ios::boolalpha);

/* trim */

std::string& trim(std::string& str);
std::string trim(const std::string& str);

} // namespace ft

#include "src/string/FromString.tpp"  // IWYU pragma: export
#include "src/string/from_string.tpp" // IWYU pragma: export
#include "src/string/to_string.tpp"   // IWYU pragma: export
