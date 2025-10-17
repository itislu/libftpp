#pragma once
#ifndef LIBFTPP_MEMORY_SHARED_PTR_DETAIL_TPP
#	define LIBFTPP_MEMORY_SHARED_PTR_DETAIL_TPP

#	include "libftpp/memory/shared_ptr_detail.hpp"
#	include <new>

namespace ft {
namespace _shared_ptr {

/* rebind_allocator */

template <typename Alloc, typename T>
struct rebind_allocator {
	typedef typename Alloc::template rebind<T>::other type;
};

template <typename Alloc, typename T>
struct rebind_allocator<const Alloc, T> : rebind_allocator<Alloc, T> {};

template <typename Alloc, typename T>
struct rebind_allocator<Alloc&, T> : rebind_allocator<Alloc, T> {};

template <typename Alloc, typename T>
struct rebind_allocator<const Alloc&, T> : rebind_allocator<Alloc, T> {};

template <typename T>
struct rebind_allocator<std::allocator<void>, T> {
	typedef std::allocator<T> type;
};

template <typename T>
struct rebind_allocator<const std::allocator<void>, T> {
	typedef std::allocator<T> type;
};

template <typename T>
struct rebind_allocator<std::allocator<void>&, T> {
	typedef std::allocator<T> type;
};

template <typename T>
struct rebind_allocator<const std::allocator<void>&, T> {
	typedef std::allocator<T> type;
};

/* allocator_deleter */

template <typename T, typename Alloc>
class allocator_deleter {
public:
	explicit allocator_deleter(const Alloc& alloc)
	    : _alloc(alloc)
	{}

	void operator()(T* ptr)
	{
		Alloc alloc(_alloc);
		ptr->~T();
		alloc.deallocate(ptr, 1);
	}

private:
	Alloc _alloc;
};

/* control_block_base */

inline control_block_base::control_block_base() throw()
    : _use_count(1),
      _weak_count(1)
{}

inline control_block_base::~control_block_base() {}

inline void control_block_base::add_shared() throw() { ++_use_count; }

inline bool control_block_base::add_shared_if_nonzero() throw()
{
	if (_use_count == 0) {
		return false;
	}
	++_use_count;
	return true;
}

inline void control_block_base::release_shared() throw()
{
	if (--_use_count == 0) {
		dispose();
		release_weak();
	}
}

inline void control_block_base::add_weak() throw() { ++_weak_count; }

inline void control_block_base::release_weak() throw()
{
	if (--_weak_count == 0) {
		destroy_self();
	}
}

inline long control_block_base::use_count() const throw() { return _use_count; }

inline long control_block_base::weak_count() const throw()
{
	return _weak_count;
}

inline void*
control_block_base::get_deleter(const std::type_info& /*type*/) throw()
{
	return 0;
}

inline void control_block_base::destroy_self() throw() { delete this; }

/* control_block_ptr */

template <typename Ptr, typename Deleter, typename Alloc>
class control_block_ptr : public control_block_base {
private:
	typedef control_block_ptr<Ptr, Deleter, Alloc> self;
	typedef typename rebind_allocator<Alloc, self>::type allocator_type;

public:
	control_block_ptr(Ptr ptr, Deleter deleter, const Alloc& alloc)
	    : control_block_base(),
	      _ptr(ptr),
	      _deleter(deleter),
	      _allocator(alloc)
	{}

protected:
	virtual void dispose() throw() { _deleter(_ptr); }

	virtual void destroy_self() throw()
	{
		allocator_type alloc(_allocator);
		alloc.destroy(this);
		alloc.deallocate(this, 1);
	}

	virtual void* get_deleter(const std::type_info& type) throw()
	{
		if (type == typeid(Deleter)) {
			return &_deleter;
		}
		return 0;
	}

private:
	Ptr _ptr;
	Deleter _deleter;
	allocator_type _allocator;
};

} // namespace _shared_ptr
} // namespace ft

#endif // LIBFTPP_MEMORY_SHARED_PTR_DETAIL_TPP
