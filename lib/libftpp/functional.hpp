// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
// NOLINTBEGIN(misc-non-private-member-variables-in-classes)

#pragma once

#include <iostream>
#include <string>

namespace ft {
namespace functional {

template <typename T>
struct FromString {
	T operator()(const std::string& str);
};

template <typename T>
struct FromStringFmt {
	explicit FromStringFmt(std::ios::fmtflags fmt_);

	T operator()(const std::string& str);

	std::ios::fmtflags fmt;
};

} // namespace functional
} // namespace ft

#include "src/functional/FromString.tpp" // IWYU pragma: export

// NOLINTEND(misc-non-private-member-variables-in-classes)
// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
