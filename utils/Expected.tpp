// NOLINTBEGIN(cppcoreguidelines-pro-type-union-access)

#pragma once

#include "Expected.hpp"
#include "SafeBool.hpp"
#include "common.hpp"
#include <cassert>

namespace utils {

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
	utils::swap(_error, other._error);
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

template <typename T, typename E>
Expected<T, E>::Expected()
    : _value(new T()),
      _has_value(true)
{}

template <typename T, typename E>
Expected<T, E>::Expected(const Expected& other)
    : utils::SafeBool<Expected<T, E> >(),
      _has_value(false)
{
	if (other._has_value) {
		_value = new T(*other._value);
		_has_value = true;
	}
	else {
		_error = new E(*other._error);
	}
}

template <typename T, typename E>
template <typename U, typename G>
Expected<T, E>::Expected(const Expected<U, G>& other)
    : _has_value(false)
{
	if (other.has_value()) {
		_value = new T(*other);
		_has_value = true;
	}
	else {
		_error = new E(other.error());
	}
}

template <typename T, typename E>
template <typename U>
Expected<T, E>::Expected(const U& value)
    : _value(new T(value)),
      _has_value(true)
{}

template <typename T, typename E>
template <typename G>
Expected<T, E>::Expected(const Unexpected<G>& unex)
    : _error(new E(unex.error())),
      _has_value(false)
{}

template <typename T, typename E>
Expected<T, E>::Expected(unexpect_t /*unused*/)
    : _error(new E()),
      _has_value(false)
{}

template <typename T, typename E>
Expected<T, E>::~Expected()
{
	if (_has_value) {
		delete _value;
	}
	else {
		delete _error;
	}
}

template <typename T, typename E>
Expected<T, E>& Expected<T, E>::operator=(Expected other) throw()
{
	swap(other);
	return *this;
}

template <typename T, typename E>
const T* Expected<T, E>::operator->() const throw()
{
	assert(_has_value);
	return _value;
}

template <typename T, typename E>
T* Expected<T, E>::operator->() throw()
{
	assert(_has_value);
	return _value;
}

template <typename T, typename E>
const T& Expected<T, E>::operator*() const throw()
{
	assert(_has_value);
	return *_value;
}

template <typename T, typename E>
T& Expected<T, E>::operator*() throw()
{
	assert(_has_value);
	return *_value;
}

template <typename T, typename E>
bool Expected<T, E>::boolean_test() const throw()
{
	return _has_value;
}

template <typename T, typename E>
bool Expected<T, E>::has_value() const throw()
{
	return _has_value;
}

template <typename T, typename E>
const T& Expected<T, E>::value() const
{
	if (!_has_value) {
		throw BadExpectedAccess<E>(*_error);
	}
	return *_value;
}

template <typename T, typename E>
T& Expected<T, E>::value()
{
	if (!_has_value) {
		throw BadExpectedAccess<E>(*_error);
	}
	return *_value;
}

template <typename T, typename E>
const E& Expected<T, E>::error() const throw()
{
	assert(!_has_value);
	return *_error;
}

template <typename T, typename E>
E& Expected<T, E>::error() throw()
{
	assert(!_has_value);
	return *_error;
}

template <typename T, typename E>
template <typename U>
T Expected<T, E>::value_or(const U& default_value) const
{
	if (_has_value) {
		return *_value;
	}
	return static_cast<T>(default_value);
}

template <typename T, typename E>
template <typename G>
E Expected<T, E>::error_or(const G& default_value) const
{
	if (!_has_value) {
		return *_error;
	}
	return default_value;
}

template <typename T, typename E>
void Expected<T, E>::swap(Expected& other) throw()
{
	if (_has_value && other._has_value) {
		utils::swap(_value, other._value);
	}
	else if (_has_value) {
		T* tmp = _value;
		_error = other._error;
		_has_value = false;
		other._value = tmp;
		other._has_value = true;
	}
	else if (other._has_value) {
		T* tmp = other._value;
		other._error = _error;
		other._has_value = false;
		_value = tmp;
		_has_value = true;
	}
	else {
		utils::swap(_error, other._error);
	}
}

template <typename T, typename E>
void swap(Expected<T, E>& lhs, Expected<T, E>& rhs) throw()
{
	lhs.swap(rhs);
}

template <typename T, typename E, typename T2, typename E2>
bool operator==(const Expected<T, E>& lhs, const Expected<T2, E2>& rhs)
{
	if (lhs.has_value() != rhs.has_value()) {
		return false;
	}
	if (!lhs.has_value()) {
		return lhs.error() == rhs.error();
	}
	return *lhs == *rhs;
}

template <typename T, typename E, typename E2>
bool operator==(const Expected<T, E>& lhs, const Unexpected<E2>& unex)
{
	return (!lhs.has_value() && lhs.error() == unex.error());
}

template <typename T, typename E, typename T2>
bool operator==(const Expected<T, E>& lhs, const T2& value)
{
	return (lhs.has_value() && *lhs == value);
}

template <typename T, typename E, typename T2, typename E2>
bool operator!=(const Expected<T, E>& lhs, const Expected<T2, E2>& rhs)
{
	return !(lhs == rhs);
}

template <typename T, typename E, typename E2>
bool operator!=(const Expected<T, E>& lhs, const Unexpected<E2>& unex)
{
	return !(lhs == unex);
}

template <typename T, typename E, typename T2>
bool operator!=(const Expected<T, E>& lhs, const T2& value)
{
	return !(lhs == value);
}

} // namespace utils

// NOLINTEND(cppcoreguidelines-pro-type-union-access)
