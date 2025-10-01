#pragma once

#include <stdint.h>
#include <string>

#if defined(__GNUC__) || defined(__clang__)
#	define SOURCE_LOCATION_CURRENT()                                  \
		(ft::source_location(__LINE__, __FILE__, __PRETTY_FUNCTION__))
#elif defined(_MSC_VER)
#	define SOURCE_LOCATION_CURRENT()                          \
		(ft::source_location(__LINE__, __FILE__, __FUNCSIG__))
#else
#	define SOURCE_LOCATION_CURRENT()                       \
		(ft::source_location(__LINE__, __FILE__, __func__))
#endif

namespace ft {

/**
 * https://en.cppreference.com/w/cpp/utility/source_location
 */
class source_location {
public:
	source_location() throw();
	source_location(uint_least32_t line,
	                const char* file_name,
	                const char* function_name) throw();
	source_location(const source_location& other) throw();
	~source_location();
	source_location& operator=(const source_location& other) throw();

	/**
	 * @return A string in the following format:
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
