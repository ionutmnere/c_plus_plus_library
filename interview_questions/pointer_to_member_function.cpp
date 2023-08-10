// Q: is it possible ?
#include <iostream>
#include <functional>

void bar()
{
	std::cout << "Hello from ::bar!" << std::endl;
}


class A
{
public:
	static void foo()
	{
		std::cout << "Hello from static A::foo!" << std::endl;
	}
};

class B
{
public:
	void foo(const int dummy_param)
	{
		std::cout << "Hello from B::foo! called with " << dummy_param << std::endl;
	}
};


int main()
{	
	// ----- Example 1 -----
	auto function_pointer = bar;
	function_pointer();

	// ----- Example 2 -----
	auto function_pointer2 = A::foo;
	function_pointer2();

	// ----- Example 3 -----
	auto function_pointer3 = &B::foo;
	B b; 
	std::invoke(function_pointer3, b, 10);

    // ----- Example 4 -----
	typedef void (B::*FpType)(const int x);
	FpType function_pointer4 = &B::foo;
	#define CALL_MEMBER_FN(object, ptrToMember) ((object).*(ptrToMember))
	B b2;
	CALL_MEMBER_FN(b2, function_pointer4)(20);

	// ----- Example 5 -----
	auto function_pointer5 = &B::foo;
	B b3;
	((b3).*(function_pointer5))(30);

	std::cout << std::endl << "main finished. exiting..." << std::endl;
	return 0;
}