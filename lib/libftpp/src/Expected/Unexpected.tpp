#pragma once

#include "../../Expected.hpp"

namespace ft {

template <typename E>
Unexpected<E>::Unexpected(const Unexpected& other)
    : _error(other._error)
{}

template <typename E>
template <typename Err>
Unexpected<E>::Unexpected(const Err& error)
    : _error(error)
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
void swap(Unexpected<E>& lhs, Unexpected<E>& rhs)
{
	lhs.swap(rhs);
}

template <typename E, typename E2>
bool operator==(const Unexpected<E>& lhs, const Unexpected<E2>& rhs)
{
	return lhs.error() == rhs.error();
}

template <typename E, typename E2>
bool operator!=(const Unexpected<E>& lhs, const Unexpected<E2>& rhs)
{
	return !(lhs == rhs);
}

} // namespace ft
