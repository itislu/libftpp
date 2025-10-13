#include "Expected.hpp"
#include <expected>
#include <iostream>
#include <string>

std::expected<int, std::string> std_f(std::expected<int, std::string> exp)
{
    if (exp) {
        std::cout << "std inside: yes" << '\n';
    }
    else {
        std::cout << "std inside: no" << '\n';
    }

    std::string str("hi");
    return std::unexpected("str");
    return 0;
}

ft::Expected<int, std::string> ft_f(ft::Expected<int, std::string> exp)
{
    if (exp) {
        std::cout << "ft inside: yes" << '\n';
    }
    else {
        std::cout << "ft inside: no" << '\n';
    }

    std::string str("hi");
    return ft::Unexpected<std::string>("str");
    return 0;
}

int main()
{
    if (std_f(std::unexpected("0"))) {
        std::cout << "std outside: yes" << '\n';
    }
    else {
        std::cout << "std outside: no" << '\n';
    }
    
    if (ft_f(ft::Unexpected<std::string>("0"))) {
        std::cout << "ft outside: yes" << '\n';
    }
    else {
        std::cout << "ft outside: no" << '\n';
    }
}
