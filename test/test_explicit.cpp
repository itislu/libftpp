#include "Expected.hpp"
#include "Optional.hpp"
#if __cplusplus >= 202302L
#include <expected>
#endif
#include <iostream>
#include <optional>
#include <string>

struct Abstract { virtual void f() = 0; };

class A {};

class B {
public:
	B() = default;
	/* explicit */ B(const A&) { std::cout << "B()" << '\n'; }
};

void f(const B&) {}

#if __cplusplus >= 202302L
void std_f(const std::expected<B, int>&) {}
// void std_f(const std::expected<A, int>&) {}
#endif

void ft_f(const ft::Expected<B, int>&) {}
// void ft_f(const ft::Expected<A, int>&) {}

int main(int argc, char* argv[])
{
	(void)argc, (void)argv;

	// f(A());

#if __cplusplus >= 202302L
	// std_f(std::expected<B, int>());
#endif
	// ft_f(ft::Expected<B, int>());
#if __cplusplus >= 202302L
	std_f(std::expected<A, int>());
	std::cout << "std_f\n";
#endif
	ft_f(ft::Expected<A, int>());
    
	// ft::Expected<B, int> b;
	// b = B();
	// std::cout << "done\n";
	// ft_f(b);
	
#if __cplusplus >= 202302L
	// std_f(std::expected<Abstract, Abstract>());
#endif
	// ft_f(ft::Expected<Abstract, Abstract>());
}
