// NOLINTBEGIN

#include "type_traits.hpp"
#include <climits>
#include <iomanip>
#include <iostream>
#if __cplusplus >= 201102L
#	include <type_traits>
#endif

struct A { // not abstract
	int m;
};

class B { // not abstract
	virtual void f() {}
};

class C { // abstract
	virtual void f() = 0;
};

class D : public C { // not abstract
	void f() {}
};

struct E { // abstract
	virtual ~E() = 0;
};

E::~E() {}

struct F : E {}; // abstract

struct G : F {}; // abstract

struct H : G { // not abstract
	~H() {}
};

union U { // not abstract
	int i;
	float f;
};

enum E_ {
	E_a,
	E_b
}; // not abstract

struct I { // not abstract
	void f();
};

struct J { // abstract
	virtual void f() = 0;
	virtual void g() = 0;
};

struct K : J { // abstract
	void f() {}
};

struct L : K { // not abstract
	void g() {}
};

struct M { // not abstract
	M() {}
};

struct N { // not abstract
	virtual void f() {}
};

struct O : virtual N {}; // not abstract

struct P : virtual N {}; // not abstract

struct Q : O, P {}; // not abstract

struct R { // abstract
	virtual void f() = 0;
};

struct S : virtual R { // abstract
	void f() {}
};

struct T : virtual R {}; // abstract

struct Uu : S, T {}; // abstract

struct V { // not abstract
	int i;
};

struct W { // abstract
	virtual int f() = 0;
};

template <typename>
struct AbstractTemplate {
	virtual void f() = 0;
	// typedef int type;
};

struct Incomplete;

#if __cplusplus >= 201102L
#	define TRY(T, SHOW)                                                      \
		do {                                                                  \
			if (SHOW                                                          \
			    || ft::is_abstract<T>::value != std::is_abstract<T>::value) { \
				std::cout << "ft:  " << ft::is_abstract<T>::value             \
				          << " (is_abstract<" #T ">)" << '\n'                 \
				          << "std: " << std::is_abstract<T>::value            \
				          << " (is_abstract<" #T ">)" << "\n\n";              \
			}                                                                 \
		} while (0);
#else
#	define TRY(T, SHOW)                                          \
		do {                                                      \
			if (SHOW) {                                           \
				std::cout << "ft:  " << ft::is_abstract<T>::value \
				          << " (is_abstract<" #T ">)" << '\n';    \
			}                                                     \
			else {                                                \
				(void)ft::is_abstract<T>::value;                  \
			}                                                     \
		} while (0);
#endif

int main()
{
	// std::cout << std::boolalpha;

	std::cout << "--- Classes ---\n";
	TRY(A, false)
	TRY(B, false)
	TRY(C, false)
	TRY(D, false)
	TRY(E, false)
	TRY(F, false)
	TRY(G, false)
	TRY(H, false)
	TRY(I, false)
	TRY(J, false)
	TRY(K, false)
	TRY(L, false)
	TRY(M, false)
	TRY(N, false)
	TRY(O, false)
	TRY(P, false)
	TRY(Q, false)
	TRY(R, false)
	TRY(S, false)
	TRY(T, false)
	TRY(Uu, false)
	TRY(V, false)
	TRY(W, false)

	std::cout << "\n--- Non-classes ---\n";
	TRY(int, false)
	TRY(float, false)
	TRY(void, false)
	TRY(int*, false)
	TRY(const int, false)
	TRY(int&, false)
	TRY(int[3], false)
	TRY(int[], false)
	TRY(const int[], false)
	TRY(volatile int[], false)
	TRY(const volatile int[], false)
	TRY(int[4][2], false)
	TRY(int (&)[3], false)
	TRY(const int (&)[3], false)
	TRY(volatile int (&)[3], false)
	TRY(const volatile int (&)[3], false)
	TRY(U, false)
	TRY(E_, false)
	TRY(void(), false)
	TRY(int() const, false)
	TRY(int(*)(), false)

	std::cout << "\n--- Pointer/Reference to classes ---\n";
	TRY(A*, false)
	TRY(C*, false)
	TRY(A&, false)
	TRY(C&, false)
	TRY(const A, false)
	TRY(const C, false)
	TRY(const A*, false)
	TRY(const C*, false)
	TRY(const A&, false)
	TRY(const C&, false)
	TRY(volatile A, false)
	TRY(volatile C, false)
	TRY(volatile A*, false)
	TRY(volatile C*, false)
	TRY(volatile A&, false)
	TRY(volatile C&, false)
	TRY(const volatile A, false)
	TRY(const volatile C, false)
	TRY(const volatile A*, false)
	TRY(const volatile C*, false)
	TRY(const volatile A&, false)
	TRY(const volatile C&, false)

	std::cout << "\n--- Template classes ---\n";
	TRY(std::basic_ostream<char>, false)
	TRY(AbstractTemplate<int>, false)
	// TRY(Incomplete, false)

	// C (*ptr)[2] = NULL;
	const bool &b1 = ft::is_const<int>::value;
	const bool &b2 = ft::bool_constant<false>::value;
	const bool &b3 = ft::bool_constant<true>::value;
	std::cout << b1 << b2 << b3 << '\n';
	int arr[ft::is_const<const int>::value];
	// const bool &b2 = ft::_is_abstract::Impl<C>::value;
	std::cout << (ft::integral_constant<std::size_t, INT_MAX>::value + ft::integral_constant<std::size_t, INT_MAX>::value) << '\n';
}

// NOLINTEND
