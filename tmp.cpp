#include <iostream>
// --- Forward declaration is needed for the friend function ---
template <typename T>
class my_unique_ptr;
template <typename T>
typename my_unique_ptr<T>::move_proxy move(my_unique_ptr<T>& ptr);
template <typename T>
class my_unique_ptr {
private:
    T* ptr_;
    // Private proxy struct for simulating moves
    struct move_proxy {
        T* ptr_;
        explicit move_proxy(my_unique_ptr<T>& source) : ptr_(source.release()) {}
    };
    // Private copy constructor and assignment to prevent copying
    my_unique_ptr(const my_unique_ptr&);
    my_unique_ptr& operator=(const my_unique_ptr&);
    // Grant 'move' access to our private 'move_proxy'
    // Note the syntax for a template friend function
    friend typename my_unique_ptr<T>::move_proxy move<T>(my_unique_ptr<T>& ptr);
public:
    explicit my_unique_ptr(T* p = 0) : ptr_(p) {}
    ~my_unique_ptr() {
        delete ptr_;
    }
    // "Move Constructor" that accepts the proxy
    my_unique_ptr(move_proxy proxy) : ptr_(proxy.ptr_) {
        proxy.ptr_ = 0;
    }
    // "Move Assignment Operator" that accepts the proxy
    my_unique_ptr& operator=(move_proxy proxy) {
        reset(proxy.ptr_);
        proxy.ptr_ = 0;
        return *this;
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
// The move function is now a friend, so this is legal.
template <typename T>
typename my_unique_ptr<T>::move_proxy move(my_unique_ptr<T>& ptr) {
    return typename my_unique_ptr<T>::move_proxy(ptr);
}
// --- Main function to demonstrate usage ---
int main() {
    my_unique_ptr<int> p1(new int(100));
    std::cout << "p1 owns pointer to value: " << *p1 << std::endl;
    my_unique_ptr<int> p2 = move(p1); // Works perfectly
    std::cout << "Ownership transferred." << std::endl;
    std::cout << "p1 is now: " << (p1.get() ? "not null" : "null") << std::endl;
    std::cout << "p2 owns pointer to value: " << *p2 << std::endl;
    return 0;
}
