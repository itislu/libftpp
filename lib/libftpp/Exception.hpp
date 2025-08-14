#pragma once

#include "Optional.hpp"
#include "SourceLocation.hpp"
#include <exception>
#include <string>

namespace ft {

template <typename BaseException>
class StdException;

/**
 * All custom exception classes in libftpp inherit from this.
 */
typedef StdException<std::exception> Exception;

/**
 * @brief Template class to extend `std` exception classes with context
 * information
 *
 * The instantiated template class will be in the same inheritance chain as
 * `BaseException`, so it can be caught in the same ways.
 * However, to get the features and output of `StdException`, an exception needs
 * to be caught as `StdException` with the same template parameter as when
 * thrown.
 *
 * @attention `StdException` classes with different template parameters are not
 * in the same inheritance chain and can only be caught as `StdException` with
 * the SAME template parameter!
 *
 * @note All custom exception classes in libftpp inherit from `Exception`, which
 * is just an alias for `StdException<std::exception>`.
 *
 * @tparam BaseException The base exception class to extend.
 */
template <typename BaseException>
class StdException : public BaseException {
public:
	explicit StdException(const std::string& error);
	StdException(const std::string& error, const ft::SourceLocation& where);
	StdException(const std::string& error, const std::string& who);
	StdException(const std::string& error,
	             const ft::SourceLocation& where,
	             const std::string& who);
	StdException(const StdException& other) throw();
	virtual ~StdException() throw();
	StdException& operator=(StdException other) throw();

	/**
	 * @return An error message in the following format:
	 * `[where().format(): ][who(): ]<error()>`
	 */
	const char* what() const throw();
	void swap(StdException& other) throw();

	StdException& set_where(const ft::SourceLocation& where);
	StdException& set_who(const std::string& who);
	/**
	 * @return The unformatted error message, not including information from
	 * `where()` and `who()`
	 */
	const std::string& error() const throw();
	const ft::Optional<ft::SourceLocation>& where() const throw();
	const ft::Optional<std::string>& who() const throw();

private:
	StdException();

	void _update_what_output();

	std::string _what_output;
	std::string _error;
	ft::Optional<ft::SourceLocation> _where;
	ft::Optional<std::string> _who;
};

template <typename BaseException>
void swap(StdException<BaseException>& lhs,
          StdException<BaseException>& rhs) throw();

} // namespace ft

#include "src/Exception/Exception.tpp" // IWYU pragma: export
