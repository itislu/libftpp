#include "libftpp/memory.hpp"
#include "libftpp/utility.hpp"
#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

// A simple struct to test with
struct TestObject {
	static int construction_count;
	static int destruction_count;

	int value;

	TestObject(int v = 0)
	    : value(v)
	{
		construction_count++;
	}
	~TestObject() { destruction_count++; }
};

int TestObject::construction_count = 0;
int TestObject::destruction_count = 0;

// A custom deleter
struct CustomDeleter {
	static int deleter_calls;
	void operator()(TestObject* p) const
	{
		deleter_calls++;
		delete p;
	}
};

int CustomDeleter::deleter_calls = 0;

// A custom deleter for arrays
struct CustomArrayDeleter {
	static int deleter_calls;
	void operator()(TestObject* p) const
	{
		deleter_calls++;
		delete[] p;
	}
};

int CustomArrayDeleter::deleter_calls = 0;

void reset_counts()
{
	TestObject::construction_count = 0;
	TestObject::destruction_count = 0;
	CustomDeleter::deleter_calls = 0;
	CustomArrayDeleter::deleter_calls = 0;
}

void test_single_object()
{
	std::cout << "--- Testing ft::unique_ptr for single objects ---"
	          << std::endl;

	// 1. Default constructor
	{
		reset_counts();
		ft::unique_ptr<TestObject> ptr;
		assert(ptr.get() == NULL);
		assert(!ptr);
	}

	// 2. Constructor with pointer
	{
		reset_counts();
		ft::unique_ptr<TestObject> ptr(new TestObject(10));
		assert(ptr.get() != NULL);
		assert(ptr->value == 10);
		assert(TestObject::construction_count == 1);
		assert(TestObject::destruction_count == 0);
	}
	assert(TestObject::destruction_count == 1);

	// 3. Destructor
	{
		reset_counts();
		TestObject* raw_ptr = new TestObject(20);
		{
			ft::unique_ptr<TestObject> ptr(raw_ptr);
			assert(TestObject::construction_count == 1);
		}
		assert(TestObject::destruction_count == 1);
	}

	// 4. release()
	{
		reset_counts();
		TestObject* raw_ptr;
		{
			ft::unique_ptr<TestObject> ptr(new TestObject(30));
			raw_ptr = ptr.release();
			assert(ptr.get() == NULL);
		}
		assert(TestObject::destruction_count == 0);
		delete raw_ptr;
		assert(TestObject::destruction_count == 1);
	}

	// 5. reset()
	{
		reset_counts();
		ft::unique_ptr<TestObject> ptr(new TestObject(40));
		assert(TestObject::construction_count == 1);
		ptr.reset(new TestObject(41));
		assert(TestObject::construction_count == 2);
		assert(TestObject::destruction_count == 1);
		assert(ptr->value == 41);
		ptr.reset();
		assert(ptr.get() == NULL);
		assert(TestObject::destruction_count == 2);
	}

	// 6. swap()
	{
		reset_counts();
		ft::unique_ptr<TestObject> ptr1(new TestObject(50));
		ft::unique_ptr<TestObject> ptr2(new TestObject(51));
		ptr1.swap(ptr2);
		assert(ptr1->value == 51);
		assert(ptr2->value == 50);
		ft::swap(ptr1, ptr2);
		assert(ptr1->value == 50);
		assert(ptr2->value == 51);
	}

	// 7. get()
	{
		reset_counts();
		TestObject* raw = new TestObject(60);
		ft::unique_ptr<TestObject> ptr(raw);
		assert(ptr.get() == raw);
	}

	// 8. operator* and operator->
	{
		reset_counts();
		ft::unique_ptr<TestObject> ptr(new TestObject(70));
		assert((*ptr).value == 70);
		assert(ptr->value == 70);
	}

	// 9. operator bool
	{
		reset_counts();
		ft::unique_ptr<TestObject> ptr1;
		ft::unique_ptr<TestObject> ptr2(new TestObject(80));
		assert(!ptr1);
		assert(ptr2);
	}

	// 10. Move constructor
	{
		reset_counts();
		ft::unique_ptr<TestObject> ptr1(new TestObject(90));
		ft::unique_ptr<TestObject> ptr2(ft::move(ptr1));
		assert(ptr1.get() == NULL);
		assert(ptr2->value == 90);
		assert(TestObject::construction_count == 1);
	}
	assert(TestObject::destruction_count == 1);

	// 11. Move assignment
	{
		reset_counts();
		ft::unique_ptr<TestObject> ptr1(new TestObject(100));
		ft::unique_ptr<TestObject> ptr2(new TestObject(101));
		assert(TestObject::construction_count == 2);
		ptr2 = ft::move(ptr1);
		assert(ptr1.get() == NULL);
		assert(ptr2->value == 100);
		assert(TestObject::destruction_count == 1);
	}
	assert(TestObject::destruction_count == 2);

	// 12. Custom deleter
	{
		reset_counts();
		{
			ft::unique_ptr<TestObject, CustomDeleter> ptr(new TestObject(110));
			assert(TestObject::construction_count == 1);
		}
		assert(TestObject::destruction_count == 1);
		assert(CustomDeleter::deleter_calls == 1);
	}

	// 13. Comparison operators
	{
		reset_counts();
		ft::unique_ptr<TestObject> ptr1(new TestObject(120));
		ft::unique_ptr<TestObject> ptr2(new TestObject(121));
		TestObject* raw1 = ptr1.get();
		TestObject* raw2 = ptr2.get();

		assert(ptr1 == ptr1);
		assert(ptr1 != ptr2);
		if (raw1 < raw2) {
			assert(ptr1 < ptr2);
			assert(ptr1 <= ptr2);
			assert(ptr2 > ptr1);
			assert(ptr2 >= ptr1);
		}
		else {
			assert(ptr2 < ptr1);
			assert(ptr2 <= ptr1);
			assert(ptr1 > ptr2);
			assert(ptr1 >= ptr2);
		}
	}

	// 14. make_unique
	{
		reset_counts();
		ft::unique_ptr<TestObject> ptr = ft::make_unique<TestObject>(130);
		assert(ptr->value == 130);
		assert(TestObject::construction_count == 1);
	}
	assert(TestObject::destruction_count == 1);

	std::cout << "All single object tests passed." << std::endl;
}

void test_array_object()
{
	std::cout << "--- Testing ft::unique_ptr for arrays ---" << std::endl;

	// 1. Default constructor
	{
		reset_counts();
		ft::unique_ptr<TestObject[]> ptr;
		assert(ptr.get() == NULL);
		assert(!ptr);
	}

	// 2. Constructor with pointer
	{
		reset_counts();
		ft::unique_ptr<TestObject[]> ptr(new TestObject[3]);
		assert(ptr.get() != NULL);
		assert(TestObject::construction_count == 3);
	}
	assert(TestObject::destruction_count == 3);

	// 3. operator[]
	{
		reset_counts();
		ft::unique_ptr<TestObject[]> ptr(new TestObject[3]);
		for (int i = 0; i < 3; ++i) {
			ptr[i].value = i * 10;
		}
		for (int i = 0; i < 3; ++i) {
			assert(ptr[i].value == i * 10);
		}
	}

	// 4. release()
	{
		reset_counts();
		TestObject* raw_ptr;
		{
			ft::unique_ptr<TestObject[]> ptr(new TestObject[3]);
			raw_ptr = ptr.release();
			assert(ptr.get() == NULL);
		}
		assert(TestObject::destruction_count == 0);
		delete[] raw_ptr;
		assert(TestObject::destruction_count == 3);
	}

	// 5. reset()
	{
		reset_counts();
		ft::unique_ptr<TestObject[]> ptr(new TestObject[2]);
		assert(TestObject::construction_count == 2);
		ptr.reset(new TestObject[4]);
		assert(TestObject::construction_count == 2 + 4);
		assert(TestObject::destruction_count == 2);
		ptr.reset();
		assert(ptr.get() == NULL);
		assert(TestObject::destruction_count == 2 + 4);
	}

	// 6. swap()
	{
		reset_counts();
		ft::unique_ptr<TestObject[]> ptr1(new TestObject[2]);
		ptr1[0].value = 1;
		ft::unique_ptr<TestObject[]> ptr2(new TestObject[3]);
		ptr2[0].value = 2;
		ptr1.swap(ptr2);
		assert(ptr1[0].value == 2);
		assert(ptr2[0].value == 1);
		assert(TestObject::construction_count == 5);
	}
	assert(TestObject::destruction_count == 5);

	// 7. Move constructor
	{
		reset_counts();
		ft::unique_ptr<TestObject[]> ptr1(new TestObject[3]);
		ptr1[0].value = 10;
		ft::unique_ptr<TestObject[]> ptr2(ft::move(ptr1));
		assert(ptr1.get() == NULL);
		assert(ptr2[0].value == 10);
	}

	// 8. Move assignment
	{
		reset_counts();
		ft::unique_ptr<TestObject[]> ptr1(new TestObject[2]);
		ptr1[0].value = 20;
		ft::unique_ptr<TestObject[]> ptr2(new TestObject[4]);
		ptr2[0].value = 30;
		assert(TestObject::construction_count == 6);
		ptr2 = ft::move(ptr1);
		assert(ptr1.get() == NULL);
		assert(ptr2[0].value == 20);
		assert(TestObject::destruction_count == 4);
	}
	assert(TestObject::destruction_count == 4 + 2);

	// 9. Custom deleter
	{
		reset_counts();
		{
			ft::unique_ptr<TestObject[], CustomArrayDeleter> ptr(
			    new TestObject[5]);
			assert(TestObject::construction_count == 5);
		}
		assert(TestObject::destruction_count == 5);
		assert(CustomArrayDeleter::deleter_calls == 1);
	}

	// 10. make_unique for arrays
	{
		reset_counts();
		ft::unique_ptr<TestObject[]> ptr = ft::make_unique<TestObject[]>(5);
		assert(TestObject::construction_count == 5);
		assert(ptr.get() != NULL);
		// Values are default-initialized, so should be 0
		for (size_t i = 0; i < 5; ++i) {
			assert(ptr[i].value == 0);
		}
	}
	assert(TestObject::destruction_count == 5);

	std::cout << "All array tests passed." << std::endl;
}

int main()
{
	test_single_object();
	std::cout << std::endl;
	test_array_object();
	std::cout << std::endl;
	std::cout << "All ft::unique_ptr tests passed successfully!" << std::endl;
	return 0;
}
