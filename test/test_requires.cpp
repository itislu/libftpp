#include "functional.hpp"
#include "type_traits.hpp"
#include <iostream>
#include <limits>
#if __cplusplus > 201103L
#	include <type_traits>
#endif

template <typename T>
struct crash : crash<void(T)> {};

void do_crash()
{
	// crash<int>::type c;
}

struct tmp {};

struct Abstract {
	virtual ~Abstract() = 0;
};

template <typename F>
struct remove_const_function : ft::type_identity<F> {};

template <typename F>
struct remove_const_function<F() const> : ft::type_identity<F()> {};

// A simple function
int subtract(int a, int b) {
    return a - b;
}

template <typename T>
struct Test {

};

template <typename T>
FT_REQUIRES(ft::negation<ft::is_integral<T> >::value && std::integral<T>)
(int) test_requires(T) {return 1;}

// template <typename T>
// FT_REQUIRES(ft::is_integral<T>::value)
// (int) test_requires2(T) {return 2;}

template <typename T>
ft::enable_if<ft::is_integral<T>::value, int>
test_requires2(T) {return 2;}

template <typename F, unsigned N, typename = void>
struct test_sfinae : ft::false_type {};

template <typename F, unsigned N>
struct test_sfinae<F, N, typename ft::voider<typename ft::function_traits<F>::template argument_type<N>::type>::type>
	: ft::true_type {};

void f()
{
	ft::function_traits<int(char, long)>::argument_type<1>::type a;
}

template <typename T>
requires std::is_integral<T>::value && std::integral<T>
void print(T t)
{
	std::cout << t << '\n';
}

int main()
{
	if (std::integral<int>) {
		std::cout << "(std::integral<int>) is true\n";
	}
	bool test_sfinae_0 = test_sfinae<int(char, long), 0>::value;
	bool test_sfinae_1 = test_sfinae<int(char, long), 1>::value;
	bool test_sfinae_2 = test_sfinae<int(char, long), 2>::value;
	std::cout << "test_sfinae_0: " << test_sfinae_0 << '\n';
	std::cout << "test_sfinae_1: " << test_sfinae_1 << '\n';
	std::cout << "test_sfinae_2: " << test_sfinae_2 << '\n';

	std::cout << test_requires("4") << '\n';

	typedef std::make_signed<void> a;
	// typedef ft::parameter_type<void> b;

	// Define the function pointer type
    using FuncPtr = int(*)(int, int);

    // 1. A regular function pointer
    FuncPtr p_func = &subtract;

    // 2. A reference to that function pointer
    FuncPtr& ref_p_func = p_func;

	int i1 = p_func(1, 2);
	int i2 = ref_p_func(1, 2);

    // --- Using the type traits ---

    // Get the result type from the function pointer type
    using ResultType1 = std::invoke_result<FuncPtr, int, int>::type;
    // C++17 alias template for convenience:
    using ResultType1_t = std::invoke_result_t<FuncPtr, int, int>;


    // Get the result type from the REFERENCE to the function pointer type
    using ResultType2 = std::invoke_result<int (&)(int, int), int, int>::type;
    // C++17 alias template:
    using ResultType2_t = std::invoke_result_t<decltype(ref_p_func), int, int>;
	
	// ft::_type_traits::function_info<int (*&)(char)>::parameter_type r;
	// ft::parameter_type<int (*)(char)>::type r1;
	// ft::parameter_type<Abstract>::type *r2;
	// ft::return_type<int[1]>::type r2;
	// ft::parameter_type<int(int, ...), 1>::type r3;

	// std::common_type<long, tmp>::type // No type

	do_crash();

	// ft::return_type<char(int, int, int, int, int, int, int, int, int, int)
	//                     const>::type r4 = 'a';
	// std::cout << "r1 = " << r4 << '\n';

	// ft::parameter_type<
	//     int(char, char, char, char, char, char, char, char, char, const char&, ...)
	//         const volatile,
	//     9>::type p1 = 'a';
	// std::cout << "p1 = " << p1 << '\n';

	// int i3 = (long)&do_crash % 2 ? 1 : 2;
	// FT_STATIC_ASSERT(i3 == 1);
	// static_assert(i3 == 1);
}
