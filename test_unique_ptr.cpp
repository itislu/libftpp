#include "libftpp/memory.hpp"
#include "libftpp/movable.hpp"
#include "libftpp/utility.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
 
class Foo // object to manage
{
public:
    Foo() : value() { std::cout << "Foo ctor\n"; }
    Foo(const Foo& other) : value(other.value) { std::cout << "Foo copy ctor\n"; }
    Foo(ft::rvalue<Foo>& other) : value(other.value) 
    { 
        std::cout << "Foo move ctor\n"; 
        other.value = 0; // or some other "invalid" value
    }
    Foo& operator=(const ft::copy_assign_ref<Foo>& other) 
    { 
        std::cout << "Foo copy assignment\n"; 
        value = other.value; 
        return *this; 
    }
    Foo& operator=(ft::rvalue<Foo>& other) 
    { 
        std::cout << "Foo move assignment\n"; 
        value = other.value; 
        other.value = 0; // or some other "invalid" value
        return *this;
    }
    ~Foo() { std::cout << "~Foo dtor\n"; }

    void print() const { std::cout << "Foo::print() called, value = " << value << "\n"; }
    void setValue(int v) { value = v; }
    int getValue() const { return value; }

private:
    FT_COPYABLE_AND_MOVABLE(Foo)

    int value;
};

class Bar // Constructable from Foo
{
public:
    Bar() { std::cout << "Bar default ctor\n"; }
    Bar(const Foo&) { std::cout << "Bar ctor from Foo\n"; }
    Bar(const Bar& other)
    { 
        std::cout << "Bar copy ctor\n"; 
    }
    Bar& operator=(const Bar& other) 
    { 
        std::cout << "Bar copy assignment\n"; 
        return *this; 
    }
    ~Bar() { std::cout << "~Bar dtor\n"; }
};
 
struct D // deleter
{
    typedef Foo* pointer;

    D() {};
    D(const D&) { std::cout << "D copy ctor\n"; }
    D(D&) { std::cout << "D non-const copy ctor\n"; }
    void operator()(Foo* p) const
    {
        std::cout << "D is deleting a Foo\n";
        delete p;
    };
};

struct D2 : public D
{
    D2() {};
    D2(const D&) { std::cout << "D2 D ctor\n"; }
    D2(D&) { std::cout << "D2 D non-const ctor\n"; }
    D2(ft::rvalue<D>&) { std::cout << "D2 D move ctor\n"; }
    D2(const D2&) : D() { std::cout << "D2 copy ctor\n"; }
    D2(D2&) : D() { std::cout << "D2 non-const copy ctor\n"; }
};

// NOLINTBEGIN(misc-const-correctness)
int main()
{
    {
        Bar bar1;
        Bar bar2(ft::move(bar1));
        bar1 = ft::move(bar2);
        // ft::unique_ptr<Foo&, D> p1(new Foo());
        // ft::unique_ptr<int() const, D> p1(new Foo());
    }
    {
        ft::unique_ptr<Foo, D> p1(new Foo());
        ft::unique_ptr<Foo, D2> p2(new Foo());
        p2 = ft::move(p1);
        // p2 = p1;
    }
    {
        D d;
        ft::unique_ptr<Foo, D&> p1(new Foo(), d);
        std::cout << "WATCH NOW\n";
        ft::unique_ptr<Bar, D2> p2(ft::move(p1));
    }
    std::cout << "Example constructor(1)...\n";
    {
        ft::unique_ptr<Foo, ft::default_delete<Foo> > up1; // up1 is empty
        ft::unique_ptr<Foo> up1b((Foo*)NULL); // up1b is empty
    }

    std::cout << "Example constructor(2)...\n";
    {
        ft::unique_ptr<Foo> up2(new Foo); //up2 now owns a Foo
    } // Foo deleted
 
    std::cout << "Example constructor(3)...\n";
    D d;
    {   // deleter type is not a reference
        ft::unique_ptr<Foo, D> up3(new Foo, d); // deleter copied
    }
    {   // deleter type is a reference
        ft::unique_ptr<Foo, D&> up3b(new Foo, d); // up3b holds a reference to d
    }
 
    std::cout << "Example constructor(4)...\n";
    {   // deleter is not a reference
        ft::unique_ptr<Foo, D> up4(new Foo, D()); // deleter moved
    }
 
    std::cout << "Example constructor(5)...\n";
    {
        ft::unique_ptr<Foo> up5a(new Foo);
        ft::unique_ptr<Foo> up5b(ft::move(up5a)); // ownership transfer
    }
 
    std::cout << "Example constructor(6)...\n";
    {
        ft::unique_ptr<Foo, D> up6a(new Foo, d); // D is copied
        ft::unique_ptr<Foo, D> up6b(ft::move(up6a)); // D is moved
        ft::unique_ptr<Foo, D2> up6c(ft::move(up6b)); // D is moved
 
        ft::unique_ptr<Foo, D&> up6d(new Foo, d); // D is a reference
        ft::unique_ptr<Foo, D> up6e(ft::move(up6c)); // D is copied
    }
 
    std::cout << "Example array constructor...\n";
    {
        ft::unique_ptr<Foo[]> up(new Foo[3]);
    } // three Foo objects deleted

    std::cout << "Example operator-> test...\n";
    {
        ft::unique_ptr<Foo> up(new Foo);
        // Test accessing member variable through operator->
        std::cout << "Value through operator->: " << up->getValue() << "\n";
        
        // Test calling member function through operator->
        up->print();
        
        // Test modifying through operator->
        up->setValue(1);
        up->print();
        
        // Compare with raw pointer behavior
        Foo* raw_ptr = new Foo;
        std::cout << "Raw pointer value: " << raw_ptr->getValue() << "\n";
        raw_ptr->setValue(2);
        raw_ptr->print();
        delete raw_ptr;
    }

    ft::make_unique<int>();
}
// NOLINTEND(misc-const-correctness)
/* 
std::unique_ptr<int> func(int v)
{
    static std::unique_ptr<int> ptr(new int(v));
    return std::move(ptr);
}

int main()
{
    return *func(42);
}
 */
