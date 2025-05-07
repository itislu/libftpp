#include "../../Exception.hpp"
#include "../../Optional.hpp"
#include "../../format.hpp"
#include <string>

namespace ft {

Exception::Exception(const std::string& msg,
                     const ft::Optional<std::string>& who /*= ft::nullopt*/,
                     const ft::Optional<std::string>& where /*= ft::nullopt*/)
    : _msg(msg),
      _who(who && !who->empty() ? who : ft::nullopt),
      _where(where && !where->empty() ? where : ft::nullopt)
{
	_update_what_output();
}

Exception::Exception(const Exception& other) throw()
{
	try {
		_what_output = other._what_output;
	}
	catch (...) {
		// REASON: Exception objects should be nothrow constructable
	}
	try {
		_msg = other._msg;
	}
	catch (...) {
		// REASON: Exception objects should be nothrow constructable
	}
	try {
		_who = other._who;
	}
	catch (...) {
		// REASON: Exception objects should be nothrow constructable
	}
	try {
		_where = other._where;
	}
	catch (...) {
		// REASON: Exception objects should be nothrow constructable
	}
}

Exception::~Exception() throw() {}

Exception& Exception::operator=(Exception other) throw()
{
	swap(other);
	return *this;
}

const char* Exception::what() const throw() { return _what_output.c_str(); }

void Exception::swap(Exception& other) throw()
{
	_what_output.swap(other._what_output);
	_msg.swap(other._msg);
	_who.swap(other._who);
	_where.swap(other._where);
}

Exception& Exception::set_who(const std::string& who)
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

Exception& Exception::set_where(const std::string& where)
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

const std::string& Exception::msg() const throw() { return _msg; }

const ft::Optional<std::string>& Exception::who() const throw() { return _who; }

const ft::Optional<std::string>& Exception::where() const throw()
{
	return _where;
}

void Exception::_update_what_output()
{
	_what_output = (_where ? GRAY(*_where + ": ") : "")
	               + (_who ? *_who + ": " : "") + _msg;
}

void swap(Exception& lhs, Exception& rhs) throw() { lhs.swap(rhs); }

} // namespace ft
