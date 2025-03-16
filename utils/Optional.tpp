// NOLINTBEGIN(cppcoreguidelines-pro-type-union-access)

#pragma once

#include "Optional.hpp"
#include "common.hpp"
#include <cstddef>

namespace utils {

template <typename T>
Optional<T>::Optional() throw()
    : _value(NULL),
      _has_value(false)
{}

template <typename T>
Optional<T>::Optional(nullopt_t /*unused*/) throw()
    : _value(NULL),
      _has_value(false)
{}

template <typename T>
Optional<T>::Optional(const Optional& other)
    : _value(other._has_value ? new T(*other._value) : NULL),
      _has_value(other._has_value)
{}

template <typename T>
template <typename U>
Optional<T>::Optional(const Optional<U>& other)
    : _value(other.has_value() ? new T(*other) : NULL),
      _has_value(other.has_value())
{}

template <typename T>
template <typename U>
Optional<T>::Optional(const U& value)
    : _value(new T(static_cast<T>(value))),
      _has_value(true)
{}

template <typename T>
Optional<T>::~Optional()
{
	if (_has_value) {
		delete _value;
	}
}

template <typename T>
Optional<T>& Optional<T>::operator=(nullopt_t /*unused*/) throw()
{
	reset();
	return *this;
}

template <typename T>
Optional<T>& Optional<T>::operator=(Optional other)
{
	swap(other);
	return *this;
}

template <typename T>
const T* Optional<T>::operator->() const throw()
{
	return _value;
}

template <typename T>
T* Optional<T>::operator->() throw()
{
	return _value;
}

template <typename T>
const T& Optional<T>::operator*() const throw()
{
	return *_value;
}

template <typename T>
T& Optional<T>::operator*() throw()
{
	return *_value;
}

template <typename T>
Optional<T>::operator bool() const throw()
{
	return _has_value;
}

template <typename T>
bool Optional<T>::has_value() const throw()
{
	return _has_value;
}

template <typename T>
const T& Optional<T>::value() const
{
	if (_has_value) {
		return *_value;
	}
	throw BadOptionalAccess();
}

template <typename T>
T& Optional<T>::value()
{
	if (_has_value) {
		return *_value;
	}
	throw BadOptionalAccess();
}

template <typename T>
T Optional<T>::value_or(const T& default_value) const
{
	if (_has_value) {
		return *_value;
	}
	return default_value;
}

template <typename T>
T& Optional<T>::value_or(T& default_value)
{
	if (_has_value) {
		return *_value;
	}
	return default_value;
}

template <typename T>
void Optional<T>::swap(Optional& other)
{
	if (_has_value && other._has_value) {
		utils::swap(_value, other._value);
	}
	else if (_has_value) {
		other._value = new T(*_value);
		other._has_value = true;
		reset();
	}
	else if (other._has_value) {
		_value = new T(*other._value);
		_has_value = true;
		other.reset();
	}
}

template <typename T>
void Optional<T>::reset() throw()
{
	if (_has_value) {
		delete _value;
		_value = NULL;
		_has_value = false;
	}
}

template <typename T>
Optional<T> make_optional(const T& value)
{
	return Optional<T>(value);
}

template <typename T>
void swap(Optional<T>& a, Optional<T>& b)
{
	a.swap(b);
}

template <typename T, typename U>
bool operator==(const Optional<T>& lhs, const Optional<U>& rhs)
{
	if (lhs.has_value() != rhs.has_value()) {
		return false;
	}
	if (!lhs.has_value()) {
		return true;
	}
	return *lhs == *rhs;
}

template <typename T, typename U>
bool operator!=(const Optional<T>& lhs, const Optional<U>& rhs)
{
	return !(lhs == rhs);
}

template <typename T, typename U>
bool operator<(const Optional<T>& lhs, const Optional<U>& rhs)
{
	if (!rhs.has_value()) {
		return false;
	}
	if (!lhs.has_value()) {
		return true;
	}
	return *lhs < *rhs;
}

template <typename T, typename U>
bool operator<=(const Optional<T>& lhs, const Optional<U>& rhs)
{
	return !(lhs > rhs);
}

template <typename T, typename U>
bool operator>(const Optional<T>& lhs, const Optional<U>& rhs)
{
	return rhs < lhs;
}

template <typename T, typename U>
bool operator>=(const Optional<T>& lhs, const Optional<U>& rhs)
{
	return !(lhs < rhs);
}

template <class T>
bool operator==(const Optional<T>& opt, nullopt_t /*unused*/) throw()
{
	return !opt.has_value();
}

template <class T>
bool operator==(nullopt_t /*unused*/, const Optional<T>& opt) throw()
{
	return opt == nullopt;
}

template <class T>
bool operator!=(const Optional<T>& opt, nullopt_t /*unused*/) throw()
{
	return !(opt == nullopt);
}

template <class T>
bool operator!=(nullopt_t /*unused*/, const Optional<T>& opt) throw()
{
	return !(opt == nullopt);
}

template <class T>
bool operator<(const Optional<T>& /*opt*/, nullopt_t /*unused*/) throw()
{
	return false;
}

template <class T>
bool operator<(nullopt_t /*unused*/, const Optional<T>& opt) throw()
{
	return opt.has_value();
}

template <class T>
bool operator<=(const Optional<T>& opt, nullopt_t /*unused*/) throw()
{
	return !(opt > nullopt);
}

template <class T>
bool operator<=(nullopt_t /*unused*/, const Optional<T>& opt) throw()
{
	return !(nullopt > opt);
}

template <class T>
bool operator>(const Optional<T>& opt, nullopt_t /*unused*/) throw()
{
	return nullopt < opt;
}

template <class T>
bool operator>(nullopt_t /*unused*/, const Optional<T>& opt) throw()
{
	return opt < nullopt;
}

template <class T>
bool operator>=(const Optional<T>& opt, nullopt_t /*unused*/) throw()
{
	return !(opt < nullopt);
}

template <class T>
bool operator>=(nullopt_t /*unused*/, const Optional<T>& opt) throw()
{
	return !(nullopt < opt);
}

template <typename T, typename U>
bool operator==(const Optional<T>& opt, const U& value)
{
	return opt.has_value() && *opt == value;
}

template <typename U, typename T>
bool operator==(const U& value, const Optional<T>& opt)
{
	return opt == value;
}

template <typename T, typename U>
bool operator!=(const Optional<T>& opt, const U& value)
{
	return !(opt == value);
}

template <typename U, typename T>
bool operator!=(const U& value, const Optional<T>& opt)
{
	return !(opt == value);
}

template <typename T, typename U>
bool operator<(const Optional<T>& opt, const U& value)
{
	return !opt.has_value() || *opt < value;
}

template <typename U, typename T>
bool operator<(const U& value, const Optional<T>& opt)
{
	return opt.has_value() && value < *opt;
}

template <typename T, typename U>
bool operator<=(const Optional<T>& opt, const U& value)
{
	return !(opt > value);
}

template <typename U, typename T>
bool operator<=(const U& value, const Optional<T>& opt)
{
	return !(value > opt);
}

template <typename T, typename U>
bool operator>(const Optional<T>& opt, const U& value)
{
	return value < opt;
}

template <typename U, typename T>
bool operator>(const U& value, const Optional<T>& opt)
{
	return opt < value;
}

template <typename T, typename U>
bool operator>=(const Optional<T>& opt, const U& value)
{
	return !(opt < value);
}

template <typename U, typename T>
bool operator>=(const U& value, const Optional<T>& opt)
{
	return !(value < opt);
}

} // namespace utils

// NOLINTEND(cppcoreguidelines-pro-type-union-access)
