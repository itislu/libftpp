#include "libftpp/assert.hpp"
#include "libftpp/movable.hpp"
#include "libftpp/preprocessor.hpp"
#include "libftpp/type_traits.hpp"
#include <type_traits>

#define VAR FT_APPEND_UNIQUE_NUM(var)

class Foo {};

FT_STATIC_ASSERT(!ft::is_rvalue_reference<int>::value);
FT_STATIC_ASSERT(!ft::is_rvalue_reference<int&>::value);
FT_STATIC_ASSERT(ft::is_rvalue_reference<ft::rvalue<int>&>::value);
FT_STATIC_ASSERT(!ft::is_rvalue_reference<ft::rvalue<int> >::value);
FT_STATIC_ASSERT(!ft::is_rvalue_reference<ft::rvalue<int&> >::value);
FT_STATIC_ASSERT(ft::is_rvalue_reference<volatile ft::rvalue<const int&>&>::value);
FT_STATIC_ASSERT(ft::_type_traits::is_rvalue<volatile ft::rvalue<const int&> >::value);


FT_STATIC_ASSERT(!ft::is_lvalue_reference<int>::value);
FT_STATIC_ASSERT(ft::is_lvalue_reference<int&>::value);
FT_STATIC_ASSERT(!ft::is_lvalue_reference<ft::rvalue<int>& >::value);
FT_STATIC_ASSERT(!ft::is_lvalue_reference<ft::rvalue<int> >::value);

// FT_STATIC_ASSERT((ft::is_same<ft::add_rvalue_reference<int>::type,
//                              ft::rvalue<int>&>::value));
// FT_STATIC_ASSERT(!(ft::is_same<ft::add_rvalue_reference<int&>::type,
//                              ft::rvalue<int&>&>::value));
// FT_STATIC_ASSERT((ft::is_same<ft::add_rvalue_reference<int&>::type,
//                              int&>::value));
// std::add_rvalue_reference<int&>::type VAR;
// FT_STATIC_ASSERT((!ft::is_same<std::add_rvalue_reference<int&>::type,
//                              int&&>::value));

FT_STATIC_ASSERT(ft::is_lvalue_reference<const int&>::value);

// remove_reference
FT_STATIC_ASSERT((ft::is_same<ft::remove_reference<const int&>::type, const int>::value));
FT_STATIC_ASSERT((ft::is_same<ft::remove_reference<ft::rvalue<int>&>::type, int>::value));
// FT_STATIC_ASSERT((ft::is_same<ft::remove_reference<const ft::rvalue<int>&>::type, int>::value));
ft::remove_reference<const ft::rvalue<int>&>::type VAR;

// std::remove_reference<const int&>::type VAR;
// std::remove_reference<int&&>::type VAR;
// std::remove_reference<const int&&>::type VAR;
// std::remove_reference<volatile int&&>::type VAR;
// std::remove_reference<const volatile int&&>::type VAR;

ft::remove_reference<const ft::rvalue<long>&>::type VAR;
ft::remove_reference<const ft::rvalue<long&>&>::type VAR;
ft::remove_reference<const ft::rvalue<volatile long&>&>::type VAR;
ft::remove_reference<const ft::rvalue<ft::rvalue<volatile long>&>&>::type VAR;
ft::remove_reference<const ft::rvalue<ft::rvalue<volatile long&> >&>::type VAR;
ft::remove_reference<const ft::rvalue<ft::rvalue<volatile long&>&>&>::type VAR;

// std::add_lvalue_reference<const long&>::type VAR;
// std::add_lvalue_reference<const long&&>::type VAR;
// ft::add_lvalue_reference<long& >::type VAR;
// ft::add_lvalue_reference<ft::rvalue<long&> >::type VAR;
// ft::add_lvalue_reference<ft::rvalue<long&>& >::type VAR;

// ft::add_rvalue_reference<long >::type VAR;
// ft::add_rvalue_reference<const long >::type VAR;
// ft::add_rvalue_reference<long& >::type VAR;
// ft::add_rvalue_reference<const ft::rvalue< Foo&> >::type VAR;
// ft::add_rvalue_reference<const ft::rvalue< Foo&>& >::type VAR;
// ft::add_rvalue_reference<const ft::rvalue< ft::rvalue<Foo&> >& >::type VAR;
// ft::add_rvalue_reference<ft::rvalue<Foo> >::type VAR;
// ft::add_rvalue_reference<ft::rvalue<Foo>& >::type VAR;
// ft::add_rvalue_reference<const ft::rvalue<Foo> >::type VAR;
// ft::add_rvalue_reference<const ft::rvalue<Foo>& >::type VAR;
// ft::add_rvalue_reference<const ft::rvalue< long> >::type VAR;
ft::add_rvalue_reference<long >::type VAR;
ft::add_rvalue_reference<const long >::type VAR;
ft::add_rvalue_reference<volatile long >::type VAR;
ft::add_rvalue_reference<const volatile long >::type VAR;
ft::add_rvalue_reference<ft::rvalue<const long> >::type VAR;
ft::add_rvalue_reference<const ft::rvalue<volatile long> >::type VAR;
ft::add_rvalue_reference<const ft::rvalue< long&>&>::type VAR;
ft::add_rvalue_reference<const ft::rvalue<volatile long&> >::type VAR;
ft::add_rvalue_reference<const ft::rvalue< long&>& >::type VAR;
ft::add_rvalue_reference<ft::rvalue<void> >::type VAR;
ft::add_rvalue_reference<ft::rvalue<long>& >::type VAR;
ft::add_rvalue_reference<ft::rvalue<void>& >::type VAR;
