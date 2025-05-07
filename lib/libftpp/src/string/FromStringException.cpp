#include "../../Exception.hpp"
#include "../../algorithm.hpp"
#include "../../string.hpp"
#include "../../utility.hpp"
#include <cerrno>
#include <cstring>
#include <string>
#include <typeinfo>

namespace ft {

FromStringException::FromStringException(const std::string& msg,
                                         const std::string& input,
                                         const std::type_info& type_id)
    : ft::Exception(msg, "ft::from_string"),
      _input(input),
      _type_id(&type_id)
{}

FromStringException::FromStringException(
    const FromStringException& other) throw()
    : ft::Exception(other),
      _type_id(other._type_id)
{
	try {
		_input = other._input;
	}
	catch (...) {
		// REASON: Exception objects should be nothrow constructable
	}
}

FromStringException::~FromStringException() throw() {}

FromStringException&
FromStringException::operator=(FromStringException other) throw()
{
	swap(other);
	return *this;
}

const std::string& FromStringException::input() const throw() { return _input; }

const std::type_info& FromStringException::type_id() const throw()
{
	return *_type_id;
}

void FromStringException::swap(FromStringException& other) throw()
{
	_input.swap(other._input);
	ft::swap(_type_id, other._type_id);
}

FromStringRangeException::FromStringRangeException(
    const std::string& input,
    const std::type_info& type_id)
    : FromStringException(std::string(std::strerror(ERANGE)) + " ("
                              + ft::demangle(type_id.name()) + "): \"" + input
                              + "\"",
                          input,
                          type_id)
{}

FromStringInvalidException::FromStringInvalidException(
    const std::string& input,
    const std::type_info& type_id)
    : FromStringException(std::string("Cannot convert to ")
                              + ft::demangle(type_id.name()) + ": \"" + input
                              + "\"",
                          input,
                          type_id)
{}

} // namespace ft
