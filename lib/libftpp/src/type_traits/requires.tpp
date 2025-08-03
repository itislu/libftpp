#pragma once

#include "../../functional.hpp"

namespace ft {
namespace _requires {

template <typename F>
struct unpack_return_type : function_traits<F>::template argument_type<> {};

} // namespace _requires
} // namespace ft
