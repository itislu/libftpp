#include "../Exception.hpp"
#include "../common.hpp"
#include <string>

namespace ft {

Exception::Exception(const std::string& msg,
                     const std::string& where /*= ""*/,
                     const std::string& who /*= ""*/)
    : _msg(msg),
      _where(where),
      _who(who)
{
	_update_full_msg();
}

Exception::Exception(const Exception& other)
    : _msg(other._msg),
      _where(other._where),
      _who(other._who),
      _full_msg(other._full_msg)
{}

Exception::~Exception() throw() {}

Exception& Exception::operator=(Exception other) throw()
{
	swap(other);
	return *this;
}

const char* Exception::what() const throw() { return _full_msg.c_str(); }

void Exception::swap(Exception& other) throw()
{
	_msg.swap(other._msg);
	_where.swap(other._where);
	_who.swap(other._who);
	_full_msg.swap(other._full_msg);
}

Exception& Exception::set_where(const std::string& where)
{
	_where = where;
	_update_full_msg();
	return *this;
}

Exception& Exception::set_who(const std::string& who)
{
	_who = who;
	_update_full_msg();
	return *this;
}

const std::string& Exception::msg() const throw() { return _msg; }

const std::string& Exception::where() const throw() { return _where; }

const std::string& Exception::who() const throw() { return _who; }

void Exception::_update_full_msg()
{
	_full_msg = (_where.empty() ? "" : GRAY(_where + ": "))
	            + (_who.empty() ? "" : _who + ": ") + _msg;
}

void swap(Exception& a, Exception& b) { a.swap(b); }

} // namespace ft
