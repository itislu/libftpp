# libftpp - A C++98 library

## Design Decisions

- Reimplemenations of existing functionality in the Standard Library should never be better than the reference.
	- One should not get reliant on these reimplementations, they will never be perfect because they are just backports to an older C++ standard.
	- It should be easy to replace `ft::` with `std::` to get the reference.

### Exceptions

- Reimplementations throw the same exception as the reference, or reimplementations of those exceptions if they don't exist in C++98.
- Originals throw custom exception objects which always inherit from `ft::Exception`.
