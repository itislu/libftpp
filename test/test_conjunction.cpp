#include "type_traits.hpp"
#include <iostream>
#if __cplusplus >= 201103L
#	include <type_traits>
#endif

struct Invalid {};

struct Valid {
	static const bool value = true;
};

int main()
{
	// Case 1: All true.
	std::cout << "conjunction<ft::true_type, ft::true_type>::value = "
	          << ft::conjunction<ft::true_type, ft::true_type>::value
	          << '\n'; // 1

	// Case 2: Short-circuits on the first element.
	std::cout << "conjunction<ft::false_type, Invalid >::value = "
	          << ft::conjunction<ft::false_type, Invalid>::value << '\n'; // 0
	// The above line compiles ONLY because Invalid is never
	// instantiated.

	// Case 3: Short-circuits on a middle element.
	std::cout
	    << "conjunction<ft::true_type, ft::false_type, Invalid >::value = "
	    << ft::conjunction<ft::true_type,
	                       ft::false_type,
	                       Invalid>::value
	    << '\n'; // 0

	// Case 4: A valid use case that passes.
	std::cout << "conjunction<ft::true_type, Valid >::value = "
	          << ft::conjunction<ft::true_type, Valid>::value << '\n'; // 1

	// Case 5: Empty ft::conjunction is true.
	std::cout << "conjunction<>::value = " << ft::conjunction<>::value
	          << '\n'; // 1

	// This line would cause a hard compile error, demonstrating the problem
	// that conjunction solves.
	// bool error = true && Invalid::value;

	std::cout
	    << "ft::conjunction<ft::integral_constant<int, 2>, ft::integral_constant<int, 4> >::value = "
	    << ft::conjunction<ft::integral_constant<int, 2>,
	                       ft::integral_constant<int, 4> >::value
	    << '\n';

	std::cout
	    << "ft::disjunction<ft::integral_constant<int, 2>, ft::integral_constant<int, 4> >::value = "
	    << ft::disjunction<ft::integral_constant<int, 2>,
	                       ft::integral_constant<int, 4> >::value
	    << '\n';

	// std::cout << ft::conjunction<void>::value << '\n';
	// std::cout << std::conjunction<void>::value << '\n';

	return 0;
}
