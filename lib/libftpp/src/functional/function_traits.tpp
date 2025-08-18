#pragma once

#include "../../assert.hpp"
#include "../../functional.hpp"
#include "../../type_traits.hpp"

namespace ft {

namespace _function_traits {
template <typename ReducedFunc,
          unsigned Arity,
          typename LastArg,
          unsigned N,
          bool IsLast = (Arity > 0 && N == Arity - 1) || (Arity == 0 && N == 0)>
struct argument_type;
} // namespace _function_traits

template <typename F>
struct function_traits {
	STATIC_ASSERT( // Only functions with up to 10 parameters supported
	    !is_function<F>::value);
};

template <typename R>
struct function_traits<R()> {
	static const unsigned arity = 0;
	typedef R result_type;
	template <unsigned N = 0>
	struct argument_type : _function_traits::argument_type<R(), 0, void, N> {};
};

template <typename R>
struct function_traits<R(...)> : function_traits<R()> {};

// NOLINTBEGIN(bugprone-macro-parentheses)
#define FUNCTION_TRAITS_IMPL(ARITY, LAST_ARG, REDUCED_FUNC_SIG)       \
	static const unsigned arity = ARITY;                              \
	typedef R result_type;                                            \
	template <unsigned N = 0>                                         \
	struct argument_type                                              \
	    : _function_traits::                                          \
	          argument_type<REDUCED_FUNC_SIG, ARITY, LAST_ARG, N> {};

namespace _function_traits {

/* Recurse until Nth arg is last. */
template <
    typename ReducedFunc,
    unsigned Arity,
    typename LastArg,
    unsigned N,
    bool IsLast /*= (Arity > 0 && N == Arity - 1) || (Arity == 0 && N == 0)*/>
struct argument_type : function_traits<ReducedFunc>::template argument_type<N> {
};

template <typename ReducedFunc, unsigned Arity, typename LastArg, unsigned N>
struct argument_type<ReducedFunc, Arity, LastArg, N, true>
    : type_identity<LastArg> {};

/* N >= original arity */
template <typename ReducedFunc, typename LastArg, unsigned N>
struct argument_type<ReducedFunc, 0, LastArg, N, false> {};

} // namespace _function_traits

/**
 * Specialize also for "Abominable Function Types":
 * https://www.open-std.org/JTC1/SC22/WG21/docs/papers/2015/p0172r0.html
 */
#define FUNCTION_TRAITS_SPECIALIZATIONS(FUNC_SIG, IMPL_ARGS)           \
	TEMPLATE_SIG                                                       \
	struct function_traits<FUNC_SIG> {                                 \
		FUNCTION_TRAITS_IMPL IMPL_ARGS /* Uses parens of IMPL_ARGS. */ \
	};                                                                 \
	TEMPLATE_SIG                                                       \
	struct function_traits<FUNC_SIG const> {                           \
		FUNCTION_TRAITS_IMPL IMPL_ARGS                                 \
	};                                                                 \
	TEMPLATE_SIG                                                       \
	struct function_traits<FUNC_SIG volatile> {                        \
		FUNCTION_TRAITS_IMPL IMPL_ARGS                                 \
	};                                                                 \
	TEMPLATE_SIG                                                       \
	struct function_traits<FUNC_SIG const volatile> {                  \
		FUNCTION_TRAITS_IMPL IMPL_ARGS                                 \
	};
// NOLINTEND(bugprone-macro-parentheses)

/* Define TEMPLATE_SIG this way because parens would not be discardable. */
#define TEMPLATE_SIG template <typename R, typename A0>
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0), (1, A0, R()))
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, ...), (1, A0, R(...)))
#undef TEMPLATE_SIG

#define TEMPLATE_SIG template <typename R, typename A0, typename A1>
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, A1), (2, A1, R(A0)))
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, A1, ...), (2, A1, R(A0, ...)))
#undef TEMPLATE_SIG

#define TEMPLATE_SIG                                             \
	template <typename R, typename A0, typename A1, typename A2>
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, A1, A2), (3, A2, R(A0, A1)))
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, A1, A2, ...), (3, A2, R(A0, A1, ...)))
#undef TEMPLATE_SIG

#define TEMPLATE_SIG                                                          \
	template <typename R, typename A0, typename A1, typename A2, typename A3>
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, A1, A2, A3), (4, A3, R(A0, A1, A2)))
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, A1, A2, A3, ...),
                                (4, A3, R(A0, A1, A2, ...)))
#undef TEMPLATE_SIG

#define TEMPLATE_SIG       \
	template <typename R,  \
	          typename A0, \
	          typename A1, \
	          typename A2, \
	          typename A3, \
	          typename A4>
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, A1, A2, A3, A4),
                                (5, A4, R(A0, A1, A2, A3)))
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, A1, A2, A3, A4, ...),
                                (5, A4, R(A0, A1, A2, A3, ...)))
#undef TEMPLATE_SIG

#define TEMPLATE_SIG       \
	template <typename R,  \
	          typename A0, \
	          typename A1, \
	          typename A2, \
	          typename A3, \
	          typename A4, \
	          typename A5>
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, A1, A2, A3, A4, A5),
                                (6, A5, R(A0, A1, A2, A3, A4)))
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, A1, A2, A3, A4, A5, ...),
                                (6, A5, R(A0, A1, A2, A3, A4, ...)))
#undef TEMPLATE_SIG

#define TEMPLATE_SIG       \
	template <typename R,  \
	          typename A0, \
	          typename A1, \
	          typename A2, \
	          typename A3, \
	          typename A4, \
	          typename A5, \
	          typename A6>
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, A1, A2, A3, A4, A5, A6),
                                (7, A6, R(A0, A1, A2, A3, A4, A5)))
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, A1, A2, A3, A4, A5, A6, ...),
                                (7, A6, R(A0, A1, A2, A3, A4, A5, ...)))
#undef TEMPLATE_SIG

#define TEMPLATE_SIG       \
	template <typename R,  \
	          typename A0, \
	          typename A1, \
	          typename A2, \
	          typename A3, \
	          typename A4, \
	          typename A5, \
	          typename A6, \
	          typename A7>
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, A1, A2, A3, A4, A5, A6, A7),
                                (8, A7, R(A0, A1, A2, A3, A4, A5, A6)))
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, A1, A2, A3, A4, A5, A6, A7, ...),
                                (8, A7, R(A0, A1, A2, A3, A4, A5, A6, ...)))
#undef TEMPLATE_SIG

#define TEMPLATE_SIG       \
	template <typename R,  \
	          typename A0, \
	          typename A1, \
	          typename A2, \
	          typename A3, \
	          typename A4, \
	          typename A5, \
	          typename A6, \
	          typename A7, \
	          typename A8>
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, A1, A2, A3, A4, A5, A6, A7, A8),
                                (9, A8, R(A0, A1, A2, A3, A4, A5, A6, A7)))
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, A1, A2, A3, A4, A5, A6, A7, A8, ...),
                                (9, A8, R(A0, A1, A2, A3, A4, A5, A6, A7, ...)))
#undef TEMPLATE_SIG

#define TEMPLATE_SIG       \
	template <typename R,  \
	          typename A0, \
	          typename A1, \
	          typename A2, \
	          typename A3, \
	          typename A4, \
	          typename A5, \
	          typename A6, \
	          typename A7, \
	          typename A8, \
	          typename A9>
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9),
                                (10, A9, R(A0, A1, A2, A3, A4, A5, A6, A7, A8)))
FUNCTION_TRAITS_SPECIALIZATIONS(R(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, ...),
                                (10,
                                 A9,
                                 R(A0, A1, A2, A3, A4, A5, A6, A7, A8, ...)))
#undef TEMPLATE_SIG

#undef FUNCTION_TRAITS_SPECIALIZATIONS
#undef FUNCTION_TRAITS_IMPL

} // namespace ft
