#pragma once

#include "../../Expected.hpp"
#include "../../numeric.hpp"
#include <cmath>
#include <ios>
#include <limits>
#include <new>
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
struct Impl;
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

template <typename To, typename From>
ft::Expected<To, ft::NumericCastException>
numeric_cast(From from, std::nothrow_t /*unused*/)
{
	try {
		return numeric_cast<To>(from);
	}
	catch (const NumericCastException& e) {
		return ft::Unexpected<NumericCastException>(e);
	}
}

namespace _numeric_cast {

template <typename To, typename From>
static To int_to_int(From from)
{
	if (!std::numeric_limits<To>::is_signed && from < 0) {
		throw NumericCastNegativeOverflowException();
	}
	return Impl<To, From>::try_cast(from);
}

template <typename To, typename From>
static To fp_to_int(From from)
{
	if (std::isnan(from)) {
		throw NumericCastException();
	}
	if (!std::numeric_limits<To>::is_signed && from < 0) {
		throw NumericCastNegativeOverflowException();
	}
	return Impl<To, From>::try_cast(from);
}

template <typename To, typename From>
static To fp_to_fp(From from)
{
	if (std::isinf(from) || std::isnan(from)) {
		return static_cast<To>(from);
	}
	return Impl<To, From>::try_cast(from);
}

template <typename To, typename From>
static To int_to_fp(From from)
{
	return Impl<To, From>::try_cast(from);
}

template <typename To, typename From>
struct Impl {
	static To try_cast(From from)
	{
		To to;
		std::stringstream ss;
		ss << std::fixed << from;
		if (!(ss >> to)) {
			from < 0 ? throw NumericCastNegativeOverflowException()
			         : throw NumericCastPositiveOverflowException();
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
struct Impl<char, From> {
	static char try_cast(From from)
	{
		int to; // NOLINT(cppcoreguidelines-init-variables)
		std::stringstream ss;
		ss << std::fixed << from;
		if (!(ss >> to)) {
			from < 0 ? throw NumericCastNegativeOverflowException()
			         : throw NumericCastPositiveOverflowException();
		}
		if (to > std::numeric_limits<char>::max()) {
			throw NumericCastPositiveOverflowException();
		}
		if (to < std::numeric_limits<char>::min()) {
			throw NumericCastNegativeOverflowException();
		}
		return static_cast<char>(from);
	}
};

template <typename From>
struct Impl<unsigned char, From> {
	static unsigned char try_cast(From from)
	{
		unsigned int to; // NOLINT(cppcoreguidelines-init-variables)
		std::stringstream ss;
		ss << std::fixed << from;
		if (!(ss >> to)) {
			from < 0 ? throw NumericCastNegativeOverflowException()
			         : throw NumericCastPositiveOverflowException();
		}
		if (to > std::numeric_limits<unsigned char>::max()) {
			throw NumericCastPositiveOverflowException();
		}
		return static_cast<unsigned char>(from);
	}
};

template <typename To>
struct Impl<To, char> {
	static To try_cast(char from)
	{
		To to;
		std::stringstream ss;
		ss << static_cast<int>(from);
		if (!(ss >> to)) {
			from < 0 ? throw NumericCastNegativeOverflowException()
			         : throw NumericCastPositiveOverflowException();
		}
		return static_cast<To>(from);
	}
};

template <typename To>
struct Impl<To, unsigned char> {
	static To try_cast(unsigned char from)
	{
		To to;
		std::stringstream ss;
		ss << static_cast<unsigned int>(from);
		if (!(ss >> to)) {
			throw NumericCastPositiveOverflowException();
		}
		return static_cast<To>(from);
	}
};

} // namespace _numeric_cast

} // namespace ft
