#include "../../SourceLocation.hpp"
#include "../../algorithm.hpp"
#include <sstream>
#include <stdint.h>
#include <string>

namespace ft {

SourceLocation::SourceLocation() throw()
    : _line(0),
      _file_name(""),
      _function_name("")
{}

SourceLocation::SourceLocation(uint_least32_t line,
                               const char* file_name,
                               const char* function_name) throw()
    : _line(line),
      _file_name(file_name),
      _function_name(function_name)
{}

SourceLocation::SourceLocation(const SourceLocation& other) throw()
    : _line(other._line),
      _file_name(other._file_name),
      _function_name(other._function_name)
{}

SourceLocation::~SourceLocation() {}

SourceLocation& SourceLocation::operator=(SourceLocation other) throw()
{
	swap(other);
	return *this;
}

void SourceLocation::swap(SourceLocation& other) throw()
{
	ft::swap(_line, other._line);
	ft::swap(_file_name, other._file_name);
	ft::swap(_function_name, other._function_name);
}

std::string SourceLocation::format() const
{
	std::ostringstream os;

	os << _file_name << ":" << _line << ": " << _function_name;
	return os.str();
}

uint_least32_t SourceLocation::line() const throw() { return _line; }

const char* SourceLocation::file_name() const throw() { return _file_name; }

const char* SourceLocation::function_name() const throw()
{
	return _function_name;
}

} // namespace ft
