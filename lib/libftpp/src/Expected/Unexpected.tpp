#pragma once

#include "../../Expected.hpp"

namespace ft {

template <typename E>
Unexpected<E>::Unexpected(const Unexpected& other)
    : _error(other._error)
{}

template <typename E>
template <typename Err>
Unexpected<E>::Unexpected(const Err& e)
    : _error(e)
{}

template <typename E>
Unexpected<E>::~Unexpected()
{}

template <typename E>
Unexpected<E>& Unexpected<E>::operator=(Unexpected other)
{
	swap(other);
	return *this;
}

template <typename E>
const E& Unexpected<E>::error() const throw()
{
	return _error;
}

template <typename E>
E& Unexpected<E>::error() throw()
{
	return _error;
}

template <typename E>
void Unexpected<E>::swap(Unexpected& other)
{
	ft::swap(_error, other._error);
}

template <typename E>
void swap(Unexpected<E>& x, Unexpected<E>& y)
{
	x.swap(y);
}

template <typename E, typename E2>
bool operator==(const Unexpected<E>& x, const Unexpected<E2>& y)
{
	return x.error() == y.error();
}

template <typename E, typename E2>
bool operator!=(const Unexpected<E>& x, const Unexpected<E2>& y)
{
	return !(x == y);
}

namespace _unexpected {

template <typename>
struct is_unexpected {
	enum {
		value = false
	};
};

template <typename T>
struct is_unexpected<Unexpected<T> > {
	enum {
		value = true
	};
};

} // namespace _unexpected

} // namespace ft
