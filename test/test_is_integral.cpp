#include "Expected.hpp"
#include "Optional.hpp"
#include "numeric.hpp"
#include "string.hpp"
#include "type_traits.hpp"
#include <iostream>
#include <limits>
#include <string>
#if __cplusplus >= 201103L
#	include <type_traits>
#endif
#if __cplusplus >= 201703L
#	include <optional>
#endif

namespace detail {
// We use two types with different sizes to distinguish which
// function overload was selected by the compiler.
typedef char yes_type;
struct no_type {
	char dummy[2];
};

// This helper function is declared but not defined.
// It's used inside an unevaluated `sizeof` expression to get a value of type T.
template <typename T>
T make_T();

// The SFINAE test functions
template <typename T>
static yes_type test(
    // Trick 1: "T* p" excludes reference types.
    // If T is a reference (e.g., int&), then T* becomes int&* which is an
    // invalid type. SFINAE removes this overload from consideration.
    T*,

    // This is an unnamed function pointer. Its type depends on a `sizeof`
    // expression. If the expression is ill-formed, the type is invalid,
    // and SFINAE removes this overload.
    char (*)[sizeof(
        // Trick 2: "reinterpret_cast<T>(t)" to exclude class types, and
        // Trick 3: "f(0)" to exclude enums.
        // In C++98, a better trick is division. Division is not defined for
        // class types (by default) or enum types, but is for integrals.
        // This replaces both tricks with a single, effective mechanism.
        make_T<T>() / 1,

        // Trick 4: "p + t" to exclude non-integral arithmetic types.
        // Pointer arithmetic is well-defined for a pointer and an integer,
        // but not for a pointer and a float/double.
        (T*)0 + make_T<T>())] = 0);

// A fallback function that matches any type, using the C-style variadic `...`
template <typename T>
static no_type test(...);

} // namespace detail

// The final is_integral struct, C++98-style (replaces std::bool_constant)
template <class T>
struct is_integral {
private:
	// First, remove any const/volatile qualifiers from T.
	typedef typename ft::remove_cv<T>::type unqualified_T;

public:
	// The core logic:
	// We pass a null pointer of the unqualified type to our test function.
	// - If unqualified_T is integral, the first `test` overload is a perfect
	// match.
	// - Otherwise, that overload is removed by SFINAE, and the `...` fallback
	// is chosen. We check the size of the return type to see which function was
	// selected.
	static const bool value =
	    sizeof(detail::test<unqualified_T>((unqualified_T*)0))
	    == sizeof(detail::yes_type);
};

class Integer {
public:
	Integer(int value)
	    : value(value)
	{}
	operator int() const { return value; }

private:
	int value;
};

class Abstract {
public:
	virtual ~Abstract() = 0;
	virtual void f() = 0;
};

class NonConstructable {
private:
	NonConstructable() {};
	NonConstructable(const NonConstructable&) {};
	~NonConstructable() {};
};

// Abstract f();

template <typename T>
REQUIRES_CONDITION(ft::is_integral<T>::value) // clang-format break
(T) test_requires(T x, T y)
{
	return x + y;
}

template <typename T,
          typename = typename ft::enable_if<ft::is_integral<T>::value>::type>
struct MustBeIntegral {
	T value;
};

#if __cplusplus >= 201703L
std::optional<int&> test_optional();
#endif

ft::Expected<int&, int> test_expected();

// MustBeIntegral<int&> test_must_be_integral();

template <typename T = void>
struct Default {};

template <int N>
struct is_large_enough {
	static const int value = N; // value is an integer (0 or 1)
};

ft::return_type<int((long))>::type r1;
// ft::return_type<int((long, char))>::type r2;
ft::parameter_type<int((long))>::type p1;
ft::parameter_type<int((long, char))>::type p2;

template <typename T, int N>
FT_REQUIRES((ft::is_integral<T>::value &&
            ft::negation<ft::is_same<T, int> >::value &&
            ft::bool_constant<(N > 0)>::value))
((ft::Expected<T, int>)) static test2(T x)
{
	return x;
}

template <typename T>
T calc(T x, T y)
{
	return x - y;
}

int main()
{
	// std::cout << std::numeric_limits<int ()>::is_specialized << '\n';
	// std::cout << std::numeric_limits<int ()>::is_integer << '\n';

	std::cout << "std::numeric_limits<Integer>::is_specialized = "
	          << std::numeric_limits<Integer>::is_specialized << '\n'; // 0

	std::cout << "ft::is_integral<Integer>::value = "
	          << ft::is_integral<Integer>::value << '\n'; // 0
	std::cout << "ft::is_integral<Integer>::value = "
	          << ft::is_integral<Integer>::value << '\n'; // 0
	std::cout << "is_integral<Integer>::value = " << is_integral<Integer>::value
	          << '\n'; // 0
	std::cout << '\n';
	std::cout << "ft::is_integral<int[1]>::value = "
	          << ft::is_integral<int[1]>::value << '\n'; // 0
	std::cout << "ft::is_integral<int[1]>::value = "
	          << ft::is_integral<int[1]>::value << '\n'; // 0
	std::cout << '\n';
	std::cout << "ft::is_integral<Abstract>::value = "
	          << ft::is_integral<Abstract>::value << '\n'; // 0
	std::cout << "ft::is_integral<Abstract>::value = "
	          << ft::is_integral<Abstract>::value << '\n'; // 0

	std::cout << ft::is_returnable<Abstract>::value << '\n';
	std::cout << ft::is_returnable<NonConstructable>::value << '\n';
	// std::cout << std::numeric_limits<Abstract>::is_integer << '\n';

	// ft::from_string<bool>("1");

	// // ft::numeric_cast<Integer&>(42);

	// // ft::add_sat("Integer", "3");
	ft::add_sat(1, 2);
	// test_requires(0, 1);
	// // test_requires("0", "1");

	// ft::Expected<int, int> e;

	// // std::optional<int&> opt;

	// // MustBeIntegral<int[1]> mbi;

	// ft::mul_sat("1", "2");

	// Default<> d;

	std::cout << test2<long, 42>(2).value() << '\n';

	std::cout << ft::numeric_cast<char>(64) << '\n';
}
