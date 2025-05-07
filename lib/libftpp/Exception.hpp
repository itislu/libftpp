#pragma once

#include <exception>
#include <string>

namespace ft {

class Exception : public std::exception {
public:
	explicit Exception(const std::string& msg,
	                   const std::string& who = "",
	                   const std::string& where = "");
	Exception(const Exception& other) throw();
	virtual ~Exception() throw();
	Exception& operator=(Exception other) throw();

	const char* what() const throw();
	void swap(Exception& other) throw();

	Exception& set_who(const std::string& who);
	Exception& set_where(const std::string& where);
	const std::string& msg() const throw();
	const std::string& who() const throw();
	const std::string& where() const throw();

private:
	Exception();

	void _update_what_output();

	std::string _msg;
	std::string _who;
	std::string _where;
	std::string _what_output;
};

void swap(Exception& lhs, Exception& rhs) throw();

} // namespace ft
