#pragma once
#ifndef LIBFTPP_MEMORY_HPP
#	define LIBFTPP_MEMORY_HPP

#	include "libftpp/assert.hpp"
#	include "libftpp/memory/shared_ptr_detail.hpp"
#	include "libftpp/memory/unique_ptr_detail.hpp"
#	include "libftpp/movable.hpp"
#	include "libftpp/safe_bool.hpp"
#	include "libftpp/type_traits.hpp"
#	include "libftpp/utility.hpp"
#	include <cstddef>
#	include <memory>
#	include <ostream>
#	include <typeinfo>

namespace ft {

/* default_delete */

/**
 * https://en.cppreference.com/w/cpp/memory/default_delete
 */
template <typename T>
struct default_delete {
private:
	struct _enabler {};

public:
	default_delete() throw();
	// NOLINTBEGIN(google-explicit-constructor): Original in
	// `std::default_delete` is not `explicit`.
	template <typename U>
	default_delete(const default_delete<U>& d,
	               typename ft::enable_if<ft::is_convertible<U*, T*>::value,
	                                      _enabler>::type /*unused*/
	               = _enabler()) throw();
	// NOLINTEND(google-explicit-constructor)

	void operator()(T* ptr) const;
};

/**
 * https://en.cppreference.com/w/cpp/memory/default_delete
 */
template <typename T>
struct default_delete<T[]> {
private:
	struct _enabler {};

public:
	default_delete() throw();
	// NOLINTBEGIN(google-explicit-constructor): Original in
	// `std::default_delete` is not `explicit`.
	template <typename U>
	default_delete(
	    const default_delete<U[]>& d,
	    typename ft::enable_if<ft::is_convertible<U (*)[], T (*)[]>::value,
	                           _enabler>::type /*unused*/
	    = _enabler()) throw();
	// NOLINTEND(google-explicit-constructor)

	template <typename U>
	FT_REQUIRES((ft::is_convertible<U (*)[], T (*)[]>::value))
	(void)operator()(U * ptr) const;
};

/* shared_ptr */

class bad_weak_ptr : public std::exception {
public:
	const char* what() const throw();
};

template <typename T>
class shared_ptr;

template <typename T>
class weak_ptr;

template <typename T>
class enable_shared_from_this;

template <typename T>
shared_ptr<T> make_shared();
template <typename T, typename A0>
shared_ptr<T> make_shared(const A0& a0);
template <typename T, typename A0, typename A1>
shared_ptr<T> make_shared(const A0& a0, const A1& a1);
template <typename T, typename A0, typename A1, typename A2>
shared_ptr<T> make_shared(const A0& a0, const A1& a1, const A2& a2);
template <typename T, typename A0, typename A1, typename A2, typename A3>
shared_ptr<T>
make_shared(const A0& a0, const A1& a1, const A2& a2, const A3& a3);
template <typename T,
          typename A0,
          typename A1,
          typename A2,
          typename A3,
          typename A4>
shared_ptr<T> make_shared(const A0& a0,
                          const A1& a1,
                          const A2& a2,
                          const A3& a3,
                          const A4& a4);
template <typename T,
          typename A0,
          typename A1,
          typename A2,
          typename A3,
          typename A4,
          typename A5>
shared_ptr<T> make_shared(const A0& a0,
                          const A1& a1,
                          const A2& a2,
                          const A3& a3,
                          const A4& a4,
                          const A5& a5);
template <typename T,
          typename A0,
          typename A1,
          typename A2,
          typename A3,
          typename A4,
          typename A5,
          typename A6>
shared_ptr<T> make_shared(const A0& a0,
                          const A1& a1,
                          const A2& a2,
                          const A3& a3,
                          const A4& a4,
                          const A5& a5,
                          const A6& a6);
template <typename T,
          typename A0,
          typename A1,
          typename A2,
          typename A3,
          typename A4,
          typename A5,
          typename A6,
          typename A7>
shared_ptr<T> make_shared(const A0& a0,
                          const A1& a1,
                          const A2& a2,
                          const A3& a3,
                          const A4& a4,
                          const A5& a5,
                          const A6& a6,
                          const A7& a7);
template <typename T,
          typename A0,
          typename A1,
          typename A2,
          typename A3,
          typename A4,
          typename A5,
          typename A6,
          typename A7,
          typename A8>
shared_ptr<T> make_shared(const A0& a0,
                          const A1& a1,
                          const A2& a2,
                          const A3& a3,
                          const A4& a4,
                          const A5& a5,
                          const A6& a6,
                          const A7& a7,
                          const A8& a8);
template <typename T,
          typename A0,
          typename A1,
          typename A2,
          typename A3,
          typename A4,
          typename A5,
          typename A6,
          typename A7,
          typename A8,
          typename A9>
shared_ptr<T> make_shared(const A0& a0,
                          const A1& a1,
                          const A2& a2,
                          const A3& a3,
                          const A4& a4,
                          const A5& a5,
                          const A6& a6,
                          const A7& a7,
                          const A8& a8,
                          const A9& a9);

template <typename T, typename Alloc>
shared_ptr<T> allocate_shared(const Alloc& alloc);
template <typename T, typename Alloc, typename A0>
shared_ptr<T> allocate_shared(const Alloc& alloc, const A0& a0);
template <typename T, typename Alloc, typename A0, typename A1>
shared_ptr<T> allocate_shared(const Alloc& alloc, const A0& a0, const A1& a1);
template <typename T, typename Alloc, typename A0, typename A1, typename A2>
shared_ptr<T>
allocate_shared(const Alloc& alloc, const A0& a0, const A1& a1, const A2& a2);
template <typename T,
          typename Alloc,
          typename A0,
          typename A1,
          typename A2,
          typename A3>
shared_ptr<T> allocate_shared(const Alloc& alloc,
                              const A0& a0,
                              const A1& a1,
                              const A2& a2,
                              const A3& a3);
template <typename T,
          typename Alloc,
          typename A0,
          typename A1,
          typename A2,
          typename A3,
          typename A4>
shared_ptr<T> allocate_shared(const Alloc& alloc,
                              const A0& a0,
                              const A1& a1,
                              const A2& a2,
                              const A3& a3,
                              const A4& a4);
template <typename T,
          typename Alloc,
          typename A0,
          typename A1,
          typename A2,
          typename A3,
          typename A4,
          typename A5>
shared_ptr<T> allocate_shared(const Alloc& alloc,
                              const A0& a0,
                              const A1& a1,
                              const A2& a2,
                              const A3& a3,
                              const A4& a4,
                              const A5& a5);
template <typename T,
          typename Alloc,
          typename A0,
          typename A1,
          typename A2,
          typename A3,
          typename A4,
          typename A5,
          typename A6>
shared_ptr<T> allocate_shared(const Alloc& alloc,
                              const A0& a0,
                              const A1& a1,
                              const A2& a2,
                              const A3& a3,
                              const A4& a4,
                              const A5& a5,
                              const A6& a6);
template <typename T,
          typename Alloc,
          typename A0,
          typename A1,
          typename A2,
          typename A3,
          typename A4,
          typename A5,
          typename A6,
          typename A7>
shared_ptr<T> allocate_shared(const Alloc& alloc,
                              const A0& a0,
                              const A1& a1,
                              const A2& a2,
                              const A3& a3,
                              const A4& a4,
                              const A5& a5,
                              const A6& a6,
                              const A7& a7);
template <typename T,
          typename Alloc,
          typename A0,
          typename A1,
          typename A2,
          typename A3,
          typename A4,
          typename A5,
          typename A6,
          typename A7,
          typename A8>
shared_ptr<T> allocate_shared(const Alloc& alloc,
                              const A0& a0,
                              const A1& a1,
                              const A2& a2,
                              const A3& a3,
                              const A4& a4,
                              const A5& a5,
                              const A6& a6,
                              const A7& a7,
                              const A8& a8);
template <typename T,
          typename Alloc,
          typename A0,
          typename A1,
          typename A2,
          typename A3,
          typename A4,
          typename A5,
          typename A6,
          typename A7,
          typename A8,
          typename A9>
shared_ptr<T> allocate_shared(const Alloc& alloc,
                              const A0& a0,
                              const A1& a1,
                              const A2& a2,
                              const A3& a3,
                              const A4& a4,
                              const A5& a5,
                              const A6& a6,
                              const A7& a7,
                              const A8& a8,
                              const A9& a9);

template <typename T>
class shared_ptr : public ft::safe_bool<shared_ptr<T> > {
public:
	typedef T element_type;
	typedef weak_ptr<T> weak_type;

	shared_ptr() throw();
	template <typename Y>
	explicit shared_ptr(
	    Y* p,
	    typename ft::enable_if<ft::is_convertible<Y*, T*>::value>::type* =
	        FT_NULLPTR);
	template <typename Y, typename Deleter>
	shared_ptr(
	    Y* p,
	    Deleter d,
	    typename ft::enable_if<ft::is_convertible<Y*, T*>::value>::type* =
	        FT_NULLPTR);
	template <typename Y, typename Deleter, typename Alloc>
	shared_ptr(
	    Y* p,
	    Deleter d,
	    Alloc a,
	    typename ft::enable_if<ft::is_convertible<Y*, T*>::value>::type* =
	        FT_NULLPTR);
	shared_ptr(const shared_ptr& r) throw();
	template <typename Y>
	shared_ptr(
	    const shared_ptr<Y>& r,
	    typename ft::enable_if<ft::is_convertible<Y*, T*>::value>::type* =
	        FT_NULLPTR) throw();
	template <typename Y>
	explicit shared_ptr(
	    const weak_ptr<Y>& r,
	    typename ft::enable_if<ft::is_convertible<Y*, T*>::value>::type* =
	        FT_NULLPTR);
	template <typename Y>
	shared_ptr(
	    const shared_ptr<Y>& r,
	    element_type* p,
	    typename ft::enable_if<ft::is_convertible<Y*, T*>::value>::type* =
	        FT_NULLPTR) throw();
	template <typename Y>
	shared_ptr(
	    std::auto_ptr<Y>& r,
	    typename ft::enable_if<ft::is_convertible<Y*, T*>::value>::type* =
	        FT_NULLPTR);
	shared_ptr(ft::rvalue<shared_ptr>& r) throw();
	template <typename Y>
	shared_ptr(ft::rvalue<shared_ptr<Y> >& r,
	           typename ft::enable_if<
	               ft::is_convertible<typename shared_ptr<Y>::element_type*,
	                                  element_type*>::value>::type* =
	               FT_NULLPTR) throw();
	~shared_ptr();

	shared_ptr& operator=(const shared_ptr& r) throw();
	template <typename Y>
	shared_ptr& operator=(const shared_ptr<Y>& r) throw();
	shared_ptr& operator=(ft::rvalue<shared_ptr>& r) throw();
	template <typename Y>
	shared_ptr& operator=(ft::rvalue<shared_ptr<Y> >& r) throw();
	template <typename Y>
	shared_ptr& operator=(std::auto_ptr<Y> r);

	void reset() throw();
	template <typename Y>
	void reset(Y* p);
	template <typename Y, typename Deleter>
	void reset(Y* p, Deleter d);
	template <typename Y, typename Deleter, typename Alloc>
	void reset(Y* p, Deleter d, Alloc a);

	element_type* get() const throw();
	element_type& operator*() const;
	element_type* operator->() const throw();
	long use_count() const throw();
	bool unique() const throw();
	bool boolean_test() const throw();

	void swap(shared_ptr& other) throw();
	template <typename Y>
	bool owner_before(const shared_ptr<Y>& other) const throw();
	template <typename Y>
	bool owner_before(const weak_ptr<Y>& other) const throw();

private:
	template <typename Y>
	friend class shared_ptr;
	template <typename Y>
	friend class weak_ptr;
	template <typename Y>
	friend class enable_shared_from_this;

	shared_ptr(_shared_ptr::control_block_base* control,
	           element_type* ptr) throw();

	template <typename Y, typename Deleter, typename Alloc>
	void _construct_control(Y* p, Deleter d, const Alloc& a);
	template <typename Y, typename Deleter>
	void _construct_control(Y* p, Deleter d, const std::allocator<void>& a);
	void _enable_shared_from_this(element_type* p) throw();
	void _release() throw();

	element_type* _ptr;
	_shared_ptr::control_block_base* _control;
};

template <typename T>
class weak_ptr : public ft::safe_bool<weak_ptr<T> > {
public:
	typedef T element_type;

	weak_ptr() throw();
	template <typename Y>
	weak_ptr(const shared_ptr<Y>& r,
	         typename ft::enable_if<ft::is_convertible<Y*, T*>::value>::type* =
	             FT_NULLPTR) throw();
	weak_ptr(const weak_ptr& r) throw();
	template <typename Y>
	weak_ptr(const weak_ptr<Y>& r,
	         typename ft::enable_if<ft::is_convertible<Y*, T*>::value>::type* =
	             FT_NULLPTR) throw();
	weak_ptr(ft::rvalue<weak_ptr>& r) throw();
	template <typename Y>
	weak_ptr(ft::rvalue<weak_ptr<Y> >& r,
	         typename ft::enable_if<ft::is_convertible<Y*, T*>::value>::type* =
	             FT_NULLPTR) throw();
	~weak_ptr();

	weak_ptr& operator=(const weak_ptr& r) throw();
	template <typename Y>
	weak_ptr& operator=(const weak_ptr<Y>& r) throw();
	template <typename Y>
	weak_ptr& operator=(const shared_ptr<Y>& r) throw();
	weak_ptr& operator=(ft::rvalue<weak_ptr>& r) throw();
	template <typename Y>
	weak_ptr& operator=(ft::rvalue<weak_ptr<Y> >& r) throw();

	void reset() throw();
	void swap(weak_ptr& other) throw();
	long use_count() const throw();
	bool expired() const throw();
	shared_ptr<T> lock() const;
	bool boolean_test() const throw();

private:
	template <typename Y>
	friend class weak_ptr;
	template <typename Y>
	friend class shared_ptr;

	weak_ptr(_shared_ptr::control_block_base* control,
	         element_type* ptr) throw();
	void _release() throw();

	element_type* _ptr;
	_shared_ptr::control_block_base* _control;
};

template <typename T>
class enable_shared_from_this {
protected:
	enable_shared_from_this() throw();
	enable_shared_from_this(const enable_shared_from_this& other) throw();
	enable_shared_from_this&
	operator=(const enable_shared_from_this& other) throw();
	~enable_shared_from_this();

public:
	shared_ptr<T> shared_from_this();
	shared_ptr<const T> shared_from_this() const;
	weak_ptr<T> weak_from_this() throw();
	weak_ptr<const T> weak_from_this() const throw();

private:
	template <typename T1, typename Y>
	friend void _shared_ptr::enable_shared_from_this(
	    const shared_ptr<T1>* owner,
	    const Y* p,
	    const enable_shared_from_this<Y>* base);

	void _internal_accept_owner(const shared_ptr<T>& sp) const throw();

	mutable weak_ptr<T> _weak_this;
};

template <typename T>
void swap(shared_ptr<T>& lhs, shared_ptr<T>& rhs) throw();
template <typename T>
void swap(weak_ptr<T>& lhs, weak_ptr<T>& rhs) throw();

template <typename T1, typename T2>
bool operator==(const shared_ptr<T1>& lhs, const shared_ptr<T2>& rhs) throw();
template <typename T1, typename T2>
bool operator!=(const shared_ptr<T1>& lhs, const shared_ptr<T2>& rhs) throw();
template <typename T1, typename T2>
bool operator<(const shared_ptr<T1>& lhs, const shared_ptr<T2>& rhs) throw();
template <typename T1, typename T2>
bool operator<=(const shared_ptr<T1>& lhs, const shared_ptr<T2>& rhs) throw();
template <typename T1, typename T2>
bool operator>(const shared_ptr<T1>& lhs, const shared_ptr<T2>& rhs) throw();
template <typename T1, typename T2>
bool operator>=(const shared_ptr<T1>& lhs, const shared_ptr<T2>& rhs) throw();

template <typename T>
bool operator==(const shared_ptr<T>& lhs, nullptr_t /*unused*/) throw();
template <typename T>
bool operator==(nullptr_t /*unused*/, const shared_ptr<T>& rhs) throw();
template <typename T>
bool operator!=(const shared_ptr<T>& lhs, nullptr_t /*unused*/) throw();
template <typename T>
bool operator!=(nullptr_t /*unused*/, const shared_ptr<T>& rhs) throw();
template <typename T>
bool operator<(const shared_ptr<T>& lhs, nullptr_t /*unused*/) throw();
template <typename T>
bool operator<(nullptr_t /*unused*/, const shared_ptr<T>& rhs) throw();
template <typename T>
bool operator<=(const shared_ptr<T>& lhs, nullptr_t /*unused*/) throw();
template <typename T>
bool operator<=(nullptr_t /*unused*/, const shared_ptr<T>& rhs) throw();
template <typename T>
bool operator>(const shared_ptr<T>& lhs, nullptr_t /*unused*/) throw();
template <typename T>
bool operator>(nullptr_t /*unused*/, const shared_ptr<T>& rhs) throw();
template <typename T>
bool operator>=(const shared_ptr<T>& lhs, nullptr_t /*unused*/) throw();
template <typename T>
bool operator>=(nullptr_t /*unused*/, const shared_ptr<T>& rhs) throw();

template <typename T1, typename T2>
bool operator==(const weak_ptr<T1>& lhs, const weak_ptr<T2>& rhs) throw();
template <typename T1, typename T2>
bool operator!=(const weak_ptr<T1>& lhs, const weak_ptr<T2>& rhs) throw();
template <typename T1, typename T2>
bool operator<(const weak_ptr<T1>& lhs, const weak_ptr<T2>& rhs) throw();
template <typename T1, typename T2>
bool operator<=(const weak_ptr<T1>& lhs, const weak_ptr<T2>& rhs) throw();
template <typename T1, typename T2>
bool operator>(const weak_ptr<T1>& lhs, const weak_ptr<T2>& rhs) throw();
template <typename T1, typename T2>
bool operator>=(const weak_ptr<T1>& lhs, const weak_ptr<T2>& rhs) throw();

template <typename T, typename U>
shared_ptr<T> static_pointer_cast(const shared_ptr<U>& r) throw();
template <typename T, typename U>
shared_ptr<T> const_pointer_cast(const shared_ptr<U>& r) throw();
template <typename T, typename U>
shared_ptr<T> dynamic_pointer_cast(const shared_ptr<U>& r);
template <typename T, typename U>
shared_ptr<T> reinterpret_pointer_cast(const shared_ptr<U>& r) throw();

template <typename Deleter, typename T>
Deleter* get_deleter(const shared_ptr<T>& p) throw();

template <typename CharT, typename Traits, typename Y>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const shared_ptr<Y>& p);

/* unique_ptr */

/**
 * https://en.cppreference.com/w/cpp/memory/unique_ptr
 *
 * @note Don't create a unique_ptr from a pointer unless you know where the
 * pointer came from and that it needs an owner. This prevents double frees.
 */
template <typename T, typename Deleter = default_delete<T> >
class unique_ptr : public ft::safe_bool<unique_ptr<T, Deleter> > {
private:
	FT_STATIC_ASSERT(ft::is_pointer<T*>::value); // T* must form a valid type.

	template <typename U, typename E>
	struct _is_compatible_unique_ptr;
	struct _enabler {};

public:
	/**
	 * `remove_reference<Deleter>::type::pointer` if that type exists, otherwise
	 * `T*`.
	 */
	typedef typename _unique_ptr::pointer<T, Deleter>::type pointer;
	typedef T element_type;
	typedef Deleter deleter_type;

	// 1)
	unique_ptr() throw();
	// NOLINTBEGIN(google-explicit-constructor): Original in `std::unique_ptr`
	// is not `explicit`.
	template <typename Nullptr_t>
	unique_ptr(
	    Nullptr_t /*unused*/,
	    typename ft::enable_if<ft::is_convertible<Nullptr_t, nullptr_t>::value
	                               && !ft::is_pointer<Deleter>::value,
	                           _enabler>::type /*unused*/
	    = _enabler()) throw();
	// NOLINTEND(google-explicit-constructor)
	// 2)
	template <typename Pointer>
	explicit unique_ptr(
	    Pointer p,
	    typename ft::enable_if<ft::is_convertible<Pointer, pointer>::value
	                               && !ft::is_pointer<Deleter>::value,
	                           _enabler>::type /*unused*/
	    = _enabler()) throw();
	// 3) a,b,c) (1)
	unique_ptr(pointer p,
	           typename ft::conditional<
	               !ft::is_reference<Deleter>::value,
	               typename ft::add_lvalue_reference<const Deleter>::type,
	               Deleter>::type d) throw();
	// 4) a) (2)
	template <typename Pointer>
	unique_ptr(
	    Pointer p,
	    ft::rvalue<Deleter>& d,
	    typename ft::enable_if<ft::is_convertible<Pointer, pointer>::value
	                               && !ft::is_reference<Deleter>::value,
	                           _enabler>::type /*unused*/
	    = _enabler()) throw();
	// NOLINTBEGIN(google-explicit-constructor): Move constructors.
	// 5)
	unique_ptr(ft::rvalue<unique_ptr>& u) throw();
	// 6)
	template <typename U, typename E>
	unique_ptr(ft::rvalue<unique_ptr<U, E> >& u,
	           typename ft::enable_if<
	               _is_compatible_unique_ptr<U, E>::value
	                   && _unique_ptr::is_compatible_deleter<E, Deleter>::value,
	               _enabler>::type /*unused*/
	           = _enabler()) throw();
	// NOLINTEND(google-explicit-constructor)
	~unique_ptr();
	unique_ptr& operator=(ft::rvalue<unique_ptr>& r) throw();
	template <typename U, typename E>
	unique_ptr& operator=(ft::rvalue<unique_ptr<U, E> >& r) throw();
	unique_ptr& operator=(nullptr_t /*unused*/) throw();

	pointer release() throw();
	void reset(pointer ptr = pointer()) throw();
	void swap(unique_ptr& other) throw();

	/**
	 * @note Make sure the returned raw pointer is no longer in use after the
	 * unique_ptr goes out of scope.
	 */
	pointer get() const throw();
	// C++98 did not have reference collapsing yet.
	typename ft::add_lvalue_reference<Deleter>::type get_deleter() throw();
	typename ft::add_lvalue_reference<const Deleter>::type get_deleter() const
	    throw();
	bool boolean_test() const throw();

	typename ft::add_lvalue_reference<T>::type operator*() const;
	pointer operator->() const throw();

private:
	FT_MOVABLE_BUT_NOT_COPYABLE(unique_ptr)

	// 4) b,c) (2)
	template <typename Pointer>
	unique_ptr(
	    Pointer p,
	    typename ft::add_rvalue_reference<
	        typename ft::remove_reference<Deleter>::type>::type d,
	    typename ft::enable_if<ft::is_convertible<Pointer, pointer>::value
	                               && ft::is_lvalue_reference<Deleter>::value,
	                           _enabler>::type = _enabler()) throw();

	pointer _ptr;
	Deleter _deleter;
};

template <typename T>
FT_REQUIRES(!ft::is_array<T>::value)
(unique_ptr<T>)make_unique();
template <typename T, typename A0>
FT_REQUIRES(!ft::is_array<T>::value)
(unique_ptr<T>)make_unique(const A0& arg0);
template <typename T, typename A0, typename A1>
FT_REQUIRES(!ft::is_array<T>::value)
(unique_ptr<T>)make_unique(const A0& arg0, const A1& arg1);
template <typename T, typename A0, typename A1, typename A2>
FT_REQUIRES(!ft::is_array<T>::value)
(unique_ptr<T>)make_unique(const A0& arg0, const A1& arg1, const A2& arg2);
template <typename T, typename A0, typename A1, typename A2, typename A3>
FT_REQUIRES(!ft::is_array<T>::value)
(unique_ptr<T>)
    make_unique(const A0& arg0, const A1& arg1, const A2& arg2, const A3& arg3);
template <typename T,
          typename A0,
          typename A1,
          typename A2,
          typename A3,
          typename A4>
FT_REQUIRES(!ft::is_array<T>::value)
(unique_ptr<T>)make_unique(const A0& arg0,
                           const A1& arg1,
                           const A2& arg2,
                           const A3& arg3,
                           const A4& arg4);
template <typename T,
          typename A0,
          typename A1,
          typename A2,
          typename A3,
          typename A4,
          typename A5>
FT_REQUIRES(!ft::is_array<T>::value)
(unique_ptr<T>)make_unique(const A0& arg0,
                           const A1& arg1,
                           const A2& arg2,
                           const A3& arg3,
                           const A4& arg4,
                           const A5& arg5);
template <typename T,
          typename A0,
          typename A1,
          typename A2,
          typename A3,
          typename A4,
          typename A5,
          typename A6>
FT_REQUIRES(!ft::is_array<T>::value)
(unique_ptr<T>)make_unique(const A0& arg0,
                           const A1& arg1,
                           const A2& arg2,
                           const A3& arg3,
                           const A4& arg4,
                           const A5& arg5,
                           const A6& arg6);
template <typename T,
          typename A0,
          typename A1,
          typename A2,
          typename A3,
          typename A4,
          typename A5,
          typename A6,
          typename A7>
FT_REQUIRES(!ft::is_array<T>::value)
(unique_ptr<T>)make_unique(const A0& arg0,
                           const A1& arg1,
                           const A2& arg2,
                           const A3& arg3,
                           const A4& arg4,
                           const A5& arg5,
                           const A6& arg6,
                           const A7& arg7);
template <typename T,
          typename A0,
          typename A1,
          typename A2,
          typename A3,
          typename A4,
          typename A5,
          typename A6,
          typename A7,
          typename A8>
FT_REQUIRES(!ft::is_array<T>::value)
(unique_ptr<T>)make_unique(const A0& arg0,
                           const A1& arg1,
                           const A2& arg2,
                           const A3& arg3,
                           const A4& arg4,
                           const A5& arg5,
                           const A6& arg6,
                           const A7& arg7,
                           const A8& arg8);
template <typename T,
          typename A0,
          typename A1,
          typename A2,
          typename A3,
          typename A4,
          typename A5,
          typename A6,
          typename A7,
          typename A8,
          typename A9>
FT_REQUIRES(!ft::is_array<T>::value)
(unique_ptr<T>)make_unique(const A0& arg0,
                           const A1& arg1,
                           const A2& arg2,
                           const A3& arg3,
                           const A4& arg4,
                           const A5& arg5,
                           const A6& arg6,
                           const A7& arg7,
                           const A8& arg8,
                           const A9& arg9);

template <typename T>
FT_REQUIRES(!ft::is_array<T>::value)
(unique_ptr<T>)make_unique_for_overwrite();

template <typename T1, typename D1, typename T2, typename D2>
bool operator==(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
template <typename T1, typename D1, typename T2, typename D2>
bool operator!=(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
template <typename T1, typename D1, typename T2, typename D2>
bool operator<(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
template <typename T1, typename D1, typename T2, typename D2>
bool operator<=(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
template <typename T1, typename D1, typename T2, typename D2>
bool operator>(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
template <typename T1, typename D1, typename T2, typename D2>
bool operator>=(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
template <typename T, typename D>
bool operator==(const unique_ptr<T, D>& x, nullptr_t /*unused*/) throw();
template <typename T, typename D>
bool operator==(nullptr_t /*unused*/, const unique_ptr<T, D>& x) throw();
template <typename T, typename D>
bool operator!=(const unique_ptr<T, D>& x, nullptr_t /*unused*/) throw();
template <typename T, typename D>
bool operator!=(nullptr_t /*unused*/, const unique_ptr<T, D>& x) throw();
template <typename T, typename D>
bool operator<(const unique_ptr<T, D>& x, nullptr_t /*unused*/);
template <typename T, typename D>
bool operator<(nullptr_t /*unused*/, const unique_ptr<T, D>& y);
template <typename T, typename D>
bool operator<=(const unique_ptr<T, D>& x, nullptr_t /*unused*/);
template <typename T, typename D>
bool operator<=(nullptr_t /*unused*/, const unique_ptr<T, D>& y);
template <typename T, typename D>
bool operator>(const unique_ptr<T, D>& x, nullptr_t /*unused*/);
template <typename T, typename D>
bool operator>(nullptr_t /*unused*/, const unique_ptr<T, D>& y);
template <typename T, typename D>
bool operator>=(const unique_ptr<T, D>& x, nullptr_t /*unused*/);
template <typename T, typename D>
bool operator>=(nullptr_t /*unused*/, const unique_ptr<T, D>& y);

template <typename CharT, typename Traits, typename Y, typename D>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const unique_ptr<Y, D>& p);

template <typename T, typename D>
void swap(unique_ptr<T, D>& lhs, unique_ptr<T, D>& rhs) throw();

/**
 * https://en.cppreference.com/w/cpp/memory/unique_ptr
 */
template <typename T, typename Deleter /*= default_delete<T> */>
class unique_ptr<T[], Deleter>
    : public ft::safe_bool<unique_ptr<T[], Deleter> > {
private:
	FT_STATIC_ASSERT(ft::is_pointer<T*>::value); // T* must form a valid type.

	template <typename U>
	struct _is_compatible_raw_pointer;
	template <typename U, typename E>
	struct _is_compatible_unique_ptr;
	struct _enabler {};

public:
	/**
	 * `remove_reference<Deleter>::type::pointer` if that type exists, otherwise
	 * `T*`.
	 */
	typedef typename _unique_ptr::pointer<T, Deleter>::type pointer;
	typedef T element_type;
	typedef Deleter deleter_type;

	// 1)
	unique_ptr() throw();
	// NOLINTBEGIN(google-explicit-constructor): Original in `std::unique_ptr`
	// is not `explicit`.
	template <typename Nullptr_t>
	unique_ptr(
	    Nullptr_t /*unused*/,
	    typename ft::enable_if<ft::is_convertible<Nullptr_t, nullptr_t>::value
	                               && !ft::is_pointer<Deleter>::value,
	                           _enabler>::type /*unused*/
	    = _enabler()) throw();
	// NOLINTEND(google-explicit-constructor)
	// 2)
	template <typename U>
	explicit unique_ptr(
	    U p,
	    typename ft::enable_if<!ft::is_pointer<Deleter>::value
	                               && _is_compatible_raw_pointer<U>::value,
	                           _enabler>::type /*unused*/
	    = _enabler()) throw();
	// 3) a,b,c) (1)
	template <typename U>
	unique_ptr(U p,
	           typename ft::conditional<
	               !ft::is_reference<Deleter>::value,
	               typename ft::add_lvalue_reference<const Deleter>::type,
	               Deleter>::type d,
	           typename ft::enable_if<_is_compatible_raw_pointer<U>::value,
	                                  _enabler>::type /*unused*/
	           = _enabler()) throw();
	// 4) a) (2)
	template <typename U>
	unique_ptr(
	    U p,
	    ft::rvalue<Deleter>& d,
	    typename ft::enable_if<!ft::is_reference<Deleter>::value
	                               && _is_compatible_raw_pointer<U>::value,
	                           _enabler>::type /*unused*/
	    = _enabler()) throw();
	// NOLINTBEGIN(google-explicit-constructor): Move constructors.
	// 5)
	unique_ptr(ft::rvalue<unique_ptr>& u) throw();
	// 6)
	template <typename U, typename E>
	unique_ptr(ft::rvalue<unique_ptr<U, E> >& u,
	           typename ft::enable_if<
	               _is_compatible_unique_ptr<U, E>::value
	                   && _unique_ptr::is_compatible_deleter<E, Deleter>::value,
	               _enabler>::type /*unused*/
	           = _enabler()) throw();
	// NOLINTEND(google-explicit-constructor)
	~unique_ptr();
	unique_ptr& operator=(ft::rvalue<unique_ptr>& r) throw();
	template <typename U, typename E>
	unique_ptr& operator=(ft::rvalue<unique_ptr<U, E> >& r) throw();
	unique_ptr& operator=(nullptr_t /*unused*/) throw();

	pointer release() throw();
	template <typename U>
	void reset(U ptr,
	           typename ft::enable_if<_is_compatible_raw_pointer<U>::value,
	                                  _enabler>::type /*unused*/
	           = _enabler()) throw();
	void reset(nullptr_t /*unused*/ = FT_NULLPTR) throw();
	void swap(unique_ptr& other) throw();

	/**
	 * @note Make sure the returned raw pointer is no longer in use after the
	 * unique_ptr goes out of scope.
	 */
	pointer get() const throw();
	// C++98 did not have reference collapsing yet.
	typename ft::add_lvalue_reference<Deleter>::type get_deleter() throw();
	typename ft::add_lvalue_reference<const Deleter>::type get_deleter() const
	    throw();
	bool boolean_test() const throw();

	T& operator[](std::size_t i) const;

private:
	FT_MOVABLE_BUT_NOT_COPYABLE(unique_ptr)

	// 4) b,c) (2)
	template <typename Pointer>
	unique_ptr(Pointer p,
	           typename ft::add_rvalue_reference<
	               typename ft::remove_reference<Deleter>::type>::type d,
	           typename ft::enable_if<
	               ft::is_lvalue_reference<Deleter>::value
	                   && _is_compatible_raw_pointer<Pointer>::value,
	               _enabler>::type = _enabler()) throw();

	pointer _ptr;
	Deleter _deleter;
};

template <typename T>
FT_REQUIRES(ft::is_unbounded_array<T>::value)
(unique_ptr<T>)make_unique(std::size_t size);

template <typename T>
FT_REQUIRES(ft::is_unbounded_array<T>::value)
(unique_ptr<T>)make_unique_for_overwrite(std::size_t size);

} // namespace ft

#	include "libftpp/memory/default_delete.tpp"   // IWYU pragma: export
#	include "libftpp/memory/unique_ptr.tpp"       // IWYU pragma: export
#	include "libftpp/memory/unique_ptr_array.tpp" // IWYU pragma: export

#endif // LIBFTPP_MEMORY_HPP
