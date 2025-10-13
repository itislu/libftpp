#include "Expected.hpp"
#include "Optional.hpp"
#include <iostream>
#include <string>

int main()
{
	ft::Expected<void, std::string> void_exp;
	ft::Expected<int, std::string> int_exp;

    void_exp.error() = "bad";

    if (void_exp.has_value()) {
        std::cout << "void_exp has value\n";
    }
    else {
        std::cout << "void_exp has error\n";
    }
    if (int_exp.has_value()) {
        std::cout << "int_exp has value\n";
    }
    else {
        std::cout << "int_exp has error\n";
    }

	// if (void_exp == int_exp) {
	if (int_exp == void_exp) {
		std::cout << "equal\n";
	}
	else {
		std::cout << "not equal\n";
	}
}
