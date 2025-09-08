#pragma once

#define HAS_MEMBER_FUNCTION_IMPL(RETURN_TYPE, NAME, ARGS_IN_PARENS)          \
	namespace detail_has_member_function_##NAME                              \
	{                                                                        \
                                                                             \
		/* 2nd param: member-function pointer non-type template parameter */ \
		template <typename T, RETURN_TYPE(T::*) ARGS_IN_PARENS>              \
		struct Sfinae {};                                                    \
                                                                             \
		template <typename T, typename = void>                               \
		struct Impl : ft::false_type {};                                     \
                                                                             \
		template <typename T>                                                \
		struct Impl<T, typename ft::voider<Sfinae<T, &T::NAME> >::type>      \
		    : ft::true_type {};                                              \
                                                                             \
	} /* namespace detail_has_member_function_##NAME */                      \
                                                                             \
	template <typename T>                                                    \
	struct has_member_function_##NAME                                        \
	    : detail_has_member_function_##NAME::Impl<T> {};
// NOLINTEND(bugprone-macro-parentheses)
