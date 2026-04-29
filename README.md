# libftpp

A C++98 library reimplementing modern C++ standard library features – from C++11 all the way up to C++26.

Everything lives in the `ft::` namespace and mirrors `std::` interfaces as closely as C++98 allows.
Public macros always start with `FT_`.

### But why?

My goal is to gain a deep understanding of how the standard library works behind the scenes. Doing it in C++98 originated out of necessity because my school ([42](https://42.fr/en/homepage/)) only allowed C++98 for our first projects in C++ (including an [HTTP/1.1 webserver](https://github.com/itislu/42-Webserv)). 

The things I chose to implement first were therefore mostly driven by what I could immediately use to make my code nicer and safer while learning the language in this constrained environment.

### Was it worth it?

I learned to see the positives in this ordeal as I discovered the intricacies and quirks of C++, and I gained a deep appreciation for the newer standards, and compilers. How compilers parse and optimize some of this C++98 mess is mind-blowing to me (looking at you [`ft::is_convertible`](libftpp/type_traits/type_traits.tpp) and [`ft::shared_ptr` constructors](libftpp/memory/shared_ptr.tpp)).

I also discovered multiple bugs in `gcc` and `clang` along the way – luckily they all got fixed already in newer versions. But finding those bug reports and reading up on how they got fixed was a great learning experience. I left comments with links throughout the code wherever I encountered some.

Now it has turned into a fun challenge that often requires creative solutions – like [custom move semantics](libftpp/movable.hpp). And wow is [Boost](https://www.boost.org/) impressive, doing all this so many years ago and so much better than I could come up with.

### Why the name?

The first project I did at 42 was a C library reimplementing some C features called [libft](https://github.com/itislu/42-Libft) (**lib**-**f**ourty-**t**wo). I used this library throughout my studies there because we were not allowed to use most of the standard library. What we wanted to use we had to implement ourselves.
I kept the name for this project as a nod to that.

---

## Table of Contents

- [Highlights](#highlights)
  - [Move Semantics & Rvalue Emulation](#move-semantics--rvalue-emulation)
  - [Type Traits](#type-traits)
  - [FT\_REQUIRES – requires Clause Emulation](#ft_requires--requires-clause-emulation)
  - [Smart Pointers](#smart-pointers)
  - [Optional & Expected](#optional--expected)
- [Full Header Reference](#full-header-reference)
  - [memory](#memory)
  - [movable](#movable)
  - [type\_traits](#type_traits)
  - [optional](#optional)
  - [expected](#expected)
  - [utility](#utility)
  - [algorithm](#algorithm)
  - [iterator](#iterator)
  - [array](#array)
  - [functional](#functional)
  - [numeric](#numeric)
  - [string](#string)
  - [exception](#exception)
  - [safe\_bool](#safe_bool)
  - [assert](#assert)
  - [source\_location](#source_location)
  - [operators](#operators)
  - [format](#format)
  - [ctype](#ctype)
  - [random](#random)
  - [preprocessor](#preprocessor)
- [Roadmap](#roadmap)
- [A Note on Testing](#a-note-on-testing)
- [Building](#building)

---

## Highlights

### Move Semantics & Rvalue Emulation

C++98 only has lvalue references (`&`) – rvalue references (`&&`) were introduced in C++11, along with `std::move`. This library implements a [Boost-inspired move emulation system](libftpp/movable.hpp) that enables move-only and move-aware types in C++98.

The core idea: [`ft::rvalue<T>`](libftpp/movable.hpp) is a type that only rvalues (temporaries or explicit [`ft::move()`](libftpp/utility.hpp) casts) can bind to, exploiting how C++98 overload resolution works with derived-to-base conversions. Three macros configure a class for move semantics:

| Macro | Purpose |
|-------|---------|
| `FT_MOVABLE_BUT_NOT_COPYABLE(T)` | Move-only type (like `std::unique_ptr`) |
| `FT_COPYABLE_AND_MOVABLE(T)` | Copyable + movable with separate operators |
| `FT_COPYABLE_AND_MOVABLE_SWAP(T)` | Copyable + movable using copy-and-swap idiom |

[`ft::move()`](libftpp/utility/move.tpp) casts an lvalue to `ft::rvalue<T>&`, and [`ft::forward<T>()`](libftpp/utility/forward.tpp) conditionally casts to an lvalue or rvalue emulation, providing reference-collapsing emulation.

### Type Traits

A comprehensive [`<type_traits>`](libftpp/type_traits.hpp)-style header, built entirely with C++98 template metaprogramming – `sizeof` tricks, SFINAE, and partial specializations. ([implementation](libftpp/type_traits/type_traits.tpp))

Includes:
- **Unary type traits** – `is_void`, `is_integral`, `is_floating_point`, `is_array`, `is_function`, `is_pointer`, `is_lvalue_reference`, `is_rvalue_reference`, `is_arithmetic`, `is_object`, `is_reference`, `is_const`, `is_volatile`, `is_abstract`, `is_signed`, `is_unsigned`, `is_bounded_array`, `is_unbounded_array`
- **Type relationships** – `is_same`, `is_convertible`
- **Type transformations** – `remove_cv`/`add_cv`, `remove_const`/`add_const`, `remove_volatile`/`add_volatile`, `remove_reference`, `add_lvalue_reference`/`add_rvalue_reference`, `remove_extent`/`remove_all_extents`, `remove_pointer`/`add_pointer`, `remove_cvref`, `enable_if`, `conditional`, `voider` (C++17's `void_t`)
- **Logical operations** – `conjunction`, `disjunction`, `negation` (emulated with up to 10 template parameters in place of variadic templates)
- **Property queries** – `rank`, `extent`
- **Base types** – `integral_constant`, `bool_constant`, `true_type`, `false_type`, `type_identity`
- **Custom traits** – `is_class_or_union`, `is_complete`, `is_const_lvalue_reference`, `is_nonconst_lvalue_reference`, `is_returnable`, `has_member_function_swap` (with a macro `FT_HAS_MEMBER_FUNCTION` to generate member function detection traits)

### FT_REQUIRES – requires Clause Emulation

A [macro](libftpp/type_traits/requires.ipp) that emulates C++20's `requires` clauses, making SFINAE-constrained function signatures more readable:

```cpp
// Instead of this:
template <typename T>
typename ft::enable_if<!ft::is_array<T>::value, ft::unique_ptr<T> >::type
make_unique();

// Write this:
template <typename T>
FT_REQUIRES(!ft::is_array<T>::value)
(ft::unique_ptr<T>) make_unique();
```

### Smart Pointers

**[`ft::unique_ptr`](libftpp/memory.hpp)** – Full implementation for both [single objects](libftpp/memory/unique_ptr.tpp) and [arrays](libftpp/memory/unique_ptr_array.tpp), including custom deleters, `make_unique`, `make_unique_for_overwrite`, and full comparison operator sets. Uses the custom move semantics to enforce exclusive ownership. Supports constructing from `std::auto_ptr` when compiling under C++98.

**[`ft::shared_ptr`](libftpp/memory/shared_ptr.tpp)** – Reference-counted shared ownership with type-erased deleters, aliasing constructors, pointer casts (`static_pointer_cast`, `dynamic_pointer_cast`, `const_pointer_cast`, `reinterpret_pointer_cast`), `owner_less`, `owner_equal`, and `get_deleter`. Supports array types and constructing from both `ft::unique_ptr` and `std::auto_ptr`.

Both smart pointer classes use [`ft::safe_bool`](libftpp/safe_bool.hpp) for safe boolean conversions and [`FT_REQUIRES`](libftpp/type_traits/requires.ipp)/`enable_if` to constrain constructors and conversions – resulting in some seriously dense template signatures.

Also provides [`ft::default_delete`](libftpp/memory/default_delete.tpp) (with array specialization), `ft::make_shared` / `ft::make_shared_for_overwrite`, and [`ft::addressof`](libftpp/memory/addressof.tpp).

### Optional & Expected

**[`ft::optional<T>`](libftpp/optional.hpp)** – A C++17-style optional type with `nullopt`, `has_value()`, `value()`, `value_or()`, monadic operations (`and_then`, `transform`, `or_else`), and full comparison operators. Enforces constraints at compile time via [`FT_STATIC_ASSERT`](libftpp/assert.hpp) (no references, no arrays, no functions, no void, no `nullopt_t`).

**[`ft::expected<T, E>`](libftpp/expected.hpp)** – A C++23-style expected type for error handling without exceptions, with `unexpected<E>`, `unexpect_t`, `has_value()`, `value()`, `error()`, `value_or()`, `error_or()`, and monadic operations (`and_then`, `transform`, `or_else`, `transform_error`). Includes a `void` specialization for operations that can fail but don't return a value. Throws `ft::bad_expected_access<E>` on invalid access.

> **Note:** Both currently use heap allocation internally. A future rework using discriminated union storage is planned (see [Roadmap](#roadmap)). The main challenge there is memory alignment.

---

## Full Header Reference

### memory

[`#include "libftpp/memory.hpp"`](libftpp/memory.hpp)

| Component | Standard | Description |
|-----------|----------|-------------|
| `ft::unique_ptr<T, Deleter>` | C++11 | Exclusive-ownership smart pointer (single object + array specialization) |
| `ft::make_unique` | C++14 | Factory function (up to 10 args, emulating variadic templates) |
| `ft::make_unique_for_overwrite` | C++20 | Default-initializing factory |
| `ft::shared_ptr<T>` | C++11 | Reference-counted shared-ownership smart pointer |
| `ft::make_shared` | C++11 | Factory function (up to 10 args + array overloads) |
| `ft::make_shared_for_overwrite` | C++20 | Default-initializing factory |
| `ft::default_delete<T>` | C++11 | Default deleter (single object + array specialization) |
| `ft::static_pointer_cast` | C++11 | `static_cast` for `shared_ptr` |
| `ft::dynamic_pointer_cast` | C++11 | `dynamic_cast` for `shared_ptr` |
| `ft::const_pointer_cast` | C++11 | `const_cast` for `shared_ptr` |
| `ft::reinterpret_pointer_cast` | C++17 | `reinterpret_cast` for `shared_ptr` |
| `ft::get_deleter` | C++11 | Retrieve deleter from `shared_ptr` |
| `ft::owner_less` | C++11 | Owner-based ordering for `shared_ptr` |
| `ft::owner_equal` | C++26 | Owner-based equality for `shared_ptr` |
| `ft::addressof` | C++11 | Obtains actual address even if `operator&` is overloaded |

---

### movable

[`#include "libftpp/movable.hpp"`](libftpp/movable.hpp)

| Component | Description |
|-----------|-------------|
| `ft::rvalue<T>` | Rvalue reference emulation type |
| `ft::copy_assign_ref<T>` | Copy assignment wrapper for correct overload priority |
| `FT_MOVABLE_BUT_NOT_COPYABLE(T)` | Make a type move-only |
| `FT_COPYABLE_AND_MOVABLE(T)` | Make a type copyable and movable |
| `FT_COPYABLE_AND_MOVABLE_SWAP(T)` | Copyable and movable using copy-and-swap |

---

### type_traits

[`#include "libftpp/type_traits.hpp"`](libftpp/type_traits.hpp)

See [Type Traits](#type-traits) for the full list.

Also provides:
- `FT_REQUIRES(expr)` – requires clause emulation
- `FT_HAS_MEMBER_FUNCTION(ret, name, args)` – generate traits detecting public member functions
- `ft::yes_type` / `ft::no_type` – helper types for SFINAE `sizeof` tricks

---

### optional

[`#include "libftpp/optional.hpp"`](libftpp/optional.hpp)

| Component | Standard | Description |
|-----------|----------|-------------|
| `ft::optional<T>` | C++17 | Optional value container |
| `ft::nullopt_t` / `ft::nullopt` | C++17 | Empty optional sentinel |
| `ft::bad_optional_access` | C++17 | Exception for invalid access |
| `ft::make_optional` | C++17 | Factory function |

---

### expected

[`#include "libftpp/expected.hpp"`](libftpp/expected.hpp)

| Component | Standard | Description |
|-----------|----------|-------------|
| `ft::expected<T, E>` | C++23 | Value-or-error container |
| `ft::expected<void, E>` | C++23 | Void specialization |
| `ft::unexpected<E>` | C++23 | Error wrapper |
| `ft::unexpect_t` / `ft::unexpect` | C++23 | In-place error construction tag |
| `ft::bad_expected_access<E>` | C++23 | Exception for invalid access |

---

### utility

[`#include "libftpp/utility.hpp"`](libftpp/utility.hpp)

| Component | Standard | Description |
|-----------|----------|-------------|
| `ft::move` | C++11 | Cast to rvalue reference emulation |
| `ft::forward` | C++11 | Perfect forwarding (reference collapsing emulation) |
| `ft::nullptr_t` / `FT_NULLPTR` | C++11 | `nullptr` emulation as a class + macro |
| `ft::demangle` | — | Demangle `typeid` names (non-standard) |
| `FT_UNREACHABLE()` | C++23 | Marks unreachable code paths |
| `FT_COUNTOF(arr)` | — | Type-safe compile-time array length |

---

### algorithm

[`#include "libftpp/algorithm.hpp"`](libftpp/algorithm.hpp)

| Component | Standard | Description |
|-----------|----------|-------------|
| `ft::contains` | C++23 | Range and iterator search |
| `ft::contains_subrange` | C++23 | Subrange search |
| `ft::copy_if` | C++11 | Conditional copy |
| `ft::copy_n` | C++11 | Copy N elements |
| `ft::equal` | C++14 | Four-iterator overload for safe comparison |
| `ft::is_sorted` / `ft::is_sorted_until` | C++11 | Sorted range checks |
| `ft::lower_bound` / `ft::upper_bound` | — | Optimized overloads taking a precomputed size (avoids extra iteration for non-random-access iterators) |
| `ft::equal_range` / `ft::binary_search` | — | Same optimization as above |
| `ft::shift_left` / `ft::shift_right` | C++20 | Shift elements in a range |
| `ft::member_swap` | — | Generic swap preferring member `swap()` |
| `ft::iter_swap` / `ft::swap_ranges` | — | Iterator-based swap using `ft::member_swap` |
| `ft::min` / `ft::max` | — | Non-const overloads allowing assignment to the result |

Some functions also accept "ranges" – any type with `begin()`/`end()` and iterator typedefs, or bounded arrays.

---

### iterator

[`#include "libftpp/iterator.hpp"`](libftpp/iterator.hpp)

| Component | Standard | Description |
|-----------|----------|-------------|
| `ft::advance` | C++20 | Ranges-style overloads with sentinel bounds |
| `ft::next` / `ft::prev` | C++11 / C++20 | Iterator increment/decrement with sentinel overloads |
| `ft::begin` / `ft::end` | C++11 | Free function range access |
| `ft::cbegin` / `ft::cend` | C++14 | Const range access |
| `ft::rbegin` / `ft::rend` | C++14 | Reverse range access |
| `ft::crbegin` / `ft::crend` | C++14 | Const reverse range access |
| `ft::size` / `ft::ssize` | C++17/C++20 | Range size |
| `ft::empty` | C++17 | Range emptiness check |
| `ft::data` | C++17 | Direct access to underlying array |
| `ft::is_iterator` | — | Custom trait: check for valid iterator |
| `ft::is_input_iterator` | — | Custom trait: input iterator check |
| `ft::is_output_iterator` | — | Custom trait: output iterator check |
| `ft::is_forward_iterator` | — | Custom trait: forward iterator check |
| `ft::is_bidirectional_iterator` | — | Custom trait: bidirectional iterator check |
| `ft::is_random_access_iterator` | — | Custom trait: random access iterator check |

---

### array

[`#include "libftpp/array.hpp"`](libftpp/array.hpp)

| Component | Standard | Description |
|-----------|----------|-------------|
| `ft::array<T, N>` | C++11 | Fixed-size aggregate container with iterators, element access, comparisons, `fill`, `swap` |
| `ft::get<I>` | C++11 | Compile-time indexed access |
| `ft::to_array` | C++20 | Create `ft::array` from a C-array |

---

### functional

[`#include "libftpp/functional.hpp"`](libftpp/functional.hpp)

| Component | Standard | Description |
|-----------|----------|-------------|
| `ft::function_traits<F>` | — | Query arity, return type, and argument types of function types (non-standard) |
| `ft::equal_to<T>` | C++14 | Transparent comparator with `void` specialization |
| `ft::not_equal_to<T>` | C++14 | Transparent comparator with `void` specialization |
| `ft::greater<T>` | C++14 | Transparent comparator with `void` specialization |
| `ft::less<T>` | C++14 | Transparent comparator with `void` specialization |
| `ft::greater_equal<T>` | C++14 | Transparent comparator with `void` specialization |
| `ft::less_equal<T>` | C++14 | Transparent comparator with `void` specialization |

---

### numeric

[`#include "libftpp/numeric.hpp"`](libftpp/numeric.hpp)

| Component | Standard | Description |
|-----------|----------|-------------|
| `ft::numeric_cast<To>(from)` | Boost | Checked numeric conversion with overflow detection |
| `ft::add_sat` / `ft::sub_sat` / `ft::mul_sat` / `ft::div_sat` | C++26 | Saturating integer arithmetic |
| `ft::add_checked` / `ft::sub_checked` / `ft::mul_checked` / `ft::div_checked` | — | Checked arithmetic returning `ft::expected` |
| `ft::add_throw` / `ft::sub_throw` / `ft::mul_throw` / `ft::div_throw` | — | Throwing checked arithmetic |
| `ft::abs_diff` | — | Absolute difference without UB |
| `ft::iota` | C++11 | Fill range with incrementing values |

Both `numeric_cast` and `from_string` support a non-throwing overload via `std::nothrow` tag, returning `ft::expected`.

---

### string

[`#include "libftpp/string.hpp"`](libftpp/string.hpp)

| Component | Standard | Description |
|-----------|----------|-------------|
| `ft::starts_with` | C++20 | String prefix check |
| `ft::ends_with` | C++20 | String suffix check |
| `ft::from_string<To>` | — | String-to-value parsing with format flags and error handling |
| `ft::to_string` | C++11 | Value-to-string conversion with format flags |
| `ft::trim` | — | Whitespace trimming |

`from_string` provides both throwing and non-throwing (`std::nothrow` tag → `ft::expected`) overloads with detailed error types (`from_string_invalid_exception`, `from_string_range_exception`).

---

### exception

[`#include "libftpp/exception.hpp"`](libftpp/exception.hpp)

| Component | Description |
|-----------|-------------|
| `ft::exception` | Base exception class with `error()`, `where()` (source location), and `who()` context fields |

All non-standard exception classes in the library inherit from `ft::exception`. Uses `ft::source_location` and `ft::optional` internally.

---

### safe_bool

[`#include "libftpp/safe_bool.hpp"`](libftpp/safe_bool.hpp)

| Component | Description |
|-----------|-------------|
| `ft::safe_bool<Derived>` | CRTP mixin implementing the Safe Bool idiom – prevents implicit conversions to `int` and cross-type comparisons |
| `ft::safe_bool<void>` | Virtual dispatch variant for polymorphic hierarchies |

Needed because C++98 lacks `explicit operator bool()`. Used by `unique_ptr`, `shared_ptr`, `optional`, and `expected`.

---

### assert

[`#include "libftpp/assert.hpp"`](libftpp/assert.hpp)

| Component | Description |
|-----------|-------------|
| `FT_STATIC_ASSERT(expr)` | Compile-time assertion for C++98 |
| `ft::make_false<T...>` | Dependent `false` for unconditionally failing static assertions in templates |
| `ft::make_true<T...>` | Dependent `true` to suppress unused typedef warnings |

---

### source_location

[`#include "libftpp/source_location.hpp"`](libftpp/source_location.hpp)

| Component | Standard | Description |
|-----------|----------|-------------|
| `ft::source_location` | C++20 | Captures file name, line, and function name |
| `FT_SOURCE_LOCATION_CURRENT()` | C++20 | Macro to capture current source location |

---

### operators

[`#include "libftpp/operators.hpp"`](libftpp/operators.hpp)

| Component | Description |
|-----------|-------------|
| `ft::operators::comparison` | Inherit from this and implement `operator<` to auto-generate `==`, `!=`, `>`, `<=`, `>=` |

---

### format

[`#include "libftpp/format.hpp"`](libftpp/format.hpp)

| Component | Description |
|-----------|-------------|
| `ft::bold`, `ft::italic`, `ft::underline` | ANSI text styling |
| `ft::red`, `ft::green`, `ft::yellow`, `ft::blue`, `ft::magenta`, `ft::cyan`, `ft::gray` | ANSI color formatting |
| `ft::log::ok`, `ft::log::info`, `ft::log::warn`, `ft::log::error`, `ft::log::line` | Structured log-line formatters |

---

### ctype

[`#include "libftpp/ctype.hpp"`](libftpp/ctype.hpp)

Wrappers around standard `<cctype>` functions that prevent undefined behavior by casting arguments to `unsigned char` first. Also returns `bool` and takes `char` for a cleaner interface.

---

### random

[`#include "libftpp/random.hpp"`](libftpp/random.hpp)

| Component | Description |
|-----------|-------------|
| `ft::urandom<T>()` | Read random data from `/dev/urandom` |

---

### preprocessor

[`#include "libftpp/preprocessor.hpp"`](libftpp/preprocessor.hpp)

| Component | Description |
|-----------|-------------|
| `FT_CONCAT` / `FT_CONCAT_EXPANDED` | Token pasting with expansion |
| `FT_APPEND_UNIQUE_NUM(name)` | Generate unique identifiers using `__COUNTER__` |

---

## Roadmap

Things I would love to work on next:

- [ ] **`ft::variant`** and compile-time **type-list** – discriminated union, the foundation for stack-allocated polymorphic storage
- [ ] **Rework `ft::optional` and `ft::expected`** – eliminate heap allocations using aligned storage and placement `new`, applying knowledge gained from `ft::variant`
- [ ] **`ft::function`** – type-erased callable wrapper
- [ ] **`ft::reference_wrapper`** – reference semantics in value contexts
- [ ] **`ft::unordered_*` containers** – hash-based containers
- [ ] **`ft::string_view`** – non-owning string reference
- [ ] **Ranges** including range-based algorithms

---

## A Note on Testing

The biggest mistake I made was to not set up a proper testing framework. Now I have lots of things that have no tests, and the test files I have are so ugly and made in different and inconsistent styles that I don't even dare to have them on the main branch. I truly learned the importance of testing in this project – through regret.

---

## Building

```bash
make
```

This produces `libftpp.a`. Link against it and add the project root to your include path.
