#pragma once

#include <cstddef>
#include <string>

namespace ft {
namespace log {

const std::size_t label_width_text = 8;
const std::size_t label_width_colored = 25;

template <typename T>
std::string ok(const T& msg);

template <typename T>
std::string info(const T& msg);

template <typename T>
std::string warn(const T& msg);

template <typename T>
std::string error(const T& msg);

template <typename T>
std::string line(const T& msg);

} // namespace log
} // namespace ft

#include "src/log.tpp" // IWYU pragma: export
