#pragma once

#include "Optional.hpp"
#include <exception>
#include <string>

namespace ft {

class Exception : public std::exception {
public:
	explicit Exception(const std::string& msg,
	                   const ft::Optional<std::string>& who = ft::nullopt,
	                   const ft::Optional<std::string>& where = ft::nullopt);
	Exception(const Exception& other) throw();
	virtual ~Exception() throw();
	Exception& operator=(Exception other) throw();

	const char* what() const throw();
	void swap(Exception& other) throw();

	Exception& set_who(const std::string& who);
	Exception& set_where(const std::string& where);
	const std::string& msg() const throw();
	const ft::Optional<std::string>& who() const throw();
	const ft::Optional<std::string>& where() const throw();

private:
	Exception();

	void _update_what_output();

	std::string _what_output;
	std::string _msg;
	ft::Optional<std::string> _who;
	ft::Optional<std::string> _where;
};

void swap(Exception& lhs, Exception& rhs) throw();

} // namespace ft
