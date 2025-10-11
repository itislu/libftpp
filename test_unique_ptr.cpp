#include "libftpp/memory.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
 
struct Foo // object to manage
{
    int value;

    Foo() : value() { std::cout << "Foo ctor\n"; }
    Foo(const Foo& other) : value(other.value) { std::cout << "Foo copy ctor\n"; }
    ~Foo() { std::cout << "~Foo dtor\n"; }

    void print() const { std::cout << "Foo::print() called, value = " << value << "\n"; }
    void setValue(int v) { value = v; }
};
 
struct D // deleter
{
    D() {};
    D(const D&) { std::cout << "D copy ctor\n"; }
    D(D&) { std::cout << "D non-const copy ctor\n"; }
    void operator()(Foo* p) const
    {
        std::cout << "D is deleting a Foo\n";
        delete p;
    };
};

// NOLINTBEGIN(misc-const-correctness)
int main()
{
    std::cout << "Example constructor(1)...\n";
    {
        ft::unique_ptr<Foo> up1; // up1 is empty
        ft::unique_ptr<Foo> up1b(NULL); // up1b is empty
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
        // ft::unique_ptr<Foo, D&> up3b(new Foo, d); // up3b holds a reference to d
    }
 
    std::cout << "Example constructor(4)...\n";
    {   // deleter is not a reference
        ft::unique_ptr<Foo, D> up4(new Foo, D()); // deleter moved
    }
 
    std::cout << "Example constructor(5)...\n";
    {
        ft::unique_ptr<Foo> up5a(new Foo);
        ft::unique_ptr<Foo> up5b(up5a.release()); // ownership transfer
    }
 
    std::cout << "Example constructor(6)...\n";
    {
        ft::unique_ptr<Foo, D> up6a(new Foo, d); // D is copied
        ft::unique_ptr<Foo, D> up6b(up6a.release()); // D is moved
 
        // ft::unique_ptr<Foo, D&> up6c(new Foo, d); // D is a reference
        // ft::unique_ptr<Foo, D> up6d(up6c.release()); // D is copied
    }
 
    // std::cout << "Example array constructor...\n";
    // {
    //     ft::unique_ptr<Foo[]> up(new Foo[3]);
    // } // three Foo objects deleted

    std::cout << "Example operator-> test...\n";
    {
        ft::unique_ptr<Foo> up(new Foo);
        // Test accessing member variable through operator->
        std::cout << "Value through operator->: " << up->value << "\n";
        
        // Test calling member function through operator->
        up->print();
        
        // Test modifying through operator->
        up->setValue(1);
        up->print();
        
        // Compare with raw pointer behavior
        Foo* raw_ptr = new Foo;
        std::cout << "Raw pointer value: " << raw_ptr->value << "\n";
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