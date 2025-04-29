#pragma once

#include "../../Optional.hpp"
#include "../../SafeBool.hpp"
#include "../../algorithm.hpp"
#include <cassert>
#include <cstddef>

namespace ft {

template <typename T>
Optional<T>::Optional() throw()
    : _value(NULL)
{}

template <typename T>
Optional<T>::Optional(nullopt_t /*unused*/) throw()
    : _value(NULL)
{}

template <typename T>
Optional<T>::Optional(const Optional& other)
    : ft::SafeBool<Optional<T> >(),
      _value(other.has_value() ? new T(*other._value) : NULL)
{}

template <typename T>
template <typename U>
Optional<T>::Optional(const Optional<U>& other)
    : _value(other.has_value() ? new T(*other) : NULL)
{}

template <typename T>
template <typename U>
Optional<T>::Optional(const U& value)
    : _value(new T(value))
{}

template <typename T>
Optional<T>::~Optional()
{
	delete _value;
}

template <typename T>
Optional<T>& Optional<T>::operator=(nullopt_t /*unused*/) throw()
{
	reset();
	return *this;
}

template <typename T>
Optional<T>& Optional<T>::operator=(Optional other) throw()
{
	swap(other);
	return *this;
}

template <typename T>
const T* Optional<T>::operator->() const throw()
{
	assert(has_value());
	return _value;
}

template <typename T>
T* Optional<T>::operator->() throw()
{
	assert(has_value());
	return _value;
}

template <typename T>
const T& Optional<T>::operator*() const throw()
{
	assert(has_value());
	return *_value;
}

template <typename T>
T& Optional<T>::operator*() throw()
{
	assert(has_value());
	return *_value;
}

template <typename T>
bool Optional<T>::boolean_test() const throw()
{
	return _value != NULL;
}

template <typename T>
bool Optional<T>::has_value() const throw()
{
	return _value != NULL;
}

template <typename T>
const T& Optional<T>::value() const
{
	if (has_value()) {
		return *_value;
	}
	throw BadOptionalAccess();
}

template <typename T>
T& Optional<T>::value()
{
	if (has_value()) {
		return *_value;
	}
	throw BadOptionalAccess();
}

template <typename T>
template <typename U>
T Optional<T>::value_or(const U& default_value) const
{
	if (has_value()) {
		return *_value;
	}
	return static_cast<T>(default_value);
}

/**
 * The monadic functions are limited in their use compared to the original ones.
 * The functions passed in the original ones can return different result or
 * error types, but in this implementation the limits of C++98 and the lack of
 * the `auto` keyword and `result_of` and `decltype` metaprogramming features
 * make it very difficult to come close to that.
 */

/**
 * f should return an Optional<T>
 */
template <typename T>
template <typename F>
Optional<T> Optional<T>::and_then(const F& f) const
{
	if (has_value()) {
		return f(*_value);
	}
	return Optional();
}

/**
 * f should return a value of type T
 */
template <typename T>
template <typename F>
Optional<T> Optional<T>::transform(const F& f) const
{
	if (has_value()) {
		return Optional(f(*_value));
	}
	return Optional();
}

/**
 * f should return an Optional<T>
 */
template <typename T>
template <typename F>
Optional<T> Optional<T>::or_else(const F& f) const
{
	if (!has_value()) {
		return f();
	}
	return *this;
}

template <typename T>
void Optional<T>::swap(Optional& other) throw()
{
	ft::swap(_value, other._value);
}

template <typename T>
void Optional<T>::reset() throw()
{
	if (has_value()) {
		delete _value;
		_value = NULL;
	}
}

template <typename T>
Optional<T> make_optional(const T& value)
{
	return Optional<T>(value);
}

template <typename T>
void swap(Optional<T>& lhs, Optional<T>& rhs) throw()
{
	lhs.swap(rhs);
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

template <typename T>
bool operator==(const Optional<T>& opt, nullopt_t /*unused*/) throw()
{
	return !opt.has_value();
}

template <typename T>
bool operator==(nullopt_t /*unused*/, const Optional<T>& opt) throw()
{
	return opt == nullopt;
}

template <typename T>
bool operator!=(const Optional<T>& opt, nullopt_t /*unused*/) throw()
{
	return !(opt == nullopt);
}

template <typename T>
bool operator!=(nullopt_t /*unused*/, const Optional<T>& opt) throw()
{
	return !(opt == nullopt);
}

template <typename T>
bool operator<(const Optional<T>& /*opt*/, nullopt_t /*unused*/) throw()
{
	return false;
}

template <typename T>
bool operator<(nullopt_t /*unused*/, const Optional<T>& opt) throw()
{
	return opt.has_value();
}

template <typename T>
bool operator<=(const Optional<T>& opt, nullopt_t /*unused*/) throw()
{
	return !(opt > nullopt);
}

template <typename T>
bool operator<=(nullopt_t /*unused*/, const Optional<T>& opt) throw()
{
	return !(nullopt > opt);
}

template <typename T>
bool operator>(const Optional<T>& opt, nullopt_t /*unused*/) throw()
{
	return nullopt < opt;
}

template <typename T>
bool operator>(nullopt_t /*unused*/, const Optional<T>& opt) throw()
{
	return opt < nullopt;
}

template <typename T>
bool operator>=(const Optional<T>& opt, nullopt_t /*unused*/) throw()
{
	return !(opt < nullopt);
}

template <typename T>
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

} // namespace ft
