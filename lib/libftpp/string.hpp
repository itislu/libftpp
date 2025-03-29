#pragma once

#include <ios>
#include <string>

namespace ft {

bool starts_with(const std::string& str, const std::string& prefix);
bool starts_with(const std::string& str, char prefix);
bool starts_with(const std::string& str, unsigned char prefix);
bool ends_with(const std::string& str, const std::string& suffix);
bool ends_with(const std::string& str, char suffix);
bool ends_with(const std::string& str, unsigned char suffix);

template <typename T>
T from_string(const std::string& str);
template <typename T>
T from_string(const std::string& str, std::ios::fmtflags fmt);
template <>
inline bool from_string<bool>(const std::string& str);
template <>
inline float from_string<float>(const std::string& str);
template <>
inline double from_string<double>(const std::string& str);
template <>
inline long double from_string<long double>(const std::string& str);

template <typename T>
std::string to_string(T v, std::ios::fmtflags fmt = std::ios::fmtflags());
template <typename T>
std::string to_string(T* v, std::ios::fmtflags fmt = std::ios::fmtflags());
std::string to_string(bool v, std::ios::fmtflags fmt = std::ios::boolalpha);

std::string& trim(std::string& str);
std::string trim(const std::string& str);

} // namespace ft

#include "src/string/from_string.tpp" // IWYU pragma: export
#include "src/string/to_string.tpp"   // IWYU pragma: export
