#include "libftpp/assert.hpp"
#include "libftpp/optional.hpp"
#include "libftpp/type_traits.hpp"
#include "libftpp/utility.hpp"
#include <iostream>
#include <vector>

struct test {};

struct wrapper {
	struct test {};
};

// namespace ft {
// void f()
// {
// 	long arr[4];
//     long *ptr = arr;

//     std::cout << FT_COUNTOF(arr) << '\n';
// 	std::cout << FT_COUNTOF(ptr) << '\n';
// }
// }

int main()
{
	enum E {
		one
	};

	typedef long (&ArrayRef)[4];
	long arr[4];
	ArrayRef arr_ref = arr;
	long* ptr = arr;
	long* const c_ptr = ptr;
	const long n = 0;
	const char* str = "";
	char* str2 = (char*)str;
	std::vector<long> vec;
	E enm = one;
	E e_arr[4];
	E* e_ptr = e_arr;
	ft::optional<long>* opt_ptr = 0;
    wrapper w;

	FT_STATIC_ASSERT(ft::is_reference<ArrayRef>::value);
	FT_STATIC_ASSERT(!ft::is_array<ArrayRef>::value);

	std::cout << FT_COUNTOF(arr) << '\n';
	std::cout << FT_COUNTOF(arr_ref) << '\n';
	// std::cout << FT_COUNTOF(ArrayRef) << '\n';
	// std::cout << sizeof(ArrayRef) << '\n';
	// std::cout << FT_COUNTOF(ptr) << '\n';
	// std::cout << FT_COUNTOF(c_ptr) << '\n';
	// std::cout << FT_COUNTOF(n) << '\n';
	// std::cout << FT_COUNTOF("string") << '\n';
	// std::cout << FT_COUNTOF(str) << '\n';
	// std::cout << FT_COUNTOF(str2) << '\n';
	// std::cout << FT_COUNTOF(vec) << '\n';
	// std::cout << FT_COUNTOF(one) << '\n';
	// std::cout << FT_COUNTOF(enm) << '\n';
	// std::cout << FT_COUNTOF(e_arr) << '\n';
	// std::cout << FT_COUNTOF(e_ptr) << '\n';
	// std::cout << FT_COUNTOF(opt_ptr) << '\n';
}
