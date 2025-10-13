#include <cstddef>
#include <cstring>
#include <iostream>

template <class T>
class rv : public T {
private:
	rv();
	~rv() throw();
	rv(rv const&);
	void operator=(rv const&);
};

// Move function
template <class T>
rv<T>& move(T& x)
{
	return *static_cast<rv<T>*>(&x);
}

template <typename T>
struct movable {
	operator rv<T>&()
	{
	    // return move(*this);
		return *static_cast<rv<T>*>(this);
	}
};

class MovableString : public movable<MovableString> {
	char* data_;
	size_t size_;

private:
	// Disable copying
	MovableString(MovableString&);
	MovableString& operator=(MovableString&);

public:
	MovableString()
	    : data_(NULL),
	      size_(0)
	{}

	explicit MovableString(const char* str)
	{
		size_ = std::strlen(str);
		data_ = new char[size_ + 1];
		std::strcpy(data_, str);
	}

	~MovableString() { delete[] data_; }

	// Move constructor
	MovableString(rv<MovableString>& other)
	    : data_(other.data_),
	      size_(other.size_)
	{
		other.data_ = NULL;
		other.size_ = 0;
	}

	// Move assignment
	MovableString& operator=(rv<MovableString>& other)
	{
		if (this != &other) {
			delete[] data_;
			data_ = other.data_;
			size_ = other.size_;
			other.data_ = NULL;
			other.size_ = 0;
		}
		return *this;
	}

	// Conversion operators
	// operator rv<MovableString>&()
	// {
	//     // return move(*this);
	// 	return *static_cast<rv<MovableString>*>(this);
	// }

	// operator const rv<MovableString>&() const
	// {
	//     return move(*this);
	// 	// return *static_cast<const rv<MovableString>*>(this);
	// }

	const char* c_str() const { return data_ ? data_ : ""; }
};

class sink_tester {
public: // conversions provided by BOOST_COPYABLE_AND_MOVABLE
	operator rv<sink_tester>&() { return *static_cast<rv<sink_tester>*>(this); }
	operator const rv<sink_tester>&() const
	{
		return *static_cast<const rv<sink_tester>*>(this);
	}
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
void sink(rv<sink_tester>&)
{
	std::cout << "non-const rvalue catched" << std::endl;
}
// BOOST_COPY_ASSIGN_REF overload
void sink(const rv<sink_tester>&)
{
	std::cout << "const (r-l)value catched" << std::endl;
}
// Overload provided by BOOST_COPYABLE_AND_MOVABLE
void sink(sink_tester&)
{
	std::cout << "non-const lvalue catched" << std::endl;
}

void func2(std::string&& str) { (void)str; }

MovableString func()
{
	MovableString str("Hello from func");
	// return str;
	return move(str);
}

void func2(rv<MovableString>& str)
{
	(void)str;
	std::cout << "func2(rv<MovableString>&)" << '\n';
}
// void func2(MovableString str)
// {
// 	(void)str;
// 	std::cout << "func2(MovableString)" << '\n';
// }

int main()
{
	sink(const_rvalue()); //"const (r-l)value catched"
	sink(const_lvalue()); //"const (r-l)value catched"
	sink(lvalue());       //"non-const lvalue catched"
	sink(rvalue());       //"non-const rvalue catched"

	// Usage
	MovableString str1("Hello");
	MovableString str2 = move(str1); // Move construction
	std::cout << str1.c_str() << '\n';

	MovableString str3 = func();
	std::cout << str3.c_str() << '\n';

	func2(str3);
	std::cout << str3.c_str() << '\n';
	// return 0;
	func2(func());

	func2(move(str3));
	std::cout << str3.c_str() << '\n';

	std::string std_string("hello");
	// func2(std::move(std_string));
	func2(std_string);
	std::cout << std_string << '\n';
}
