#include "libftpp/numeric.hpp"

namespace ft {

namespace _abs_diff {
template <typename U, typename I>
static U abs_diff(I a, I b) throw();
} // namespace _abs_diff

unsigned char abs_diff(char a, char b) throw()
{
	return _abs_diff::abs_diff<unsigned char>(a, b);
}

unsigned char abs_diff(signed char a, signed char b) throw()
{
	return _abs_diff::abs_diff<unsigned char>(a, b);
}

unsigned short abs_diff(short a, short b) throw()
{
	return _abs_diff::abs_diff<unsigned short>(a, b);
}

unsigned int abs_diff(int a, int b) throw()
{
	return _abs_diff::abs_diff<unsigned int>(a, b);
}

unsigned long abs_diff(long a, long b) throw()
{
	return _abs_diff::abs_diff<unsigned long>(a, b);
}

namespace _abs_diff {

template <typename U, typename I>
static U abs_diff(I a, I b) throw()
{
	return a > b ? static_cast<U>(a) - static_cast<U>(b)
	             : static_cast<U>(b) - static_cast<U>(a);
}

} // namespace _abs_diff

} // namespace ft
