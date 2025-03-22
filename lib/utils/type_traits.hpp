#pragma once

namespace utils {

template <bool B, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
	typedef T type;
};

/**
 * Generates type traits that check if a class has a specific method.
 * The generated type traits are named has_<method_name>.
 */
#define HAS_METHOD(name, signature)                   \
	template <typename T>                             \
	struct has_##name {                               \
	private:                                          \
		typedef char yes[1];                          \
		typedef char no[2];                           \
                                                      \
		template <typename U, signature>              \
		struct SFINAE {};                             \
                                                      \
		template <typename U>                         \
		static yes& test(SFINAE<U, &U::name>*);       \
		template <typename U>                         \
		static no& test(...);                         \
                                                      \
	public:                                           \
		enum {                                        \
			value = sizeof(test<T>(0)) == sizeof(yes) \
		};                                            \
	};

HAS_METHOD(swap, void (U::*)(U&))

#undef HAS_METHOD

} // namespace utils
