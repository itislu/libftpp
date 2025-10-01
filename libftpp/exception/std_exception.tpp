// IWYU pragma: private; include "libftpp/exception.hpp"
#pragma once

#include "libftpp/algorithm.hpp"
#include "libftpp/exception.hpp"
#include "libftpp/optional.hpp"
#include "libftpp/source_location.hpp"
#include <string>

namespace ft {

template <typename BaseException>
std_exception<BaseException>::std_exception(const std::string& error)
    : _error(error)
{
	_update_what_output();
}

template <typename BaseException>
std_exception<BaseException>::std_exception(const std::string& error,
                                            const ft::source_location& where)
    : _error(error),
      _where(where)
{
	_update_what_output();
}

template <typename BaseException>
std_exception<BaseException>::std_exception(const std::string& error,
                                            const std::string& who)
    : _error(error),
      _who(!who.empty() ? ft::optional<std::string>(who) : ft::nullopt)
{
	_update_what_output();
}

template <typename BaseException>
std_exception<BaseException>::std_exception(const std::string& error,
                                            const ft::source_location& where,
                                            const std::string& who)
    : _error(error),
      _where(where),
      _who(!who.empty() ? ft::optional<std::string>(who) : ft::nullopt)
{
	_update_what_output();
}

template <typename BaseException>
std_exception<BaseException>::std_exception(const std_exception& other) throw()
{
	try {
		_what_output = other._what_output;
	}
	catch (...) {
		// EMPTY: Exception objects should be nothrow constructable.
	}
	try {
		_error = other._error;
	}
	catch (...) {
		// EMPTY: Exception objects should be nothrow constructable.
	}
	try {
		_where = other._where;
	}
	catch (...) {
		// EMPTY: Exception objects should be nothrow constructable.
	}
	try {
		_who = other._who;
	}
	catch (...) {
		// EMPTY: Exception objects should be nothrow constructable.
	}
}

template <typename BaseException>
std_exception<BaseException>::~std_exception() throw()
{}

template <typename BaseException>
std_exception<BaseException>&
std_exception<BaseException>::operator=(std_exception other) throw()
{
	swap(other);
	return *this;
}

template <typename BaseException>
const char* std_exception<BaseException>::what() const throw()
{
	return _what_output.c_str();
}

template <typename BaseException>
void std_exception<BaseException>::swap(std_exception& other) throw()
{
	ft::swap(_what_output, other._what_output);
	ft::swap(_error, other._error);
	ft::swap(_where, other._where);
	ft::swap(_who, other._who);
}

template <typename BaseException>
std_exception<BaseException>&
std_exception<BaseException>::set_where(const ft::source_location& where)
{
	_where = where;
	_update_what_output();
	return *this;
}

template <typename BaseException>
std_exception<BaseException>&
std_exception<BaseException>::set_who(const std::string& who)
{
	if (who.empty()) {
		_who.reset();
	}
	else {
		_who = who;
	}
	_update_what_output();
	return *this;
}

template <typename BaseException>
const std::string& std_exception<BaseException>::error() const throw()
{
	return _error;
}

template <typename BaseException>
const ft::optional<ft::source_location>&
std_exception<BaseException>::where() const throw()
{
	return _where;
}

template <typename BaseException>
const ft::optional<std::string>& std_exception<BaseException>::who() const
    throw()
{
	return _who;
}

template <typename BaseException>
void std_exception<BaseException>::_update_what_output()
{
	_what_output.clear();
	if (_where.has_value()) {
		_what_output.append(_where->format());
		_what_output.append(": ");
	}
	if (_who.has_value()) {
		_what_output.append(*_who);
		_what_output.append(": ");
	}
	_what_output.append(_error);
}

template <typename BaseException>
void swap(std_exception<BaseException>& lhs,
          std_exception<BaseException>& rhs) throw()
{
	lhs.swap(rhs);
}

} // namespace ft
