// my_move.hpp

#include "libftpp/movable.hpp"
#include "libftpp/utility.hpp"
#include <cstddef>
#include <iostream>

namespace lib {

template <typename T>
class copy_assign_ref : public T {
private:
	copy_assign_ref();
	~copy_assign_ref();
	copy_assign_ref(copy_assign_ref const&);
	void operator=(copy_assign_ref const&);
};

// The wrapper class that emulates an rvalue reference.
template <class T>
class rv : public copy_assign_ref<T> {
private:
	rv();
	~rv();
	rv(rv const&);
	void operator=(rv const&);
};

// The move function that casts a T& to an rv<T>&.
template <class T>
rv<T>& move(T& t)
{
	// Casts the object to the rv<T> wrapper to trigger move-specific overloads.
	return static_cast<rv<T>&>(t);
}

template <class Derived>
struct movable {
protected:
// private:
#define MOV_CONST /* const */
	movable(MOV_CONST movable&) {
        std::cout << "COPY constructor\n";
    };
	movable& operator=(MOV_CONST movable&) {
        std::cout << "COPY assignment\n";
        return *this;
    };

protected:
	movable() {}
	~movable() {}

public:
#define EXPLICIT /* explicit */

	EXPLICIT operator rv<Derived>&()
	{
		return static_cast<rv<Derived>&>(*this);
	}

	EXPLICIT operator const rv<Derived>&() const
	{
		return static_cast<const rv<Derived>&>(*this);
	}
};

} // namespace lib

// Macro to be placed inside a class definition to make it movable.
#define LIB_MOVABLE(TYPE)                                                    \
public:                                                                      \
	operator lib::rv<TYPE>&() { return static_cast<lib::rv<TYPE>&>(*this); } \
	operator const lib::rv<TYPE>&() const                                    \
	{                                                                        \
		return static_cast<const lib::rv<TYPE>&>(*this);                     \
	}

// Macro for defining the parameter type in move constructors/assignments.
// #if __cplusplus >= 201103L
// #	define LIB_RV_REF(TYPE) TYPE&&
// #else
// #	define LIB_RV_REF(TYPE) lib::rv<TYPE>&
// #endif

/**
 * Disadvantage of mixin is that user is required to know to not use const-refs
 * when making copy functions private.
 * Also, g++ warns with -Wextra to explicitly initialize the base class in the
 * copy constructor.
 *
 * However, macro solution also needs to tell the user to not make the const-ref
 * copy functions private themselves.
 */
class ResourceOwner /* : public lib::movable<ResourceOwner> */ {
private:
	int* data;

// public:
#define RO_CONST /* const */
	// ResourceOwner(RO_CONST ResourceOwner&);
	// ResourceOwner& operator=(RO_CONST ResourceOwner& other);
	// ResourceOwner(const ResourceOwner&);
	// ResourceOwner& operator=(const ResourceOwner& other);
	// {
	//     // this->operator=(const_cast<const ResourceOwner&>(other));
	//     return *this = const_cast<const ResourceOwner&>(other);
	// }
	// ;

	FT_COPYABLE_AND_MOVABLE(ResourceOwner)
	// FT_MOVABLE_BUT_NOT_COPYABLE(ResourceOwner)

public:
	// Macro to inject move semantics support.
	// LIB_MOVABLE(ResourceOwner)

	// Default constructor
	ResourceOwner()
	    : data(new int(0))
	{
		std::cout << "Resource acquired." << '\n';
	}

	ResourceOwner(const ResourceOwner& other)
	    : /* lib::movable<ResourceOwner>(), */
          data(other.data != NULL ? new int(*other.data) : NULL)
	{
	    std::cout << "ResourceOwner copy constructor." << '\n';
	}

	// ResourceOwner& operator=(const ResourceOwner& other)
	ResourceOwner& operator=(const ft::copy_assign_ref<ResourceOwner>& other)
	{
	    std::cout << "ResourceOwner copy assignment operator." << '\n';
	    if (&other == this) return *this;
	    delete data;
	    data = other.data != NULL ? new int(*other.data) : NULL;
	    return *this;
	}
    
	// ResourceOwner& operator=(ResourceOwner other)
    // {
    //     std::cout << "ResourceOwner unifying assignment operator (by value)." << '\n';
    //     swap(other);
    //     return *this;
    // }

    // From boost.
    // I can use it to avoid "no copy assignment operator" clang-tidy warning.
	// This will require the macro solution.
    // ResourceOwner& operator=(ResourceOwner &t)
    // {
	// 	*this = const_cast<const ResourceOwner&>(t);
    //     return *this;
    // }

	// Move constructor
	/* explicit  */ResourceOwner(ft::rvalue<ResourceOwner>& other)
	{
		// Steal the pointer from the source object.
		data = other.data;
		// Invalidate the source object.
		other.data = NULL;
		std::cout << "Resource moved (constructor)." << '\n';
	}

	// Move assignment operator
	ResourceOwner& operator=(ft::rvalue<ResourceOwner>& other)
	{
        // swap(other);
		if (this != &other) {
			// Release our own resource first.
			delete data;
			// Steal the resource from the source object.
			data = other.data;
			// Invalidate the source object.
			other.data = 0; // or NULL
		}
        std::cout << "Resource moved (assignment)." << '\n';
		return *this;
	}

	// Destructor
	~ResourceOwner()
	{
		if (data) {
			std::cout << "Resource released." << '\n';
			delete data;
		}
	}

    void swap(ResourceOwner& other)
    {
        std::swap(data, other.data);
    }

	void setValue(int value)
	{
		if (data) {
			*data = value;
		}
	}

	int getValue() const { return data ? *data : -1; }
};

class sink_tester /* : public lib::movable<sink_tester> */ {
	LIB_MOVABLE(sink_tester)
};

// Functions returning different r/lvalue types
sink_tester rvalue() { return sink_tester(); }
const sink_tester const_rvalue() { return sink_tester(); }
sink_tester& lvalue()
{
	static sink_tester lv;
	return lv;
}
const sink_tester& const_lvalue()
{
	static const sink_tester clv = sink_tester();
	return clv;
}

// BOOST_RV_REF overload
void sink(lib::rv<sink_tester>&)
{
	std::cout << "non-const rvalue catched" << '\n';
}
// BOOST_COPY_ASSIGN_REF overload
void sink(const lib::rv<sink_tester>&)
{
	std::cout << "const (r-l)value catched" << '\n';
}
// Overload provided by BOOST_COPYABLE_AND_MOVABLE
void sink(sink_tester&) { std::cout << "non-const lvalue catched" << '\n'; }

ResourceOwner func1()
{
	ResourceOwner ro;
	ro.setValue(1);
	// return ro;
	return ft::move(ro);
    return ResourceOwner();
}

void func2(ft::rvalue<ResourceOwner>& ro) { ro.setValue(2); }

class A /* : public lib::movable<A> */ {
public:
    A() {}
    A(const A&) {}
    A& operator=(const A&) { return *this; }
    ~A() {}

    void take(lib::rv<A>&) {}
    void no_take(A&) {}
// private:
//     A(A&&);
//     A& operator=(A&&);
};

// void take(A&&) {}

int main()
{
    A a;
    // take(std::move(a));
    // take(a);
    a = ft::move(a);
    // a.take(a);
    a.no_take(ft::move(a));

	std::cout << "--- Creating ro1 ---" << '\n';
	ResourceOwner ro1;
	ro1.setValue(42);
	std::cout << "ro1 value: " << ro1.getValue() << '\n';

	std::cout << "\n--- Moving ro1 to ro2 ---" << '\n';
	// The call to ft::move(ro1) casts ro1 to lib::rv<ResourceOwner>&,
	// which selects the move constructor.
	ResourceOwner ro2 = ft::move(ro1);

	std::cout << "ro1 value after move: " << ro1.getValue() << " (now invalid)"
	          << '\n';
	std::cout << "ro2 value after move: " << ro2.getValue() << '\n';

	std::cout << "\n--- Moving ro2 back to ro1 ---" << '\n';
	// This selects the move assignment operator.
	std::cout << "hello1\n";
	// ro1 = ro2;
	std::cout << "hello2\n";
	ro1 = ft::move(ro2);
	std::cout << "hello3\n";
	std::cout << "ro1 value after 2nd move: " << ro1.getValue() << '\n';
	std::cout << "hello4\n";
	std::cout << "ro2 value after 2nd move: " << ro2.getValue()
	          << " (now invalid)" << '\n';

	std::cout << "\n--- ResourceOwner func1() ---" << '\n';
	ResourceOwner ro3 = func1(); // "Calling a private constructor"!
	std::cout << ro3.getValue() << '\n';
	ro3 = func1(); // "Calling a private constructor"!

	std::cout << "\n--- void func2(lib::rv<ResourceOwner>&) ---" << '\n';
	// func2(ro3);
	func2(ft::move(ro3));
	// func2(ft::move(func1())); // Not compilable.
	std::cout << ro3.getValue() << '\n';

	const ResourceOwner ro4;
	// const ResourceOwner ro5(ro4);
	// ro3 = ft::move(ro4);
	ro3 = ro4;
	ro3 = ro2;
	ro3 = ft::move(ro2);

	std::cout << "\n----------------------------" << '\n';
	sink(const_rvalue()); //"const (r-l)value catched"
	sink(const_lvalue()); //"const (r-l)value catched"
	sink(lvalue());       //"non-const lvalue catched"
	sink(rvalue());       //"non-const rvalue catched"

	std::cout << "\n--- Exiting main ---" << '\n';
	return 0;
}
