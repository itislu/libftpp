// NOLINTBEGIN(cppcoreguidelines-pro-type-union-access)

#pragma once

#include "../../Expected.hpp"
#include "../../SafeBool.hpp"
#include "../../algorithm.hpp"
#include <cassert>
#include <cstddef>

namespace ft {

template <typename E>
Expected<void, E>::Expected() throw()
    : _error(NULL),
      _has_value(true)
{}

template <typename E>
Expected<void, E>::Expected(const Expected& other)
    : ft::SafeBool<Expected<void, E> >(),
      _error(other._has_value ? NULL : new E(*other._error)),
      _has_value(other._has_value)
{}

template <typename E>
template <typename U, typename G>
Expected<void, E>::Expected(const Expected<U, G>& other)
    : _error(other.has_value() ? NULL : new E(other.error())),
      _has_value(other._has_value())
{}

template <typename E>
template <typename G>
Expected<void, E>::Expected(const Unexpected<G>& unex)
    : _error(new E(unex.error())),
      _has_value(false)
{}

template <typename E>
Expected<void, E>::Expected(unexpect_t /*unused*/)
    : _error(new E()),
      _has_value(false)
{}

template <typename E>
Expected<void, E>::~Expected()
{
	delete _error;
}

template <typename E>
Expected<void, E>& Expected<void, E>::operator=(Expected other) throw()
{
	swap(other);
	return *this;
}

template <typename E>
void Expected<void, E>::operator*() const throw()
{
	assert(_has_value);
}

template <typename E>
bool Expected<void, E>::boolean_test() const throw()
{
	return _has_value;
}

template <typename E>
bool Expected<void, E>::has_value() const throw()
{
	return _has_value;
}

template <typename E>
void Expected<void, E>::value() const
{
	if (!_has_value) {
		throw BadExpectedAccess<E>(*_error);
	}
}

template <typename E>
const E& Expected<void, E>::error() const throw()
{
	assert(!_has_value);
	return *_error;
}

template <typename E>
E& Expected<void, E>::error() throw()
{
	assert(!_has_value);
	return *_error;
}

template <typename E>
template <typename G>
E Expected<void, E>::error_or(const G& default_value) const
{
	if (!_has_value) {
		return *_error;
	}
	return default_value;
}

/**
 * The monadic functions are limited in their use compared to the original ones.
 * The functions passed in the original ones can return different result or
 * error types, but in this implementation the limits of C++98 and the lack of
 * the `auto` keyword and `result_of` and `decltype` metaprogramming features
 * make it very difficult to come close to that.
 */

/**
 * f should return an Expected<void, E>
 */
template <typename E>
template <typename F>
Expected<void, E> Expected<void, E>::and_then(const F& f) const
{
	if (_has_value) {
		return f();
	}
	return *this;
}

/**
 * f should return nothing
 */
template <typename E>
template <typename F>
Expected<void, E> Expected<void, E>::transform(const F& f) const
{
	if (_has_value) {
		f();
		return Expected();
	}
	return *this;
}

/**
 * f should return an Expected<void, E>
 */
template <typename E>
template <typename F>
Expected<void, E> Expected<void, E>::or_else(const F& f) const
{
	if (!_has_value) {
		return f(*_error);
	}
	return *this;
}

/**
 * f should return an unexpected value of type E
 */
template <typename E>
template <typename F>
Expected<void, E> Expected<void, E>::transform_error(const F& f) const
{
	if (!_has_value) {
		return Expected(Unexpected<E>(f(*_error)));
	}
	return *this;
}

template <typename E>
void Expected<void, E>::swap(Expected& other) throw()
{
	ft::swap(_error, other._error);
	ft::swap(_has_value, other._has_value);
}

template <typename E, typename T2, typename E2>
bool operator==(const Expected<void, E>& lhs, const Expected<T2, E2>& rhs)
{
	if (lhs.has_value() != rhs.has_value()) {
		return false;
	}
	if (!lhs.has_value()) {
		return lhs.error() == rhs.error();
	}
	return true;
}

} // namespace ft

// NOLINTEND(cppcoreguidelines-pro-type-union-access)
