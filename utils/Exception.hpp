#pragma once

#include <exception>
#include <string>

namespace utils {

class Exception : public std::exception {
public:
	Exception(const std::string& msg,
	          const std::string& where = "",
	          const std::string& who = "");
	Exception(const Exception& other);
	virtual ~Exception() throw();

	Exception& operator=(Exception other);
	void swap(Exception& other);

	const char* what() const throw();
	Exception& set_where(const std::string& where);
	Exception& set_who(const std::string& who);

	const std::string& msg() const;
	const std::string& where() const;
	const std::string& who() const;

private:
	void _update_full_msg();

	std::string _msg;
	std::string _where;
	std::string _who;
	std::string _full_msg;
};

} // namespace utils
