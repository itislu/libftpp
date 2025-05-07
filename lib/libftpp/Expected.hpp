#pragma once

#include "SafeBool.hpp"
#include <exception>

namespace ft {

template <typename E>
class Unexpected;
template <typename E>
class BadExpectedAccess;
struct unexpect_t;

/**
 * https://en.cppreference.com/w/cpp/utility/expected
 */
template <typename T, typename E>
class Expected : public ft::SafeBool<Expected<T, E> > {
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

	template <typename F>
	Expected and_then(const F& f) const;
	template <typename F>
	Expected transform(const F& f) const;
	template <typename F>
	Expected or_else(const F& f) const;
	template <typename F>
	Expected transform_error(const F& f) const;

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

/**
 * https://en.cppreference.com/w/cpp/utility/expected
 */
template <typename E>
class Expected<void, E> : public ft::SafeBool<Expected<void, E> > {
public:
	Expected() throw();
	Expected(const Expected& other);
	template <typename U, typename G>
	Expected(const Expected<U, G>& other);
	template <typename G>
	Expected(const Unexpected<G>& unex);
	explicit Expected(unexpect_t /*unused*/);
	~Expected();
	Expected& operator=(Expected other) throw();

	void operator*() const throw();
	bool boolean_test() const throw();
	bool has_value() const throw();
	void value() const;
	const E& error() const throw();
	E& error() throw();
	template <typename G>
	E error_or(const G& default_value) const;

	template <typename F>
	Expected and_then(const F& f) const;
	template <typename F>
	Expected transform(const F& f) const;
	template <typename F>
	Expected or_else(const F& f) const;
	template <typename F>
	Expected transform_error(const F& f) const;

	void swap(Expected& other) throw();

private:
	E* _error;
	bool _has_value;
};

template <typename E, typename T2, typename E2>
bool operator==(const Expected<void, E>& lhs, const Expected<T2, E2>& rhs);
template <typename E>
class BadExpectedAccess;

// NOLINTBEGIN(cppcoreguidelines-virtual-class-destructor)
/**
 * https://en.cppreference.com/w/cpp/utility/expected/bad_expected_access
 */
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

/**
 * https://en.cppreference.com/w/cpp/utility/expected/unexpected
 */
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

/**
 * https://en.cppreference.com/w/cpp/utility/expected/bad_expected_access
 */
template <typename E>
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

/**
 * https://en.cppreference.com/w/cpp/utility/expected/unexpect_t
 */
struct unexpect_t {
	explicit unexpect_t(int /*unused*/) throw();
};

/**
 * https://en.cppreference.com/w/cpp/utility/expected/unexpect_t
 */
extern const unexpect_t unexpect;

} // namespace ft

#include "src/Expected/BadExpectedAccess.tpp" // IWYU pragma: export
#include "src/Expected/Expected.tpp"          // IWYU pragma: export
#include "src/Expected/Expected_void.tpp"     // IWYU pragma: export
#include "src/Expected/Unexpected.tpp"        // IWYU pragma: export
