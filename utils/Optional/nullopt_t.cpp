#include "../Optional.hpp"

namespace utils {

nullopt_t::nullopt_t(int /*unused*/) throw() {}

const nullopt_t nullopt(0);

} // namespace utils
