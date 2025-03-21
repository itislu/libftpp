#pragma once

#include <exception>
#include <string>

namespace utils {

/**
 * Important: Always catch by reference!
 * Catching by value risks a call to std::terminate because this class contains
 * std::strings which could throw bad_alloc when copy constructed.
 */
class Exception : public std::exception {
public:
	explicit Exception(const std::string& msg,
	                   const std::string& where = "",
	                   const std::string& who = "");
	Exception(const Exception& other);
	virtual ~Exception() throw();
	Exception& operator=(Exception other) throw();

	const char* what() const throw();
	void swap(Exception& other) throw();

	Exception& set_where(const std::string& where);
	Exception& set_who(const std::string& who);
	const std::string& msg() const throw();
	const std::string& where() const throw();
	const std::string& who() const throw();

private:
	void _update_full_msg();

	std::string _msg;
	std::string _where;
	std::string _who;
	std::string _full_msg;
};

} // namespace utils
