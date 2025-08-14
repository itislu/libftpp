#pragma once

#include "../../Exception.hpp"
#include "../../Optional.hpp"
#include "../../SourceLocation.hpp"
#include "../../algorithm.hpp"
#include <string>

namespace ft {

template <typename BaseException>
StdException<BaseException>::StdException(const std::string& error)
    : _error(error)
{
	_update_what_output();
}

template <typename BaseException>
StdException<BaseException>::StdException(const std::string& error,
                                          const ft::SourceLocation& where)
    : _error(error),
      _where(where)
{
	_update_what_output();
}

template <typename BaseException>
StdException<BaseException>::StdException(const std::string& error,
                                          const std::string& who)
    : _error(error),
      _who(!who.empty() ? ft::Optional<std::string>(who) : ft::nullopt)
{
	_update_what_output();
}

template <typename BaseException>
StdException<BaseException>::StdException(const std::string& error,
                                          const ft::SourceLocation& where,
                                          const std::string& who)
    : _error(error),
      _where(where),
      _who(!who.empty() ? ft::Optional<std::string>(who) : ft::nullopt)
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
		_where = other._where;
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
	ft::swap(_what_output, other._what_output);
	ft::swap(_error, other._error);
	ft::swap(_where, other._where);
	ft::swap(_who, other._who);
}

template <typename BaseException>
StdException<BaseException>&
StdException<BaseException>::set_where(const ft::SourceLocation& where)
{
	_where = where;
	_update_what_output();
	return *this;
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
const std::string& StdException<BaseException>::error() const throw()
{
	return _error;
}

template <typename BaseException>
const ft::Optional<ft::SourceLocation>&
StdException<BaseException>::where() const throw()
{
	return _where;
}

template <typename BaseException>
const ft::Optional<std::string>& StdException<BaseException>::who() const
    throw()
{
	return _who;
}

template <typename BaseException>
void StdException<BaseException>::_update_what_output()
{
	_what_output.clear();
	if (_where) {
		_what_output.append(_where->format());
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
