#pragma once

#include "../../functional.hpp"
#include "../../type_traits.hpp"
#include "_type_traits.hpp"

namespace ft {
namespace _requires {

// NOLINTBEGIN(readability-magic-numbers)
template <typename F>
struct Impl
    : conjunction<
          typename _type_traits::type_or_null<
              typename function_traits<F>::template argument_type<0> >::type,
          typename _type_traits::type_or_null<
              typename function_traits<F>::template argument_type<1> >::type,
          typename _type_traits::type_or_null<
              typename function_traits<F>::template argument_type<2> >::type,
          typename _type_traits::type_or_null<
              typename function_traits<F>::template argument_type<3> >::type,
          typename _type_traits::type_or_null<
              typename function_traits<F>::template argument_type<4> >::type,
          typename _type_traits::type_or_null<
              typename function_traits<F>::template argument_type<5> >::type,
          typename _type_traits::type_or_null<
              typename function_traits<F>::template argument_type<6> >::type,
          typename _type_traits::type_or_null<
              typename function_traits<F>::template argument_type<7> >::type,
          typename _type_traits::type_or_null<
              typename function_traits<F>::template argument_type<8> >::type,
          typename _type_traits::type_or_null<
              typename function_traits<F>::template argument_type<9> >::type> {
};
// NOLINTEND(readability-magic-numbers)

template <typename F>
struct GetReturnType : function_traits<F>::template argument_type<> {
};

} // namespace _requires
} // namespace ft
