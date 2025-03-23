#pragma once

#include "../../Expected.hpp"

namespace ft {

template <typename E>
BadExpectedAccess<E>::BadExpectedAccess(const E& error)
    : _error(error)
{}

template <typename E>
BadExpectedAccess<E>::BadExpectedAccess(const BadExpectedAccess& other)
    : BadExpectedAccess<void>(other),
      _error(other._error)
{}

template <typename E>
BadExpectedAccess<E>::~BadExpectedAccess() throw()
{}

template <typename E>
BadExpectedAccess<E>&
BadExpectedAccess<E>::operator=(const BadExpectedAccess& other)
{
	if (&other != this) {
		_error = other._error;
	}
	return *this;
}

template <typename E>
const E& BadExpectedAccess<E>::error() const throw()
{
	return _error;
}

template <typename E>
E& BadExpectedAccess<E>::error() throw()
{
	return _error;
}

} // namespace ft
