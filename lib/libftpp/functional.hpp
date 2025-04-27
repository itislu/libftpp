// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
// NOLINTBEGIN(misc-non-private-member-variables-in-classes)

#pragma once

#include <iostream>
#include <ostream>

namespace ft {
namespace functional {

template <typename T>
struct Print {
	Print(std::ostream& os = std::cout);

	void operator()(const T& v);

	std::ostream& ostream;
};

} // namespace functional
} // namespace ft

// NOLINTEND(misc-non-private-member-variables-in-classes)
// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)

#include "src/functional/Print.tpp" // IWYU pragma: export
