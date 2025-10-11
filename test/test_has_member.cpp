#include "type_traits.hpp"
#include <iostream>

template <class T>
struct is_member_function_pointer_helper : ft::false_type {};

template <class T, class U>
struct is_member_function_pointer_helper<T U::*> : ft::is_function<T> {};

template <class T>
struct is_member_function_pointer
    : is_member_function_pointer_helper<typename ft::remove_cv<T>::type> {};

struct A {
	void swap(A& other) /* const */ {}
};

struct B {
	void swap(A& other) {}
	int swap(B& other) { return 0; }
};

struct C {
	void test(C& other) {}
	void test(B& other) {}
	void test(A& other) {}
};

struct D {
	int swap;
};

template <typename ToCheck, void (ToCheck::*)(A&)>
struct Sfinae {};

template <typename U, typename = void>
struct Impl : ft::false_type {};

template <typename U>
struct Impl<U, typename ft::voider<Sfinae<U, &U::swap> >::type>
    : ft::true_type {};

template <typename U>
struct Impl<U, typename ft::voider<Sfinae<U, &U::test> >::type>
    : ft::true_type {};

int main()
{
	std::cout << ft::has_member_function_swap<A>::value << '\n';
	std::cout << ft::has_member_function_swap<B>::value << '\n';
	std::cout << ft::has_member_function_swap<C>::value << '\n';
	std::cout << ft::has_member_function_swap<D>::value << '\n';

	// std::cout << Impl<A>::value << '\n';
	// std::cout << Impl<B>::value << '\n';
	// std::cout << Impl<C>::value << '\n';
	// std::cout << Impl<A>::value << '\n';
	// std::cout << Impl<B>::value << '\n';
	// std::cout << Impl<C>::value << '\n';
}
