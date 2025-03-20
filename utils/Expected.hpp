#pragma once

#include "SafeBool.hpp"
#include <exception>

namespace utils {

template <class E>
class BadExpectedAccess;

// NOLINTBEGIN(cppcoreguidelines-virtual-class-destructor)
template <>
class BadExpectedAccess<void> : public std::exception {
public:
	const char* what() const throw();

protected:
	BadExpectedAccess() throw();
	BadExpectedAccess(const BadExpectedAccess& /*unused*/);
	~BadExpectedAccess() throw();
	BadExpectedAccess& operator=(const BadExpectedAccess& /*unused*/);
};
// NOLINTEND(cppcoreguidelines-virtual-class-destructor)

template <class E>
class BadExpectedAccess : public BadExpectedAccess<void> {
public:
	explicit BadExpectedAccess(const E& error);
	BadExpectedAccess(const BadExpectedAccess& other);
	~BadExpectedAccess() throw();
	BadExpectedAccess& operator=(const BadExpectedAccess& other);

	const E& error() const throw();
	E& error() throw();

private:
	E _error;
};

template <typename E>
class Unexpected {
public:
	Unexpected(const Unexpected& other);
	template <typename Err>
	explicit Unexpected(const Err& error);
	~Unexpected();

	Unexpected& operator=(Unexpected other);

	const E& error() const throw();
	E& error() throw();

	void swap(Unexpected& other);

private:
	Unexpected();

	E _error;
};

template <typename E>
void swap(Unexpected<E>& lhs, Unexpected<E>& rhs);

template <typename E, typename E2>
bool operator==(const Unexpected<E>& lhs, const Unexpected<E2>& rhs);
template <typename E, typename E2>
bool operator!=(const Unexpected<E>& lhs, const Unexpected<E2>& rhs);

struct unexpect_t {
	explicit unexpect_t(int /*unused*/) throw();
};

extern const unexpect_t unexpect;

template <typename T, typename E>
class Expected : public SafeBool<Expected<T, E> > {
public:
	Expected();
	Expected(const Expected& other);
	template <typename U, typename G>
	Expected(const Expected<U, G>& other);
	template <typename U>
	Expected(const U& value);
	template <typename G>
	Expected(const Unexpected<G>& unex);
	explicit Expected(unexpect_t /*unused*/);
	~Expected();

	Expected& operator=(Expected other) throw();

	const T* operator->() const throw();
	T* operator->() throw();
	const T& operator*() const throw();
	T& operator*() throw();
	bool boolean_test() const throw();
	bool has_value() const throw();
	const T& value() const;
	T& value();
	const E& error() const throw();
	E& error() throw();
	template <typename U>
	T value_or(const U& default_value) const;
	template <typename G>
	E error_or(const G& default_value) const;

	void swap(Expected& other) throw();

private:
	union {
		T* _value;
		E* _error;
	};
	bool _has_value;
};

template <typename T, typename E>
void swap(Expected<T, E>& lhs, Expected<T, E>& rhs) throw();

template <typename T, typename E, typename T2, typename E2>
bool operator==(const Expected<T, E>& lhs, const Expected<T2, E2>& rhs);
template <typename T, typename E, typename E2>
bool operator==(const Expected<T, E>& lhs, const Unexpected<E2>& unex);
template <typename T, typename E, typename T2>
bool operator==(const Expected<T, E>& lhs, const T2& value);
template <typename T, typename E, typename T2, typename E2>
bool operator!=(const Expected<T, E>& lhs, const Expected<T2, E2>& rhs);
template <typename T, typename E, typename E2>
bool operator!=(const Expected<T, E>& lhs, const Unexpected<E2>& unex);
template <typename T, typename E, typename T2>
bool operator!=(const Expected<T, E>& lhs, const T2& value);

} // namespace utils

#include "Expected.tpp" // IWYU pragma: export
