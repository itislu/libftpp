#pragma once

#include "SafeBoolBase.hpp"
#include "libftpp/SafeBool.hpp"
#include <cstddef>

namespace ft {

inline SafeBool<void>::operator safe_bool_t() const
{
	return boolean_test()
	           ? &SafeBoolBase::this_type_does_not_support_comparisons
	           : NULL;
}

inline SafeBool<void>::SafeBool() {}

inline SafeBool<void>::~SafeBool() {}

} // namespace ft
