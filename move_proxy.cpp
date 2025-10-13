#include <algorithm> // For std::swap
#include "libftpp/utility.hpp"

// --- Part 1: noncopyable utility (unchanged) ---
class noncopyable {
protected:
    noncopyable() {}
    ~noncopyable() {}
private:
    noncopyable(const noncopyable&);
    const noncopyable& operator=(const noncopyable&);
};


// --- Part 2: The CRTP infrastructure (UPDATED) ---

// Forward declarations are still needed
template <typename T>
class movable_impl;

template <typename T>
typename movable_impl<T>::move_proxy move(T& subject);


// The CRTP base class that provides the move proxy and friend declaration.
template <typename T>
class movable_impl {
public:
    // The proxy now holds a POINTER to the source object.
    // This avoids the need for a default constructor for T.
    struct move_proxy {
        T* source_ptr_; // The only member is a pointer

        // The constructor simply captures the address of the source.
        explicit move_proxy(T& source) : source_ptr_(&source) {}
    };

private:
    // Grant the global 'move' function access to our private proxy.
    friend typename movable_impl<T>::move_proxy move<T>(T& subject);
};


// The global move function (logic is identical, but returns the new proxy type)
template <typename T>
typename movable_impl<T>::move_proxy move(T& subject) {
    return typename movable_impl<T>::move_proxy(subject);
}

#include <iostream>

// A resource-managing class WITHOUT a default constructor.
class ResourceHandle : public movable_impl<ResourceHandle>/* , private noncopyable */ {
private:
    int resource_id_;

    ResourceHandle(const ft::copy_assign_ref<ResourceHandle>&);
    ResourceHandle& operator=(const ft::copy_assign_ref<ResourceHandle>&);

public:
    // The only constructor requires an ID. No default constructor exists.
    explicit ResourceHandle(int id) : resource_id_(id) {
        std::cout << "ResourceHandle " << resource_id_ << " acquired." << std::endl;
    }

    // Destructor
    ~ResourceHandle() {
        if (resource_id_ != 0) {
            std::cout << "ResourceHandle " << resource_id_ << " released." << std::endl;
        } else {
            std::cout << "Empty ResourceHandle destroyed." << std::endl;
        }
    }

    // 1. The essential swap method
    void swap(ResourceHandle& other) {
        std::swap(this->resource_id_, other.resource_id_);
    }

    // 2. The "Move Constructor"
    // We must explicitly initialize our members to a valid "empty" state
    // before swapping with the source.
    ResourceHandle(move_proxy proxy) : resource_id_(0) { // Initialize to empty state
        swap(*proxy.source_ptr_);
        std::cout << "(Move Constructed)" << std::endl;
    }

    // 3. The "Move Assignment Operator"
    ResourceHandle& operator=(move_proxy proxy) {
        swap(*proxy.source_ptr_);
        std::cout << "(Move Assigned)" << std::endl;
        return *this;
    }

    // Utility function
    int getID() const {
        return resource_id_;
    }
};

// A factory function that returns an owned resource
ResourceHandle createResource() {
    ResourceHandle temp(123);
    return move(temp); // Return by move
    return temp;
}

int main() {
    std::cout << "--- Creating r1 ---" << std::endl;
    ResourceHandle r1(42);
    std::cout << "r1 holds resource: " << r1.getID() << std::endl;

    std::cout << "\n--- Move constructing r2 from r1 ---" << std::endl;
    ResourceHandle r2 = move(r1);
    std::cout << "r1 now holds resource: " << r1.getID() << std::endl;
    std::cout << "r2 now holds resource: " << r2.getID() << std::endl;

    std::cout << "\n--- Move assigning from r2 to r3 ---" << std::endl;
    ResourceHandle r3(999);
    std::cout << "r3 initially holds: " << r3.getID() << std::endl;
    r3 = move(r2); // Old resource in r3 (999) is released
    std::cout << "r2 now holds resource: " << r2.getID() << std::endl;
    std::cout << "r3 now holds resource: " << r3.getID() << std::endl;

    std::cout << "\n--- Creating from factory ---" << std::endl;
    ResourceHandle r4 = createResource();
    std::cout << "r4 created from factory, holds: " << r4.getID() << std::endl;
    
    std::cout << "\n--- End of main ---" << std::endl;
    return 0;
}
