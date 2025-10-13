// NOLINTBEGIN

#include "libftpp/type_traits.hpp"
#include <iomanip>
#include <iostream>
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

class NonDestructable {
	~NonDestructable(); // Not destructible
};

struct TestClass {
	int const_func() const { return 0; }
	void regular_func() {}
	static int static_func() { return 0; }
};

typedef int (TestClass::*ConstMemFuncPtr)() const;
typedef void (TestClass::*RegularMemFuncPtr)();
typedef int (*StaticFuncPtr)();

int const_func() { return 0; }
void regular_func() {}
int static_func() { return 0; }

typedef int (&ConstFuncRef)();
typedef void (&RegularFuncRef)();
typedef int (&StaticFuncRef)();

typedef int func_const_t() const;
typedef void func_void_const_t() const;
typedef int func_regular_t();
typedef void func_void_regular_t();

#if __cplusplus >= 201102L
#	define TRY(FROM, TO, SHOW)                                              \
		do {                                                                 \
			if (SHOW                                                         \
			    || ft::is_convertible<FROM, TO>::value                       \
			           != std::is_convertible<FROM, TO>::value) {            \
				std::cout << "ft:  " << ft::is_convertible<FROM, TO>::value  \
				          << " (is_convertible<" #FROM ", " #TO ">)" << '\n' \
				          << "std: " << std::is_convertible<FROM, TO>::value \
				          << " (is_convertible<" #FROM ", " #TO ">)"         \
				          << "\n\n";                                         \
			}                                                                \
		} while (0);
#else
#	define TRY(FROM, TO, SHOW)                                               \
		do {                                                                  \
			if (SHOW) {                                                       \
				std::cout << "ft:  " << ft::is_convertible<FROM, TO>::value   \
				          << " (is_convertible<" #FROM ", " #TO ">)" << '\n'; \
			}                                                                 \
			else {                                                            \
				(void)ft::is_convertible<FROM, TO>::value;                    \
			}                                                                 \
		} while (0);
#endif

int main()
{
	// std::cout << std::boolalpha;

	// Abstract variations
	TRY(Abstract, Abstract, false)
	TRY(Abstract, Abstract&, false)
	TRY(Abstract, const Abstract&, false)
	TRY(Abstract&, Abstract, false)
	TRY(Abstract&, Abstract&, false)
	TRY(Abstract&, const Abstract&, false)
	TRY(const Abstract&, Abstract, false)
	TRY(const Abstract&, Abstract&, false)
	TRY(const Abstract&, const Abstract&, false)
	TRY(Abstract, volatile Abstract&, false)
	TRY(Abstract&, volatile Abstract&, false)
	TRY(const Abstract&, volatile Abstract&, false)
	TRY(volatile Abstract&, const Abstract&, false)

	// Inheritance
	TRY(Abstract, Base, false)
	TRY(Abstract, Base&, false)
	TRY(Abstract, const Base&, false)
	TRY(Abstract&, Base, false)
	TRY(Abstract&, Base&, false)
	TRY(Abstract&, const Base&, false)
	TRY(const Abstract&, Base, false)
	TRY(const Abstract&, Base&, false)
	TRY(const Abstract&, const Base&, false)
	TRY(Abstract, Derived, false)
	TRY(Abstract, Derived&, false)
	TRY(Abstract, const Derived&, false)
	TRY(Abstract&, Derived, false)
	TRY(Abstract&, Derived&, false)
	TRY(Abstract&, const Derived&, false)
	TRY(const Abstract&, Derived, false)
	TRY(const Abstract&, Derived&, false)
	TRY(const Abstract&, const Derived&, false)

	// Derived/Base/Other
	TRY(Base, Base&, false)
	TRY(Base&, Base, false)
	TRY(Derived, Base, false)
	TRY(Derived, Base&, false)
	TRY(Derived&, Base, false)
	TRY(Derived&, Base&, false)
	TRY(Base&, Derived, false)
	TRY(Base&, Derived&, false)
	TRY(Other, Base, false)
	TRY(Other, Base&, false)
	TRY(Base&, Other, false)
	TRY(Base&, Other&, false)

	// Pointer conversions
	TRY(Derived*, Base*, false)
	TRY(Derived*, Abstract*, false)
	TRY(Derived*, void*, false)
	TRY(Base*, Derived*, false)
	TRY(Base*, Abstract*, false)
	TRY(void*, Base*, false)
	TRY(Base*, void*, false)
	TRY(Other*, Base*, false)

	// void and void*
	TRY(void, void, false)
	TRY(void, Abstract, false)
	TRY(Abstract, void, false)
	TRY(Base*, void*, false)
	TRY(void*, Base*, false)

	std::cout << "--- Array cases ---\n";
	TRY(int[2], int (&)[2], false)
	TRY(arr_t, arr_t, false)
	TRY(arr_t, int*, false)
	TRY(arr_t, const int*, false)
	TRY(arr_t, int (&)[3], false)
	TRY(arr_t, const int (&)[3], false)
	TRY(int*, arr_t, false)
	TRY(int*, int (&)[3], false)
	TRY(arr_t&, int*, false)
	TRY(absarr_t, Abstract*, false)
	TRY(absarr_t, Abstract * (&)[5], false)
	TRY(absarr_t, Abstract* [5], false)

	std::cout << "--- Function cases ---\n";
	TRY(func_t, func_t, false)
	TRY(func_t, func_t*, false)
	TRY(func_t, func_t&, false)
	TRY(func_t*, func_t*, false)
	TRY(func_t&, func_t*, false)
	TRY(funci_t, void (*)(), false)
	TRY(func_t*, void*, false)

	std::cout << "--- is_convertible with explicit/implicit ctors ---\n";
	TRY(X, Implicit, false)
	TRY(X, Explicit, false) // This should be false (explicit!)
	TRY(X&, Implicit, false)
	TRY(X&, Explicit, false)
	TRY(const X&, Implicit, false)
	TRY(const X&, Explicit, false)
	// Down-conversions, up-conversions, pointers:
	TRY(X*, Implicit, false) // Should be false
	TRY(X*, Explicit, false) // Should be false
	// Add assignment-matching tests
	TRY(Implicit, Implicit, false) // Should be true (copy)
	TRY(Explicit, Explicit, false) // Should be true (copy)

	TRY(Abstract*, Abstract*, false)
	TRY(Abstract, int, false)
	TRY(Abstract, float, false)

	TRY(Abstract, DerivedAbstract, false)
	TRY(Abstract, DerivedAbstract&, false)
	TRY(Abstract, const DerivedAbstract&, false)
	TRY(Abstract&, DerivedAbstract, false)
	TRY(Abstract&, DerivedAbstract&, false)
	TRY(Abstract&, const DerivedAbstract&, false)
	TRY(const Abstract&, DerivedAbstract, false)
	TRY(const Abstract&, DerivedAbstract&, false)
	TRY(const Abstract&, const DerivedAbstract&, false)
	TRY(DerivedAbstract, Base, false)
	TRY(DerivedAbstract, Base&, false)
	TRY(DerivedAbstract, const Base&, false)
	TRY(DerivedAbstract&, Base, false)
	TRY(DerivedAbstract&, Base&, false)
	TRY(DerivedAbstract&, const Base&, false)
	TRY(const DerivedAbstract&, Base, false)
	TRY(const DerivedAbstract&, Base&, false)
	TRY(const DerivedAbstract&, const Base&, false)
	TRY(DerivedAbstract, Derived, false)
	TRY(DerivedAbstract, Derived&, false)
	TRY(DerivedAbstract, const Derived&, false)
	TRY(DerivedAbstract&, Derived, false)
	TRY(DerivedAbstract&, Derived&, false)
	TRY(DerivedAbstract&, const Derived&, false)
	TRY(const DerivedAbstract&, Derived, false)
	TRY(const DerivedAbstract&, Derived&, false)
	TRY(const DerivedAbstract&, const Derived&, false)

	TRY(int(), int (*)(), false)
	TRY(void(int), void (*)(int), false)

	TRY(const B&, A&, false)
	TRY(B&, const A&, false)
	TRY(B, const A&, false)
	TRY(B, A&, false)

	TRY(void, int, false)
	TRY(int[], int*, false)
	TRY(int() const, int (*)(), false)
	TRY(int() const, int() const, false)
	TRY(int() const, int(), false)
	TRY(int(), int() const, false)
	TRY(int() const, int() const&, false)

	TRY(ConstMemFuncPtr, ConstMemFuncPtr, false)
	TRY(RegularMemFuncPtr, RegularMemFuncPtr, false)
	TRY(ConstMemFuncPtr, RegularMemFuncPtr, false)
	TRY(RegularMemFuncPtr, ConstMemFuncPtr, false)
	TRY(StaticFuncPtr, StaticFuncPtr, false)
	TRY(ConstMemFuncPtr, StaticFuncPtr, false)

	TRY(ConstFuncRef, ConstFuncRef, false)
	TRY(RegularFuncRef, RegularFuncRef, false)
	TRY(ConstFuncRef, RegularFuncRef, false)
	TRY(RegularFuncRef, ConstFuncRef, false)
	TRY(StaticFuncRef, StaticFuncRef, false)
	TRY(ConstFuncRef, StaticFuncRef, false)
	TRY(func_const_t, func_const_t, false)
	TRY(func_void_const_t, func_void_const_t, false)
	TRY(func_regular_t, func_regular_t, false)
	TRY(func_void_regular_t, func_void_regular_t, false)

	// Cross-conversions between const and non-const function types
	TRY(func_const_t, func_regular_t, false)
	TRY(func_regular_t, func_const_t, false)
	TRY(func_void_const_t, func_void_regular_t, false)
	TRY(func_void_regular_t, func_void_const_t, false)

	// Function type to pointer conversions
	TRY(func_const_t, int (*)(), false)
	TRY(func_regular_t, int (*)(), false)
	// TRY(func_const_t, int(*)() const, false) // This doesn't exist
	// TRY(func_regular_t, int(*)() const, false) // This doesn't exist

	// Function type to reference conversions
	TRY(func_regular_t, func_regular_t&, false)
	TRY(func_const_t, func_regular_t&, false)

	std::cout << "is_function: " << ft::is_function<int() const>::value << '\n';
	std::cout << "is_const: " << ft::is_const<int() const>::value << '\n';
	std::cout << "is_same<add_lvalue_reference...: "
	          << ft::is_same<ft::add_lvalue_reference<int() const>::type,
	                         int() const>::value
	          << '\n';
	std::cout
	    << "is_same<remove_const...: "
	    << ft::is_same<ft::remove_const<int() const>::type, int() const>::value
	    << '\n';
	struct Test {
		ft::add_lvalue_reference<int() const>::type t;
		ft::remove_cv<int() const>::type t2;
		// std::decay<int() const>::type t3;
	};
	typedef int const_func_t() const; // This is how to typedef it

#ifdef LIBFTPP_BUILTIN_IS_CONVERTIBLE
	TRY(int, NonCopyable, false) // private access
	TRY(NonDestructable, NonDestructable, false) // private access
#endif
	TRY(A, NonDestructable, false) // private access
	TRY(NonDestructable, B, false) // private access
}

// NOLINTEND
