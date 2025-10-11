// #include "string.hpp"
// #include "string.tpp"
// #include <cctype>
// #include <cmath>
// #include <iostream>
// #include <iterator>
// #include <string>

// class A {
// public:
// 	A()
// 	    : i(42)
// 	{}

// 	int i;
// };

// std::ostream& operator<<(std::ostream& os, A a)
// {
// 	os << a.i;
// 	return os;
// }

// std::istream& operator>>(std::istream& is, A& a)
// {
// 	is >> a.i;
// 	return is;
// }

// int main()
// {
// 	// float f = NAN;
// 	// std::cout << std::isnan(-f) << '\n';

// 	// std::cout << std::stof("1111111111111111111111111111111111111111") <<
// 	// '\n';

// 	// A a = ft::from_string<A>("   123asdf1");

// 	std::cout << "|" << ft::from_string<char>("48") << "|" << '\n';

// 	// ft::_detail::from_string_floating_point<float>("");
// 	std::cout << ft::to_string(A()) << '\n';

// 	std::cout << ft::from_string<A>("   123asdf1") << '\n';
// 	std::cout << ft::from_string<double>("   123asdf1") << '\n';
// 	std::cout << ft::from_string<long double>("   123asdf1") << '\n';
// 	std::cout << ft::from_string<int>("   123asdf1") << '\n';
// 	std::cout << ft::from_string<bool>("   2") << '\n';

// 	// std::cout << ft::transform("hello world", toupper) << '\n';

// 	std::string in("hello world");
// 	std::string out;
// 	// out.resize(in.length());
// 	ft::transform(
// 	    in.begin(), in.end(), std::inserter(out, out.begin()), toupper);
// 	std::cout << out << '\n';
// }
