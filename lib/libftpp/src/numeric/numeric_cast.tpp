#pragma once

#include "../../numeric.hpp"
#include <cmath>
#include <ios>
#include <limits>
#include <sstream>

namespace ft {

namespace _numeric_cast {
template <typename To, typename From>
static To int_to_int(From from);
template <typename To, typename From>
static To fp_to_int(From from);
template <typename To, typename From>
static To fp_to_fp(From from);
template <typename To, typename From>
static To int_to_fp(From from);
template <typename To, typename From>
static To try_cast(From from);
template <typename To, typename From>
struct TryCast;
} // namespace _numeric_cast

template <typename To, typename From>
To numeric_cast(From from)
{
	if (std::numeric_limits<To>::is_integer) {
		if (std::numeric_limits<From>::is_integer) {
			return _numeric_cast::int_to_int<To>(from);
		}
		return _numeric_cast::fp_to_int<To>(from);
	}
	if (std::numeric_limits<From>::is_integer) {
		return _numeric_cast::int_to_fp<To>(from);
	}
	return _numeric_cast::fp_to_fp<To>(from);
}

namespace _numeric_cast {

template <typename To, typename From>
static To int_to_int(From from)
{
	if (!std::numeric_limits<To>::is_signed && from < 0) {
		throw NegativeOverflow();
	}
	return TryCast<To, From>::cast(from);
}

template <typename To, typename From>
static To fp_to_int(From from)
{
	if (std::isnan(from)) {
		throw BadNumericCast();
	}
	if (!std::numeric_limits<To>::is_signed && from < 0) {
		throw NegativeOverflow();
	}
	return TryCast<To, From>::cast(from);
}

template <typename To, typename From>
static To fp_to_fp(From from)
{
	if (std::isinf(from) || std::isnan(from)) {
		return static_cast<To>(from);
	}
	return TryCast<To, From>::cast(from);
}

template <typename To, typename From>
static To int_to_fp(From from)
{
	return TryCast<To, From>::cast(from);
}

template <typename To, typename From>
struct TryCast {
	static To cast(From from)
	{
		To to;
		std::stringstream ss;
		ss << std::fixed << from;
		if (!(ss >> to)) {
			from < 0 ? throw NegativeOverflow() : throw PositiveOverflow();
		}
		return static_cast<To>(from);
	}
};

/**
 * Specializations for char and unsigned char because stringstream doesn't
 * interpret char as a number for insertion, and for extraction just takes the
 * first char literally.
 */

template <typename From>
struct TryCast<char, From> {
	static char cast(From from)
	{
		int to; // NOLINT(cppcoreguidelines-init-variables)
		std::stringstream ss;
		ss << std::fixed << from;
		if (!(ss >> to)) {
			from < 0 ? throw NegativeOverflow() : throw PositiveOverflow();
		}
		if (to > std::numeric_limits<char>::max()) {
			throw PositiveOverflow();
		}
		if (to < std::numeric_limits<char>::min()) {
			throw NegativeOverflow();
		}
		return static_cast<char>(from);
	}
};

template <typename From>
struct TryCast<unsigned char, From> {
	static unsigned char cast(From from)
	{
		unsigned int to; // NOLINT(cppcoreguidelines-init-variables)
		std::stringstream ss;
		ss << std::fixed << from;
		if (!(ss >> to)) {
			from < 0 ? throw NegativeOverflow() : throw PositiveOverflow();
		}
		if (to > std::numeric_limits<unsigned char>::max()) {
			throw PositiveOverflow();
		}
		return static_cast<unsigned char>(from);
	}
};

template <typename To>
struct TryCast<To, char> {
	static To cast(char from)
	{
		To to;
		std::stringstream ss;
		ss << static_cast<int>(from);
		if (!(ss >> to)) {
			from < 0 ? throw NegativeOverflow() : throw PositiveOverflow();
		}
		return static_cast<To>(from);
	}
};

template <typename To>
struct TryCast<To, unsigned char> {
	static To cast(unsigned char from)
	{
		To to;
		std::stringstream ss;
		ss << static_cast<unsigned int>(from);
		if (!(ss >> to)) {
			throw PositiveOverflow();
		}
		return static_cast<To>(from);
	}
};

} // namespace _numeric_cast

} // namespace ft
