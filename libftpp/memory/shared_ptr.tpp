#pragma once
#ifndef LIBFTPP_MEMORY_SHARED_PTR_TPP
#	define LIBFTPP_MEMORY_SHARED_PTR_TPP

#	include "libftpp/memory.hpp"
#	include "libftpp/assert.hpp"
#	include "libftpp/utility.hpp"
#	include <algorithm>
#	include <cassert>
#	include <new>

namespace ft {

/* bad_weak_ptr */

inline const char* bad_weak_ptr::what() const throw() { return "bad_weak_ptr"; }

/* shared_ptr */

template <typename T>
shared_ptr<T>::shared_ptr() throw()
    : _ptr(FT_NULLPTR),
      _control(0)
{}

template <typename T>
template <typename Y>
shared_ptr<T>::shared_ptr(
    Y* p,
    typename ft::enable_if<ft::is_convertible<Y*, T*>::value>::type* /*unused*/)
    : _ptr(p),
      _control(0)
{
	if (p == FT_NULLPTR) {
		return;
	}
	try {
		_construct_control(p, ft::default_delete<Y>(), std::allocator<void>());
	}
	catch (...) {
		ft::default_delete<Y>()(p);
		throw;
	}
	_enable_shared_from_this(_ptr);
}

template <typename T>
template <typename Y, typename Deleter>
shared_ptr<T>::shared_ptr(
    Y* p,
    Deleter d,
    typename ft::enable_if<ft::is_convertible<Y*, T*>::value>::type* /*unused*/)
    : _ptr(p),
      _control(0)
{
	if (p == FT_NULLPTR) {
		return;
	}
	try {
		_construct_control(p, d, std::allocator<void>());
	}
	catch (...) {
		d(p);
		throw;
	}
	_enable_shared_from_this(_ptr);
}

template <typename T>
template <typename Y, typename Deleter, typename Alloc>
shared_ptr<T>::shared_ptr(
    Y* p,
    Deleter d,
    Alloc a,
    typename ft::enable_if<ft::is_convertible<Y*, T*>::value>::type* /*unused*/)
    : _ptr(p),
      _control(0)
{
	if (p == FT_NULLPTR) {
		return;
	}
	try {
		_construct_control(p, d, a);
	}
	catch (...) {
		d(p);
		throw;
	}
	_enable_shared_from_this(_ptr);
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& r) throw()
    : _ptr(r._ptr),
      _control(r._control)
{
	if (_control != 0) {
		_control->add_shared();
	}
}

template <typename T>
template <typename Y>
shared_ptr<T>::shared_ptr(
    const shared_ptr<Y>& r,
    typename ft::enable_if<
        ft::is_convertible<Y*, T*>::value>::type* /*unused*/) throw()
    : _ptr(r._ptr),
      _control(r._control)
{
	if (_control != 0) {
		_control->add_shared();
	}
}

template <typename T>
template <typename Y>
shared_ptr<T>::shared_ptr(
    const weak_ptr<Y>& r,
    typename ft::enable_if<ft::is_convertible<Y*, T*>::value>::type* /*unused*/)
    : _ptr(FT_NULLPTR),
      _control(0)
{
	_shared_ptr::control_block_base* control = r._control;
	if (!control || !control->add_shared_if_nonzero()) {
		throw bad_weak_ptr();
	}
	_ptr = const_cast<Y*>(r._ptr);
	_control = control;
}

template <typename T>
template <typename Y>
shared_ptr<T>::shared_ptr(
    const shared_ptr<Y>& r,
    element_type* p,
    typename ft::enable_if<
        ft::is_convertible<Y*, T*>::value>::type* /*unused*/) throw()
    : _ptr(p),
      _control(r._control)
{
	if (_control != 0) {
		_control->add_shared();
	}
}

template <typename T>
template <typename Y>
shared_ptr<T>::shared_ptr(
    std::auto_ptr<Y>& r,
    typename ft::enable_if<ft::is_convertible<Y*, T*>::value>::type* /*unused*/)
    : _ptr(r.get()),
      _control(0)
{
	Y* raw = r.get();
	r.release();
	if (raw == FT_NULLPTR) {
		return;
	}
	try {
		_construct_control(
		    raw, ft::default_delete<Y>(), std::allocator<void>());
	}
	catch (...) {
		ft::default_delete<Y>()(raw);
		throw;
	}
	_ptr = raw;
	_enable_shared_from_this(_ptr);
}

template <typename T>
shared_ptr<T>::shared_ptr(ft::rvalue<shared_ptr>& r) throw()
    : _ptr(r._ptr),
      _control(r._control)
{
	r._ptr = FT_NULLPTR;
	r._control = 0;
}

template <typename T>
template <typename Y>
shared_ptr<T>::shared_ptr(
    ft::rvalue<shared_ptr<Y> >& r,
    typename ft::enable_if<
        ft::is_convertible<typename shared_ptr<Y>::element_type*,
                           element_type*>::value>::type* /*unused*/) throw()
    : _ptr(r._ptr),
      _control(r._control)
{
	r._ptr = FT_NULLPTR;
	r._control = 0;
}

template <typename T>
shared_ptr<T>::~shared_ptr()
{
	_release();
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& r) throw()
{
	if (this != &r) {
		shared_ptr tmp(r);
		swap(tmp);
	}
	return *this;
}

template <typename T>
template <typename Y>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<Y>& r) throw()
{
	shared_ptr tmp(r);
	swap(tmp);
	return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(ft::rvalue<shared_ptr>& r) throw()
{
	if (this != &r) {
		_release();
		_ptr = r._ptr;
		_control = r._control;
		r._ptr = FT_NULLPTR;
		r._control = 0;
	}
	return *this;
}

template <typename T>
template <typename Y>
shared_ptr<T>& shared_ptr<T>::operator=(ft::rvalue<shared_ptr<Y> >& r) throw()
{
	_release();
	_ptr = r._ptr;
	_control = r._control;
	r._ptr = FT_NULLPTR;
	r._control = 0;
	return *this;
}

template <typename T>
template <typename Y>
shared_ptr<T>& shared_ptr<T>::operator=(std::auto_ptr<Y> r)
{
	shared_ptr tmp(r);
	swap(tmp);
	return *this;
}

template <typename T>
void shared_ptr<T>::reset() throw()
{
	shared_ptr().swap(*this);
}

template <typename T>
template <typename Y>
void shared_ptr<T>::reset(Y* p)
{
	shared_ptr(p).swap(*this);
}

template <typename T>
template <typename Y, typename Deleter>
void shared_ptr<T>::reset(Y* p, Deleter d)
{
	shared_ptr(p, d).swap(*this);
}

template <typename T>
template <typename Y, typename Deleter, typename Alloc>
void shared_ptr<T>::reset(Y* p, Deleter d, Alloc a)
{
	shared_ptr(p, d, a).swap(*this);
}

template <typename T>
typename shared_ptr<T>::element_type* shared_ptr<T>::get() const throw()
{
	return _ptr;
}

template <typename T>
typename shared_ptr<T>::element_type& shared_ptr<T>::operator*() const
{
	assert(_ptr != FT_NULLPTR);
	return *_ptr;
}

template <typename T>
typename shared_ptr<T>::element_type* shared_ptr<T>::operator->() const throw()
{
	assert(_ptr != FT_NULLPTR);
	return _ptr;
}

template <typename T>
long shared_ptr<T>::use_count() const throw()
{
	return _control ? _control->use_count() : 0;
}

template <typename T>
bool shared_ptr<T>::unique() const throw()
{
	return use_count() == 1;
}

template <typename T>
bool shared_ptr<T>::boolean_test() const throw()
{
	return _ptr != FT_NULLPTR;
}

template <typename T>
void shared_ptr<T>::swap(shared_ptr& other) throw()
{
	using std::swap;
	swap(_ptr, other._ptr);
	swap(_control, other._control);
}

template <typename T>
template <typename Y>
bool shared_ptr<T>::owner_before(const shared_ptr<Y>& other) const throw()
{
	return _control < other._control;
}

template <typename T>
template <typename Y>
bool shared_ptr<T>::owner_before(const weak_ptr<Y>& other) const throw()
{
	return _control < other._control;
}

template <typename T>
template <typename Y, typename Deleter, typename Alloc>
void shared_ptr<T>::_construct_control(Y* p, Deleter d, const Alloc& a)
{
	typedef _shared_ptr::control_block_ptr<Y*, Deleter, Alloc> block_type;
	typedef typename _shared_ptr::rebind_allocator<Alloc, block_type>::type
	    allocator_type;
	allocator_type alloc(a);
	block_type* block = alloc.allocate(1);
	try {
		new (block) block_type(p, d, a);
	}
	catch (...) {
		alloc.deallocate(block, 1);
		throw;
	}
	_control = block;
}

template <typename T>
void shared_ptr<T>::_enable_shared_from_this(element_type* p) throw()
{
	_shared_ptr::enable_shared_from_this(this, p, p);
}

template <typename T>
void shared_ptr<T>::_release() throw()
{
	if (_control != 0) {
		_control->release_shared();
		_ptr = FT_NULLPTR;
		_control = 0;
	}
}

/* weak_ptr */

template <typename T>
weak_ptr<T>::weak_ptr() throw()
    : _ptr(FT_NULLPTR),
      _control(0)
{}

template <typename T>
template <typename Y>
weak_ptr<T>::weak_ptr(
    const shared_ptr<Y>& r,
    typename ft::enable_if<
        ft::is_convertible<Y*, T*>::value>::type* /*unused*/) throw()
    : _ptr(r._ptr),
      _control(r._control)
{
	if (_control != 0) {
		_control->add_weak();
	}
}

template <typename T>
weak_ptr<T>::weak_ptr(const weak_ptr& r) throw()
    : _ptr(r._ptr),
      _control(r._control)
{
	if (_control != 0) {
		_control->add_weak();
	}
}

template <typename T>
template <typename Y>
weak_ptr<T>::weak_ptr(
    const weak_ptr<Y>& r,
    typename ft::enable_if<
        ft::is_convertible<Y*, T*>::value>::type* /*unused*/) throw()
    : _ptr(r._ptr),
      _control(r._control)
{
	if (_control != 0) {
		_control->add_weak();
	}
}

template <typename T>
weak_ptr<T>::weak_ptr(ft::rvalue<weak_ptr>& r) throw()
    : _ptr(r._ptr),
      _control(r._control)
{
	r._ptr = FT_NULLPTR;
	r._control = 0;
}

template <typename T>
template <typename Y>
weak_ptr<T>::weak_ptr(
    ft::rvalue<weak_ptr<Y> >& r,
    typename ft::enable_if<
        ft::is_convertible<Y*, T*>::value>::type* /*unused*/) throw()
    : _ptr(r._ptr),
      _control(r._control)
{
	r._ptr = FT_NULLPTR;
	r._control = 0;
}

template <typename T>
weak_ptr<T>::~weak_ptr()
{
	_release();
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(const weak_ptr& r) throw()
{
	if (this != &r) {
		weak_ptr tmp(r);
		swap(tmp);
	}
	return *this;
}

template <typename T>
template <typename Y>
weak_ptr<T>& weak_ptr<T>::operator=(const weak_ptr<Y>& r) throw()
{
	weak_ptr tmp(r);
	swap(tmp);
	return *this;
}

template <typename T>
template <typename Y>
weak_ptr<T>& weak_ptr<T>::operator=(const shared_ptr<Y>& r) throw()
{
	weak_ptr tmp(r);
	swap(tmp);
	return *this;
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(ft::rvalue<weak_ptr>& r) throw()
{
	if (this != &r) {
		_release();
		_ptr = r._ptr;
		_control = r._control;
		r._ptr = FT_NULLPTR;
		r._control = 0;
	}
	return *this;
}

template <typename T>
template <typename Y>
weak_ptr<T>& weak_ptr<T>::operator=(ft::rvalue<weak_ptr<Y> >& r) throw()
{
	_release();
	_ptr = r._ptr;
	_control = r._control;
	r._ptr = FT_NULLPTR;
	r._control = 0;
	return *this;
}

template <typename T>
void weak_ptr<T>::reset() throw()
{
	weak_ptr().swap(*this);
}

template <typename T>
void weak_ptr<T>::swap(weak_ptr& other) throw()
{
	using std::swap;
	swap(_ptr, other._ptr);
	swap(_control, other._control);
}

template <typename T>
long weak_ptr<T>::use_count() const throw()
{
	return _control ? _control->use_count() : 0;
}

template <typename T>
bool weak_ptr<T>::expired() const throw()
{
	return use_count() == 0;
}

template <typename T>
shared_ptr<T> weak_ptr<T>::lock() const
{
	if (!_control || !_control->add_shared_if_nonzero()) {
		return shared_ptr<T>();
	}
	return shared_ptr<T>(_control, _ptr);
}

template <typename T>
bool weak_ptr<T>::boolean_test() const throw()
{
	return !expired();
}

template <typename T>
weak_ptr<T>::weak_ptr(_shared_ptr::control_block_base* control,
                      element_type* ptr) throw()
    : _ptr(ptr),
      _control(control)
{
	if (_control != 0) {
		_control->add_weak();
	}
}

template <typename T>
void weak_ptr<T>::_release() throw()
{
	if (_control != 0) {
		_control->release_weak();
		_control = 0;
		_ptr = FT_NULLPTR;
	}
}

/* enable_shared_from_this */

template <typename T>
enable_shared_from_this<T>::enable_shared_from_this() throw()
    : _weak_this()
{}

template <typename T>
enable_shared_from_this<T>::enable_shared_from_this(
    const enable_shared_from_this& other) throw()
    : _weak_this(other._weak_this)
{}

template <typename T>
enable_shared_from_this<T>& enable_shared_from_this<T>::operator=(
    const enable_shared_from_this& other) throw()
{
	_weak_this = other._weak_this;
	return *this;
}

template <typename T>
enable_shared_from_this<T>::~enable_shared_from_this()
{}

template <typename T>
shared_ptr<T> enable_shared_from_this<T>::shared_from_this()
{
	shared_ptr<T> sp = _weak_this.lock();
	if (!sp) {
		throw bad_weak_ptr();
	}
	return sp;
}

template <typename T>
shared_ptr<const T> enable_shared_from_this<T>::shared_from_this() const
{
	shared_ptr<const T> sp = _weak_this.lock();
	if (!sp) {
		throw bad_weak_ptr();
	}
	return sp;
}

template <typename T>
weak_ptr<T> enable_shared_from_this<T>::weak_from_this() throw()
{
	return _weak_this;
}

template <typename T>
weak_ptr<const T> enable_shared_from_this<T>::weak_from_this() const throw()
{
	return _weak_this;
}

template <typename T>
void enable_shared_from_this<T>::_internal_accept_owner(
    const shared_ptr<T>& sp) const throw()
{
	if (_weak_this.expired()) {
		_weak_this = sp;
	}
}

/* shared_ptr helpers */

template <typename T, typename Y>
void
_shared_ptr::enable_shared_from_this(const shared_ptr<T>* owner,
                                     const Y* p,
                                     const enable_shared_from_this<Y>* base)
{
	if (base) {
		shared_ptr<Y> sp(*owner, const_cast<Y*>(p));
		const_cast<enable_shared_from_this<Y>*>(base)->_internal_accept_owner(
		    sp);
	}
}

template <typename T, typename Y>
void _shared_ptr::enable_shared_from_this(const shared_ptr<T>* /*owner*/,
                                          const Y* /*p*/,
                                          ...)
{}

/* shared_ptr private ctor used by weak_ptr::lock */

template <typename T>
shared_ptr<T>::shared_ptr(_shared_ptr::control_block_base* control,
                          element_type* ptr) throw()
    : _ptr(ptr),
      _control(control)
{}

/* make_shared / allocate_shared */

template <typename T>
shared_ptr<T> make_shared()
{
	return shared_ptr<T>(new T());
}

template <typename T, typename A0>
shared_ptr<T> make_shared(const A0& a0)
{
	return shared_ptr<T>(new T(a0));
}

template <typename T, typename A0, typename A1>
shared_ptr<T> make_shared(const A0& a0, const A1& a1)
{
	return shared_ptr<T>(new T(a0, a1));
}

template <typename T, typename A0, typename A1, typename A2>
shared_ptr<T> make_shared(const A0& a0, const A1& a1, const A2& a2)
{
	return shared_ptr<T>(new T(a0, a1, a2));
}

template <typename T, typename A0, typename A1, typename A2, typename A3>
shared_ptr<T>
make_shared(const A0& a0, const A1& a1, const A2& a2, const A3& a3)
{
	return shared_ptr<T>(new T(a0, a1, a2, a3));
}

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
                          const A4& a4)
{
	return shared_ptr<T>(new T(a0, a1, a2, a3, a4));
}

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
                          const A5& a5)
{
	return shared_ptr<T>(new T(a0, a1, a2, a3, a4, a5));
}

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
                          const A6& a6)
{
	return shared_ptr<T>(new T(a0, a1, a2, a3, a4, a5, a6));
}

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
                          const A7& a7)
{
	return shared_ptr<T>(new T(a0, a1, a2, a3, a4, a5, a6, a7));
}

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
                          const A8& a8)
{
	return shared_ptr<T>(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8));
}

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
                          const A9& a9)
{
	return shared_ptr<T>(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

template <typename T, typename Alloc>
shared_ptr<T> allocate_shared(const Alloc& alloc)
{
	typedef typename Alloc::template rebind<T>::other value_alloc;
	value_alloc a(alloc);
	T* storage = a.allocate(1);
	try {
		a.construct(storage, T());
	}
	catch (...) {
		a.deallocate(storage, 1);
		throw;
	}
	shared_ptr<T> result(storage,
	                     _shared_ptr::allocator_deleter<T, Alloc>(alloc, a));
	return result;
}

/* TODO: allocate_shared overloads */

/* swap */

template <typename T>
void swap(shared_ptr<T>& lhs, shared_ptr<T>& rhs) throw()
{
	lhs.swap(rhs);
}

template <typename T>
void swap(weak_ptr<T>& lhs, weak_ptr<T>& rhs) throw()
{
	lhs.swap(rhs);
}

/* comparison operators */

template <typename T1, typename T2>
bool operator==(const shared_ptr<T1>& lhs, const shared_ptr<T2>& rhs) throw()
{
	return lhs.get() == rhs.get();
}

/* TODO: other operators */

} // namespace ft

#endif // LIBFTPP_MEMORY_SHARED_PTR_TPP
