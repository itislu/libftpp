// NOLINTBEGIN

#include "type_traits.hpp"
#include <iomanip>
#include <iostream>
#include <typeinfo>
#if __cplusplus >= 201102L
#	include <type_traits>
#endif

struct Abstract {
	virtual void f() = 0;
	operator float() const { return 0; }
};
struct DerivedAbstract : Abstract {};
struct Base : Abstract {
	void f() {}
};
struct Derived : Base {};
struct Other {};

struct Abstract2 {
	virtual void f() = 0;
	operator Base() const { return Base(); }
};

typedef int arr_t[3];
typedef Abstract* absarr_t[5];
typedef void func_t();
typedef int funci_t(int);

struct X {};
struct Implicit {
	Implicit(const X&) {}
};
struct Explicit {
	explicit Explicit(const X&) {}
};

struct A {};
struct B : A {};

struct NonCopyable {
	NonCopyable(int);

private:
	NonCopyable(const NonCopyable&); // Not copyable
};

template <typename T, typename U>
struct is_same {
	static const bool value = false;
};

template <typename T>
struct is_same<T, T> {
	static const bool value = true;
};

#if __cplusplus >= 201102L
#	define TEST_TYPE(TYPE, SHOW)                                              \
		do {                                                                   \
			typedef ft::add_lvalue_reference<TYPE>::type ft_result;            \
			typedef std::add_lvalue_reference<TYPE>::type std_result;          \
			bool types_match = std::is_same<ft_result, std_result>::value;     \
			if (SHOW || !types_match) {                                        \
				std::cout << "Type: " #TYPE "\n";                              \
				/* std::cout << "ft::add_lvalue_reference<" #TYPE ">::type = " \
				          << typeid(ft_result).name() << '\n';                 \
				std::cout << "std::add_lvalue_reference<" #TYPE ">::type = "   \
				          << typeid(std_result).name() << '\n'; */             \
				std::cout << "Match: " << (types_match ? "YES" : "NO")         \
				          << "\n\n";                                           \
			}                                                                  \
		} while (0);
#else
#	define TEST_TYPE(TYPE, SHOW)                                              \
		do {                                                                   \
			typedef ft::add_lvalue_reference<TYPE>::type ft_result;            \
			if (SHOW) {                                                        \
				std::cout << "Type: " #TYPE "\n";                              \
				/* std::cout << "ft::add_lvalue_reference<" #TYPE ">::type = " \
				          << typeid(ft_result).name() << "\n\n"; */            \
			}                                                                  \
			/* Just use the typedef to ensure instantiation */                 \
			/* (void)typeid(ft_result).name(); */                              \
		} while (0);
#endif

int main()
{
	std::cout << "=== Testing ft::add_lvalue_reference ===\n\n";

	// Basic types
	std::cout << "--- Basic types ---\n";
	TEST_TYPE(int, false)
	TEST_TYPE(float, false)
	TEST_TYPE(double, false)
	TEST_TYPE(char, false)
	TEST_TYPE(bool, false)
	TEST_TYPE(void, false)

	// Pointer types
	std::cout << "--- Pointer types ---\n";
	TEST_TYPE(int*, false)
	TEST_TYPE(void*, false)
	TEST_TYPE(char*, false)

	// Reference types
	std::cout << "--- Reference types ---\n";
	TEST_TYPE(int&, false)
	TEST_TYPE(const int&, false)
	TEST_TYPE(volatile int&, false)
	TEST_TYPE(const volatile int&, false)

	// CV-qualified types
	std::cout << "--- CV-qualified types ---\n";
	TEST_TYPE(const int, false)
	TEST_TYPE(volatile int, false)
	TEST_TYPE(const volatile int, false)
	TEST_TYPE(const char*, false)
	TEST_TYPE(volatile char*, false)
	TEST_TYPE(const volatile char*, false)

	// Abstract classes and inheritance
	std::cout << "--- Abstract and inheritance ---\n";
	TEST_TYPE(Abstract, false)
	TEST_TYPE(Abstract&, false)
	TEST_TYPE(const Abstract&, false)
	TEST_TYPE(volatile Abstract&, false)
	TEST_TYPE(const volatile Abstract&, false)
	TEST_TYPE(Abstract*, false)
	TEST_TYPE(const Abstract*, false)
	TEST_TYPE(DerivedAbstract, false)
	TEST_TYPE(DerivedAbstract&, false)
	TEST_TYPE(const DerivedAbstract&, false)
	TEST_TYPE(Base, false)
	TEST_TYPE(Base&, false)
	TEST_TYPE(const Base&, false)
	TEST_TYPE(Derived, false)
	TEST_TYPE(Derived&, false)
	TEST_TYPE(const Derived&, false)
	TEST_TYPE(Other, false)
	TEST_TYPE(Other&, false)
	TEST_TYPE(const Other&, false)

	// Abstract2 class
	std::cout << "--- Abstract2 class ---\n";
	TEST_TYPE(Abstract2, false)
	TEST_TYPE(Abstract2&, false)
	TEST_TYPE(const Abstract2&, false)

	// Array types
	std::cout << "--- Array types ---\n";
	TEST_TYPE(arr_t, false)
	TEST_TYPE(arr_t&, false)
	TEST_TYPE(const arr_t&, false)
	TEST_TYPE(absarr_t, false)
	TEST_TYPE(absarr_t&, false)
	TEST_TYPE(const absarr_t&, false)
	TEST_TYPE(int[3], false)
	TEST_TYPE(int (&)[3], false)
	TEST_TYPE(const int (&)[3], false)
	TEST_TYPE(Abstract* [5], false)
	TEST_TYPE(Abstract * (&)[5], false)
	TEST_TYPE(const Abstract*(&)[5], false)
	TEST_TYPE(int[], false) // Incomplete array type

	// Function types
	std::cout << "--- Function types ---\n";
	TEST_TYPE(func_t, false)
	TEST_TYPE(func_t&, false)
	TEST_TYPE(func_t*, false)
	TEST_TYPE(funci_t, false)
	TEST_TYPE(funci_t&, false)
	TEST_TYPE(funci_t*, false)
	TEST_TYPE(void(), false)
	TEST_TYPE(void (*)(), false)
	TEST_TYPE(void (&)(), false)
	TEST_TYPE(void(int), false)
	TEST_TYPE(void (*)(int), false)
	TEST_TYPE(void (&)(int), false)
	TEST_TYPE(int(), false)
	TEST_TYPE(int (*)(), false)
	TEST_TYPE(int (&)(), false)

	// Struct types for explicit/implicit conversion tests
	std::cout << "--- Custom struct types ---\n";
	TEST_TYPE(X, false)
	TEST_TYPE(X&, false)
	TEST_TYPE(const X&, false)
	TEST_TYPE(X*, false)
	TEST_TYPE(Implicit, false)
	TEST_TYPE(Implicit&, false)
	TEST_TYPE(const Implicit&, false)
	TEST_TYPE(Explicit, false)
	TEST_TYPE(Explicit&, false)
	TEST_TYPE(const Explicit&, false)

	// A/B inheritance types
	std::cout << "--- A/B inheritance types ---\n";
	TEST_TYPE(A, false)
	TEST_TYPE(A&, false)
	TEST_TYPE(const A&, false)
	TEST_TYPE(B, false)
	TEST_TYPE(B&, false)
	TEST_TYPE(const B&, false)

	// Non-copyable type
	std::cout << "--- Non-copyable type ---\n";
	TEST_TYPE(NonCopyable, false)
	TEST_TYPE(NonCopyable&, false)
	TEST_TYPE(const NonCopyable&, false)

	// Member function pointer types
	std::cout << "--- Member function pointer types ---\n";
	TEST_TYPE(void (Abstract::*)(), false)
	TEST_TYPE(void (Abstract::*)() const, false)
	TEST_TYPE(int (Base::*)(), false)
	TEST_TYPE(void(Abstract::*&)(), false)
	// TEST_TYPE(const void (Abstract::*&)(), false) // const on return type has
	// no effect

	// Member data pointer types
	std::cout << "--- Member data pointer types ---\n";
	TEST_TYPE(int Abstract::*, false)
	TEST_TYPE(float Base::*, false)
	TEST_TYPE(int Abstract::*&, false)
	TEST_TYPE(const int Abstract::*&, false)

	// More complex types
	std::cout << "--- Complex types ---\n";
	TEST_TYPE(int**, false)
	TEST_TYPE(int**&, false)
	TEST_TYPE(const int**&, false)
	TEST_TYPE(int* const*, false)
	TEST_TYPE(const int* const*, false)
	TEST_TYPE(int (*)[3], false)
	TEST_TYPE(int (*&)[3], false)
	TEST_TYPE(const int (*&)[3], false)

	// Edge cases that might cause issues
	std::cout << "--- Edge cases ---\n";
	TEST_TYPE(void*, false)
	TEST_TYPE(void*&, false)
	TEST_TYPE(const void*&, false)
	TEST_TYPE(void**, false)
	TEST_TYPE(void**&, false)
	TEST_TYPE(int() const, false)
#if __cplusplus >= 201103L
	TEST_TYPE(void() &, false) // Function reference with ref-qualifier
#endif

	struct Test {
		ft::add_lvalue_reference<int() const>::type f;
	};

	std::cout << "=== Test completed ===\n";
}

// NOLINTEND
