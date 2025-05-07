#include "../../Exception.hpp"
#include "../../format.hpp"
#include <string>

namespace ft {

Exception::Exception(const std::string& msg,
                     const std::string& who /*= ""*/,
                     const std::string& where /*= ""*/)
    : _msg(msg),
      _who(who),
      _where(where)
{
	_update_what_output();
}

Exception::Exception(const Exception& other) throw()
{
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
	try {
		_what_output = other._what_output;
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
	_msg.swap(other._msg);
	_who.swap(other._who);
	_where.swap(other._where);
	_what_output.swap(other._what_output);
}

Exception& Exception::set_who(const std::string& who)
{
	_who = who;
	_update_what_output();
	return *this;
}

Exception& Exception::set_where(const std::string& where)
{
	_where = where;
	_update_what_output();
	return *this;
}

const std::string& Exception::msg() const throw() { return _msg; }

const std::string& Exception::who() const throw() { return _who; }

const std::string& Exception::where() const throw() { return _where; }

void Exception::_update_what_output()
{
	_what_output = (_where.empty() ? "" : GRAY(_where + ": "))
	               + (_who.empty() ? "" : _who + ": ") + _msg;
}

void swap(Exception& lhs, Exception& rhs) throw() { lhs.swap(rhs); }

} // namespace ft
