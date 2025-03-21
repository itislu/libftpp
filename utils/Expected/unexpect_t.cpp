#include "../Expected.hpp"

namespace utils {

unexpect_t::unexpect_t(int /*unused*/) throw() {}

const unexpect_t unexpect(0);

} // namespace utils
