#pragma once

#include "../../Exception.hpp"
#include "../../Optional.hpp"
#include <string>

namespace ft {

template <typename BaseException>
StdException<BaseException>::StdException(
    const std::string& error,
    const ft::Optional<std::string>& who /*= ft::nullopt*/,
    const ft::Optional<std::string>& where /*= ft::nullopt*/)
    : _error(error),
      _who(who && !who->empty() ? who : ft::nullopt),
      _where(where && !where->empty() ? where : ft::nullopt)
{
	_update_what_output();
}

template <typename BaseException>
StdException<BaseException>::StdException(const StdException& other) throw()
{
	try {
		_what_output = other._what_output;
	}
	catch (...) {
		// EMPTY: Exception objects should be nothrow constructable
	}
	try {
		_error = other._error;
	}
	catch (...) {
		// EMPTY: Exception objects should be nothrow constructable
	}
	try {
		_who = other._who;
	}
	catch (...) {
		// EMPTY: Exception objects should be nothrow constructable
	}
	try {
		_where = other._where;
	}
	catch (...) {
		// EMPTY: Exception objects should be nothrow constructable
	}
}

template <typename BaseException>
StdException<BaseException>::~StdException() throw()
{}

template <typename BaseException>
StdException<BaseException>&
StdException<BaseException>::operator=(StdException other) throw()
{
	swap(other);
	return *this;
}

template <typename BaseException>
const char* StdException<BaseException>::what() const throw()
{
	return _what_output.c_str();
}

template <typename BaseException>
void StdException<BaseException>::swap(StdException& other) throw()
{
	_what_output.swap(other._what_output);
	_error.swap(other._error);
	_who.swap(other._who);
	_where.swap(other._where);
}

template <typename BaseException>
StdException<BaseException>&
StdException<BaseException>::set_who(const std::string& who)
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
StdException<BaseException>&
StdException<BaseException>::set_where(const std::string& where)
{
	if (where.empty()) {
		_where.reset();
	}
	else {
		_where = where;
	}
	_update_what_output();
	return *this;
}

template <typename BaseException>
const std::string& StdException<BaseException>::error() const throw()
{
	return _error;
}

template <typename BaseException>
const ft::Optional<std::string>& StdException<BaseException>::who() const
    throw()
{
	return _who;
}

template <typename BaseException>
const ft::Optional<std::string>& StdException<BaseException>::where() const
    throw()
{
	return _where;
}

template <typename BaseException>
void StdException<BaseException>::_update_what_output()
{
	_what_output.clear();
	if (_where) {
		_what_output.append(*_where);
		_what_output.append(": ");
	}
	if (_who) {
		_what_output.append(*_who);
		_what_output.append(": ");
	}
	_what_output.append(_error);
}

template <typename BaseException>
void swap(StdException<BaseException>& lhs,
          StdException<BaseException>& rhs) throw()
{
	lhs.swap(rhs);
}

} // namespace ft
