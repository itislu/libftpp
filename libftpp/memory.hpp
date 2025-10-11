#pragma once
#ifndef LIBFTPP_MEMORY_HPP
#	define LIBFTPP_MEMORY_HPP

#	include "libftpp/safe_bool.hpp"
#	include "libftpp/type_traits.hpp"
#	include <ostream>

namespace ft {

template <typename T>
struct default_delete {
	default_delete() throw();
	// TODO: typename enable_if<is_convertible<U*, T*>::value>::type
	template <typename U>
	default_delete(const default_delete<U>& d) throw();

	void operator()(T* ptr) const;
};

template <typename T>
struct default_delete<T[]> {
public:
	default_delete() throw();
	// TODO: typename enable_if<is_convertible<U (*)[], T (*)[]>::value>::type
	template <typename U>
	default_delete(const default_delete<U[]>& d) throw();

	template <typename U>
	// TODO: typename enable_if<is_convertible<U (*)[], T (*)[]>::value>::type
	void operator()(U* ptr) const;
};

/**
 * @note Don't create a unique_ptr from a pointer unless you know where the
 * pointer came from and that it needs an owner. This prevents double frees.
 */
// TODO Mention that reset(release()) has to be used instead of move operators.
template <typename T, typename Deleter = default_delete<T> >
class unique_ptr : public ft::safe_bool<unique_ptr<T, Deleter> > {
public:
	// TODO std::remove_reference<Deleter>::type::pointer if that type exists,
	// otherwise T*. Must satisfy NullablePointer
	typedef T* pointer;
	typedef T element_type;
	typedef Deleter deleter_type;

	unique_ptr() throw();
	explicit unique_ptr(pointer p) throw();
	// TODO Conditional overloads.
	unique_ptr(pointer p, const Deleter& d) throw();
	~unique_ptr();

	pointer release() throw();
	void reset(pointer ptr = pointer()) throw();
	void swap(unique_ptr& other) throw();

	/**
	 * @note Make sure the returned raw pointer is no longer in use after the
	 * unique_ptr goes out of scope.
	 */
	pointer get() const throw();
	Deleter& get_deleter() throw();
	const Deleter& get_deleter() const throw();
	bool boolean_test() const throw();

	typename ft::add_lvalue_reference<T>::type operator*() const;
	pointer operator->() const throw();

private:
	// Disable copy semantics.
	unique_ptr(const unique_ptr&);
	unique_ptr& operator=(const unique_ptr&);

	pointer _p;
	Deleter _d;
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

template <typename CharT, typename Traits, typename Y, typename D>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const unique_ptr<Y, D>& p);

template <typename T, typename D>
void swap(unique_ptr<T, D>& lhs, unique_ptr<T, D>& rhs) throw();

// TODO
template <typename T, typename Deleter>
class unique_ptr<T[], Deleter> {
public:
private:
};

} // namespace ft

#	include "libftpp/memory/default_delete.tpp" // IWYU pragma: export
#	include "libftpp/memory/unique_ptr.tpp"     // IWYU pragma: export

#endif // LIBFTPP_MEMORY_HPP
