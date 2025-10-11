#include "Exception.hpp"
#include "numeric.hpp"
#include "string.hpp"
#include <climits>
#include <cmath>
#include <exception>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

int main()
{
	{
		const volatile char cv = '*';
		std::cout << ft::numeric_cast<float>(cv) << '\n';
		std::stringstream ss;
		auto f = 2147483648.f;
		char c;
		ss << std::fixed << f;
		ss >> c;
		std::cout << "From: " << std::fixed << f << " (" << typeid(f).name() << ")" << '\n';
		std::cout << "To:   " << c << '\n';
		std::cout << (long)static_cast<char>(f) << '\n';
		std::cout << (ss.fail() ? "Failed" : "Ok") << '\n';
	}
	return 0;
	{
		const double d = std::numeric_limits<double>::max();
		std::cout << static_cast<float>(d) << '\n';
	}
	{
		std::stringstream ss;
		const float f = 2147483648.0f;
		double d;
		ss << f;
		ss >> d;
		std::cout << "From: " << f << '\n';
		std::cout << "To:   " << d << '\n';
		std::cout << (ss.fail() ? "Failed" : "Ok") << '\n';
		// return 0;
	}
	try {
		std::cout << ft::numeric_cast<float>(std::numeric_limits<double>::max())
		          << '\n';
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
	try {
		std::cout << ft::numeric_cast<int>(-INFINITY) << '\n';
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
	try {
		float f = NAN;
		double d = NAN;
		std::cout << *reinterpret_cast<int*>(&f) << '\n';
		std::cout << *reinterpret_cast<int*>(&d) << '\n';
		std::cout << ft::numeric_cast<int>(NAN) << '\n';
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
	try {
		std::cout << ft::numeric_cast<unsigned int>(
		    std::numeric_limits<unsigned long>::max())
		          << '\n';
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
	try {
		std::cout << ft::numeric_cast<unsigned int>(-1) << '\n';
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
	try {
		std::cout << ft::numeric_cast<char>(42) << '\n';
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
	try {
		std::cout << ft::numeric_cast<float>('*') << '\n';
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
	try {
		std::cout << ft::numeric_cast<char>(9.5f) << '\n';
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
	try {
		std::cout << ft::numeric_cast<float>((double)-INFINITY) << '\n';
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
	try {
		std::cout << ft::numeric_cast<bool>(2) << '\n';
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}

	std::cout << "\nfrom_string:\n";
	try {
		std::cout << ft::from_string<char>("*") << '\n';
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
	try {
		std::cout << ft::from_string<char>("0") << '\n';
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
	try {
		std::cout << ft::from_string<int>("2147483648") << '\n';
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
