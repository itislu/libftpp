#pragma once

#include "../../SafeBool.hpp"
#include "SafeBoolBase.hpp"
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
