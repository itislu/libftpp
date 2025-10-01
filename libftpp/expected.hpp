#pragma once

#include "libftpp/SafeBool.hpp"
#include "libftpp/assert.hpp"
#include "libftpp/type_traits.hpp"
#include <exception>

namespace ft {

template <typename E>
class unexpected;
template <typename E>
class bad_expected_access;
struct unexpect_t;

namespace _unexpected {
template <typename T>
struct is_unexpected;
} // namespace _unexpected

/**
 * https://en.cppreference.com/w/cpp/utility/expected
 */
template <typename T, typename E>
class expected : public ft::SafeBool<expected<T, E> > {
private:
	STATIC_ASSERT( // T must not be an array type
	    !ft::is_array<T>::value);
	STATIC_ASSERT( // T must not be a reference type
	    !ft::is_reference<T>::value);
	STATIC_ASSERT( // T must not be a function type
	    !ft::is_function<T>::value);
	STATIC_ASSERT( // T must not be a specialization of ft::unexpected
	    !_unexpected::is_unexpected<typename ft::remove_cv<T>::type>::value);
	STATIC_ASSERT( // T must not be ft::unexpect_t
	    (!ft::is_same<typename ft::remove_cv<T>::type, ft::unexpect_t>::value));
	STATIC_ASSERT( // E must be an object type
	    ft::is_object<E>::value);
	STATIC_ASSERT( // E must not be an array type
	    !ft::is_array<E>::value);
	STATIC_ASSERT( // E must not be a specialization of ft::unexpected
	    !_unexpected::is_unexpected<typename ft::remove_cv<E>::type>::value);
	STATIC_ASSERT( // E must not be cv-qualified type
	    !ft::is_const<E>::value && !ft::is_volatile<E>::value);

public:
	expected();
	expected(const expected& other);
	template <typename U, typename G>
	expected(const expected<U, G>& other);
	template <typename U>
	expected(const U& v);
	template <typename G>
	expected(const unexpected<G>& e);
	explicit expected(unexpect_t /*unused*/);
	~expected();
	expected& operator=(expected other) throw();

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
	expected and_then(const F& f) const;
	template <typename F>
	expected transform(const F& f) const;
	template <typename F>
	expected or_else(const F& f) const;
	template <typename F>
	expected transform_error(const F& f) const;

	void swap(expected& other) throw();

private:
	union {
		T* _value;
		E* _error;
	};
	bool _has_value;
};

template <typename T, typename E>
void swap(expected<T, E>& lhs, expected<T, E>& rhs) throw();

template <typename T, typename E, typename T2, typename E2>
bool operator==(const expected<T, E>& lhs, const expected<T2, E2>& rhs);
template <typename T, typename E, typename E2>
bool operator==(const expected<T, E>& lhs, const unexpected<E2>& unex);
template <typename T, typename E, typename T2>
bool operator==(const expected<T, E>& lhs, const T2& val);
template <typename T, typename E, typename T2, typename E2>
bool operator!=(const expected<T, E>& lhs, const expected<T2, E2>& rhs);
template <typename T, typename E, typename E2>
bool operator!=(const expected<T, E>& lhs, const unexpected<E2>& unex);
template <typename T, typename E, typename T2>
bool operator!=(const expected<T, E>& lhs, const T2& val);

/**
 * https://en.cppreference.com/w/cpp/utility/expected
 */
template <typename E>
class expected<void, E> : public ft::SafeBool<expected<void, E> > {
private:
	STATIC_ASSERT( // E must be an object type
	    ft::is_object<E>::value);
	STATIC_ASSERT( // E must not be an array type
	    !ft::is_array<E>::value);
	STATIC_ASSERT( // E must not be a specialization of ft::unexpected
	    !_unexpected::is_unexpected<typename ft::remove_cv<E>::type>::value);
	STATIC_ASSERT( // E must not be cv-qualified type
	    !ft::is_const<E>::value && !ft::is_volatile<E>::value);

public:
	expected() throw();
	expected(const expected& other);
	template <typename U, typename G>
	expected(const expected<U, G>& other);
	template <typename G>
	expected(const unexpected<G>& e);
	explicit expected(unexpect_t /*unused*/);
	~expected();
	expected& operator=(expected other) throw();

	void operator*() const throw();
	bool boolean_test() const throw();
	bool has_value() const throw();
	void value() const;
	const E& error() const throw();
	E& error() throw();
	template <typename G>
	E error_or(const G& default_value) const;

	template <typename F>
	expected and_then(const F& f) const;
	template <typename F>
	expected transform(const F& f) const;
	template <typename F>
	expected or_else(const F& f) const;
	template <typename F>
	expected transform_error(const F& f) const;

	void swap(expected& other) throw();

private:
	E* _error;
	bool _has_value;
};

template <typename E, typename T2, typename E2>
bool operator==(const expected<void, E>& lhs, const expected<T2, E2>& rhs);

/**
 * https://en.cppreference.com/w/cpp/utility/expected/unexpected
 */
template <typename E>
class unexpected {
private:
	STATIC_ASSERT( // E must be an object type
	    ft::is_object<E>::value);
	STATIC_ASSERT( // E must not be an array type
	    !ft::is_array<E>::value);
	STATIC_ASSERT( // E must not be a specialization of ft::unexpected
	    !_unexpected::is_unexpected<typename ft::remove_cv<E>::type>::value);
	STATIC_ASSERT( // E must not be cv-qualified type
	    !ft::is_const<E>::value && !ft::is_volatile<E>::value);

public:
	unexpected(const unexpected& other);
	template <typename Err>
	explicit unexpected(const Err& e);
	~unexpected();
	unexpected& operator=(unexpected other);

	const E& error() const throw();
	E& error() throw();

	void swap(unexpected& other);

private:
	unexpected();

	E _error;
};

template <typename E>
void swap(unexpected<E>& x, unexpected<E>& y);

template <typename E, typename E2>
bool operator==(const unexpected<E>& x, const unexpected<E2>& y);
template <typename E, typename E2>
bool operator!=(const unexpected<E>& x, const unexpected<E2>& y);

// NOLINTBEGIN(cppcoreguidelines-virtual-class-destructor)
/**
 * https://en.cppreference.com/w/cpp/utility/expected/bad_expected_access
 */
template <>
class bad_expected_access<void> : public std::exception {
public:
	const char* what() const throw();

protected:
	bad_expected_access() throw();
	bad_expected_access(const bad_expected_access& /*unused*/);
	~bad_expected_access() throw();
	bad_expected_access& operator=(const bad_expected_access& /*unused*/);
};
// NOLINTEND(cppcoreguidelines-virtual-class-destructor)

/**
 * https://en.cppreference.com/w/cpp/utility/expected/bad_expected_access
 */
template <typename E>
class bad_expected_access : public bad_expected_access<void> {
public:
	explicit bad_expected_access(const E& e);
	bad_expected_access(const bad_expected_access& other);
	~bad_expected_access() throw();
	bad_expected_access& operator=(const bad_expected_access& other);

	const E& error() const throw();
	E& error() throw();

private:
	E _error;
};

/**
 * https://en.cppreference.com/w/cpp/utility/expected/unexpect_t
 */
struct unexpect_t {
	explicit unexpect_t() throw();
};

/**
 * https://en.cppreference.com/w/cpp/utility/expected/unexpect_t
 */
extern const unexpect_t unexpect;

} // namespace ft

#include "libftpp/expected/bad_expected_access.tpp" // IWYU pragma: export
#include "libftpp/expected/expected.tpp"            // IWYU pragma: export
#include "libftpp/expected/expected_void.tpp"       // IWYU pragma: export
#include "libftpp/expected/unexpected.tpp"          // IWYU pragma: export
