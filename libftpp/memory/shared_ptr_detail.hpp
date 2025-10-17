#pragma once
#ifndef LIBFTPP_MEMORY_SHARED_PTR_DETAIL_HPP
#	define LIBFTPP_MEMORY_SHARED_PTR_DETAIL_HPP

#	include <cstddef>
#	include <memory>
#	include <typeinfo>

namespace ft {

template <typename T>
class shared_ptr;

template <typename T>
class enable_shared_from_this;

namespace _shared_ptr {

class control_block_base {
public:
	control_block_base() throw();
	virtual ~control_block_base();

	void add_shared() throw();
	bool add_shared_if_nonzero() throw();
	void release_shared() throw();
	void add_weak() throw();
	void release_weak() throw();
	long use_count() const throw();
	long weak_count() const throw();

	virtual void* get_deleter(const std::type_info& type) throw();

protected:
	virtual void dispose() throw() = 0;
	virtual void destroy_self() throw();

private:
	long _use_count;
	long _weak_count;
};

template <typename Ptr, typename Deleter, typename Alloc>
class control_block_ptr;

template <typename Alloc, typename T>
struct rebind_allocator;

template <typename T, typename Y>
void enable_shared_from_this(const shared_ptr<T>* owner,
                             Y* p,
                             const enable_shared_from_this<Y>* base);

template <typename T, typename Y>
void enable_shared_from_this(const shared_ptr<T>* owner,
                             Y* p,
                             const void* /*unused*/);

} // namespace _shared_ptr
} // namespace ft

#endif // LIBFTPP_MEMORY_SHARED_PTR_DETAIL_HPP
