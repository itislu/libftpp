// move_semantics.hpp - A C++98 library for move semantics
#ifndef MOVE_SEMANTICS_HPP
#define MOVE_SEMANTICS_HPP

#include <algorithm>  // for std::swap
#include <vector>
#include <iostream>

namespace cpp98_move {

// ============================================================================
// Core move infrastructure
// ============================================================================

// Base class for movable types - provides the move proxy mechanism
template <typename Derived>
class movable {
public:
    // The proxy that represents an rvalue
    class rvalue_proxy {
    private:
        mutable Derived* source_;
    public:
        explicit rvalue_proxy(Derived& src) : source_(&src) {}
        
        // Allow the proxy to be used to construct the derived type
        Derived* release() const {
            Derived* tmp = source_;
            source_ = 0;
            return tmp;
        }
        
        Derived& get() const { return *source_; }
    };
    
protected:
    // Protected destructor - this is a mixin class
    ~movable() {}
    
private:
    // Prevent copying of the mixin itself
    movable(const movable&);
    movable& operator=(const movable&);
};

// The generic move function
template <typename T>
typename movable<T>::rvalue_proxy move(T& obj) {
    return typename movable<T>::rvalue_proxy(obj);
}

// Forward declaration for swap
template <typename T>
void swap(T& a, T& b);

// ============================================================================
// CRTP Mixin for adding move semantics to any class
// ============================================================================

template <typename Derived>
class enable_move : public movable<Derived> {
public:
    typedef typename movable<Derived>::rvalue_proxy rvalue_proxy;
    
protected:
    // Protected constructors for use by derived classes
    enable_move() {}
    
    // Move constructor from proxy
    enable_move(rvalue_proxy proxy) {
        Derived* other = proxy.release();
        if (other) {
            static_cast<Derived*>(this)->swap(*other);
        }
    }
    
    // Move assignment from proxy
    Derived& operator=(rvalue_proxy proxy) {
        Derived* other = proxy.release();
        if (other) {
            Derived temp(*other);  // Copy the source
            static_cast<Derived*>(this)->swap(temp);
            other->swap(temp);  // Clear the source
        }
        return *static_cast<Derived*>(this);
    }
    
    ~enable_move() {}
    
private:
    // Prevent copying of the mixin
    enable_move(const enable_move&);
    enable_move& operator=(const enable_move&);
};

// ============================================================================
// Example 1: Movable unique_ptr implementation
// ============================================================================

template <typename T>
class unique_ptr : public enable_move<unique_ptr<T> > {
private:
    T* ptr_;
    
    typedef typename enable_move<unique_ptr<T> >::rvalue_proxy rvalue_proxy;
    
    // Private copy operations
    unique_ptr(const unique_ptr&);
    unique_ptr& operator=(const unique_ptr&);
    
public:
    explicit unique_ptr(T* p = 0) : ptr_(p) {}
    
    ~unique_ptr() {
        delete ptr_;
    }
    
    // Move constructor using the proxy
    unique_ptr(rvalue_proxy proxy) : enable_move<unique_ptr<T> >(proxy), ptr_(0) {
        unique_ptr* other = proxy.release();
        if (other) {
            swap(*other);
        }
    }
    
    // Move assignment using the proxy
    unique_ptr& operator=(rvalue_proxy proxy) {
        unique_ptr* other = proxy.release();
        if (other && other != this) {
            unique_ptr temp;
            temp.swap(*other);
            swap(temp);
        }
        return *this;
    }
    
    // Swap function required for move operations
    void swap(unique_ptr& other) {
        std::swap(ptr_, other.ptr_);
    }
    
    T* get() const { return ptr_; }
    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    
    T* release() {
        T* temp = ptr_;
        ptr_ = 0;
        return temp;
    }
    
    void reset(T* p = 0) {
        if (ptr_ != p) {
            delete ptr_;
            ptr_ = p;
        }
    }
};

// ============================================================================
// Example 2: Movable vector wrapper with expensive copy
// ============================================================================

template <typename T>
class heavy_vector : public enable_move<heavy_vector<T> > {
private:
    std::vector<T> data_;
    std::string name_;
    
    typedef typename enable_move<heavy_vector<T> >::rvalue_proxy rvalue_proxy;
    
public:
    heavy_vector() : name_("default") {}
    
    explicit heavy_vector(const std::string& name) : name_(name) {}
    
    // Regular copy constructor (expensive)
    heavy_vector(const heavy_vector& other) 
        : data_(other.data_), name_(other.name_ + "_copy") {
        std::cout << "Expensive copy of " << other.name_ << std::endl;
    }
    
    // Move constructor (cheap)
    heavy_vector(rvalue_proxy proxy) : enable_move<heavy_vector<T> >(proxy) {
        heavy_vector* other = proxy.release();
        if (other) {
            swap(*other);
            std::cout << "Cheap move of " << name_ << std::endl;
        }
    }
    
    // Regular copy assignment (expensive)
    heavy_vector& operator=(const heavy_vector& other) {
        if (this != &other) {
            heavy_vector temp(other);
            swap(temp);
        }
        return *this;
    }
    
    // Move assignment (cheap)
    heavy_vector& operator=(rvalue_proxy proxy) {
        heavy_vector* other = proxy.release();
        if (other && other != this) {
            swap(*other);
            std::cout << "Cheap move assignment of " << name_ << std::endl;
        }
        return *this;
    }
    
    void swap(heavy_vector& other) {
        data_.swap(other.data_);
        name_.swap(other.name_);
    }
    
    void push_back(const T& val) { data_.push_back(val); }
    size_t size() const { return data_.size(); }
    const std::string& name() const { return name_; }
};

// ============================================================================
// Utility functions
// ============================================================================

// Swap specializations
template <typename T>
void swap(unique_ptr<T>& a, unique_ptr<T>& b) {
    a.swap(b);
}

template <typename T>
void swap(heavy_vector<T>& a, heavy_vector<T>& b) {
    a.swap(b);
}

// ============================================================================
// Algorithm support - move elements in containers
// ============================================================================

template <typename InputIt, typename OutputIt>
OutputIt move_range(InputIt first, InputIt last, OutputIt d_first) {
    while (first != last) {
        *d_first = move(*first);
        ++first;
        ++d_first;
    }
    return d_first;
}

// ============================================================================
// Optional: Macro for easier class definition
// ============================================================================

#define MAKE_MOVABLE(ClassName) \
    private: \
        typedef typename cpp98_move::enable_move<ClassName>::rvalue_proxy rvalue_proxy; \
    public: \
        ClassName(rvalue_proxy proxy) : cpp98_move::enable_move<ClassName>(proxy) { \
            ClassName* other = proxy.release(); \
            if (other) swap(*other); \
        } \
        ClassName& operator=(rvalue_proxy proxy) { \
            ClassName* other = proxy.release(); \
            if (other && other != this) { \
                ClassName temp; \
                temp.swap(*other); \
                swap(temp); \
            } \
            return *this; \
        }

} // namespace cpp98_move

#endif // MOVE_SEMANTICS_HPP

// ============================================================================
// Demo program
// ============================================================================

int main() {
    using namespace cpp98_move;
    
    std::cout << "=== unique_ptr demo ===" << std::endl;
    {
        unique_ptr<int> p1(new int(42));
        std::cout << "p1 value: " << *p1 << std::endl;
        
        unique_ptr<int> p2 = move(p1);
        std::cout << "After move, p1 is " << (p1.get() ? "not null" : "null") << std::endl;
        std::cout << "p2 value: " << *p2 << std::endl;
        
        unique_ptr<int> p3(new int(100));
        p3 = move(p2);
        std::cout << "After assignment, p2 is " << (p2.get() ? "not null" : "null") << std::endl;
        std::cout << "p3 value: " << *p3 << std::endl;
    }
    
    std::cout << "\n=== heavy_vector demo ===" << std::endl;
    {
        heavy_vector<int> v1("vector1");
        v1.push_back(1);
        v1.push_back(2);
        v1.push_back(3);
        
        std::cout << "\nCopy construction:" << std::endl;
        heavy_vector<int> v2(v1);  // Expensive copy
        
        std::cout << "\nMove construction:" << std::endl;
        heavy_vector<int> v3 = move(v1);  // Cheap move
        
        std::cout << "\nv1 size after move: " << v1.size() << std::endl;
        std::cout << "v3 size after move: " << v3.size() << std::endl;
        std::cout << "v3 name: " << v3.name() << std::endl;
    }
    
    std::cout << "\n=== Container of movable objects ===" << std::endl;
    {
        std::vector<unique_ptr<int> > vec;
        vec.reserve(3);
        
        // Can't push_back directly due to copy requirement
        // But we can use resize and then move assign
        vec.resize(3);
        vec[0] = move(unique_ptr<int>(new int(10)));
        vec[1] = move(unique_ptr<int>(new int(20)));
        vec[2] = move(unique_ptr<int>(new int(30)));
        
        std::cout << "Vector contents: ";
        for (size_t i = 0; i < vec.size(); ++i) {
            if (vec[i].get()) {
                std::cout << *vec[i] << " ";
            }
        }
        std::cout << std::endl;
    }
    
    return 0;
}
