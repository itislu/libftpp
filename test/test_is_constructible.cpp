#include "type_traits.hpp"
#include <iostream>
#if __cplusplus >= 201102L
#	include <type_traits>
#endif

#if __cplusplus >= 201102L
#	define TRY(T, ARG, SHOW)                                                \
		do {                                                                 \
			if (SHOW                                                         \
			    || ft::is_constructible<T, ARG>::value                       \
			           != std::is_constructible<T, ARG>::value) {            \
				std::cout << "ft:  " << ft::is_constructible<T, ARG>::value  \
				          << " (is_constructible<" #T ", " #ARG ">)" << '\n' \
				          << "std: " << std::is_constructible<T, ARG>::value \
				          << " (is_constructible<" #T ", " #ARG ">)"         \
				          << "\n\n";                                         \
			}                                                                \
		} while (0);
#else
#	define TRY(T, ARG, SHOW)                                                 \
		do {                                                                  \
			if (SHOW) {                                                       \
				std::cout << "ft:  " << ft::is_constructible<T, ARG>::value   \
				          << " (is_constructible<" #T ", " #ARG ">)" << '\n'; \
			}                                                                 \
			else {                                                            \
				(void)ft::is_constructible<T, ARG>::value;                    \
			}                                                                 \
		} while (0);
#endif

struct A {};

struct B {
	B(const A&) {}
};

int main()
{
    TRY(B, A, true);
    TRY(A, B, true);
    TRY(int[2], int[2], true);
}
