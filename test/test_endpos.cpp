#include "format.hpp"
#include "string.hpp"
#include <charconv>
#include <cstddef>
#include <cstring>
#include <exception>
#include <ios>
#include <iostream>
#include <string>

int main()
{
	const char* const nptr = "99999999999999999True";
	std::size_t endpos = 4242;

	{
		std::cout << FT_BOLD("ft::from_string") << '\n';
		endpos = 4242;
		try {
			std::cout << ft::from_string<bool>(
			    nptr, std::ios::boolalpha | std::ios::uppercase, &endpos)
			          << '\n';
		}
		catch (const std::exception& e) {
			std::cout << "Exception: " << e.what() << '\n';
		}
		std::cout << "endpos: " << endpos << '\n';
	}

	{
		std::cout << '\n' << FT_BOLD("std::sto*") << '\n';
		endpos = 4242;
		try {
			std::cout << std::stof(nptr, &endpos/* , 0 */) << '\n';
		}
		catch (const std::exception& e) {
			std::cout << "Exception: " << e.what() << '\n';
		}
		std::cout << "endpos: " << endpos << '\n';
	}

	{
		std::cout << '\n' << FT_BOLD("std::from_chars") << '\n';
		int value = 0;
		const char* start = nptr;
		const char* end = start + std::strlen(nptr);
		std::from_chars_result result = std::from_chars(start, end, value);

		// Calculate position analogous to endpos
		std::ptrdiff_t chars_processed = result.ptr - start;

		if (result.ec == std::errc()) {
			std::cout << value << '\n';
		}
		else if (result.ec == std::errc::result_out_of_range) {
			std::cout << "Exception: Value out of range\n";
		}
		else if (result.ec == std::errc::invalid_argument) {
			std::cout << "Exception: Invalid argument\n";
		}
		else {
			std::cout << "Exception: Unknown error\n";
		}
		std::cout << "chars processed: " << chars_processed << '\n';
	}
}
