#pragma once

#include <stdint.h>
#include <string>

#if defined(__GNUC__) || defined(__clang__) // GCC, Clang, ICC
#	define SOURCE_LOCATION_CURRENT() \
		(ft::SourceLocation(__LINE__, __FILE__, __PRETTY_FUNCTION__))
#elif defined(_MSC_VER) // MSVC
#	define SOURCE_LOCATION_CURRENT() \
		(ft::SourceLocation(__LINE__, __FILE__, __FUNCSIG__))
#else
#	define SOURCE_LOCATION_CURRENT() \
		(ft::SourceLocation(__LINE__, __FILE__, __func__))
#endif

namespace ft {

/**
 * https://en.cppreference.com/w/cpp/utility/source_location
 */
class SourceLocation {
public:
	SourceLocation() throw();
	SourceLocation(uint_least32_t line,
	               const char* file_name,
	               const char* function_name) throw();
	SourceLocation(const SourceLocation& other) throw();
	~SourceLocation();
	SourceLocation& operator=(SourceLocation other) throw();

	void swap(SourceLocation& other) throw();

	/**
	 * Returns a string in the following format:
	 * `<file_name>:<line>: <function_name>`
	 */
	std::string format() const;

	uint_least32_t line() const throw();
	const char* file_name() const throw();
	const char* function_name() const throw();

private:
	uint_least32_t _line;
	const char* _file_name;
	const char* _function_name;
};

} // namespace ft
