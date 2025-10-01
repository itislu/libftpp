#pragma once

#include "libftpp/optional.hpp"
#include "libftpp/source_location.hpp"
#include <exception>
#include <string>

namespace ft {

template <typename BaseException>
class std_exception;

/**
 * All custom exception classes in libftpp inherit from this.
 */
typedef std_exception<std::exception> exception;

/**
 * @brief Template class to extend `std` exception classes with context
 * information
 *
 * The instantiated template class will be in the same inheritance chain as
 * `BaseException`, so it can be caught in the same ways.
 * However, to get the features and output of `std_exception`, an exception
 * needs to be caught as `std_exception` with the same template parameter as
 * when thrown.
 *
 * @attention `std_exception` classes with different template parameters are not
 * in the same inheritance chain and can only be caught as `std_exception` with
 * the SAME template parameter!
 *
 * @note All custom exception classes in libftpp inherit from `exception`, which
 * is just an alias for `std_exception<std::exception>`.
 *
 * @tparam BaseException The base exception class to extend.
 */
template <typename BaseException>
class std_exception : public BaseException {
public:
	explicit std_exception(const std::string& error);
	std_exception(const std::string& error, const ft::source_location& where);
	std_exception(const std::string& error, const std::string& who);
	std_exception(const std::string& error,
	              const ft::source_location& where,
	              const std::string& who);
	std_exception(const std_exception& other) throw();
	virtual ~std_exception() throw();
	std_exception& operator=(std_exception other) throw();

	/**
	 * @return An error message in the following format:
	 * `[where().format(): ][who(): ]<error()>`
	 */
	const char* what() const throw();
	void swap(std_exception& other) throw();

	std_exception& set_where(const ft::source_location& where);
	std_exception& set_who(const std::string& who);
	/**
	 * @return The unformatted error message, not including information from
	 * `where()` and `who()`
	 */
	const std::string& error() const throw();
	const ft::optional<ft::source_location>& where() const throw();
	const ft::optional<std::string>& who() const throw();

private:
	std_exception();

	void _update_what_output();

	std::string _what_output;
	std::string _error;
	ft::optional<ft::source_location> _where;
	ft::optional<std::string> _who;
};

template <typename BaseException>
void swap(std_exception<BaseException>& lhs,
          std_exception<BaseException>& rhs) throw();

} // namespace ft

#include "libftpp/exception/std_exception.tpp" // IWYU pragma: export
