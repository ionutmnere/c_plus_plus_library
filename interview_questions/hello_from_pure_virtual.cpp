// Q: is it possible?

#include <iostream>

class A 
{
public:
	virtual void foo() = 0;
	
};
void A::foo()
{
	std::cout << "Hello from foo pure virtual function!" << std::endl;
}

class B : public A
{
public:
	void foo() override 
	{
		A::foo();
		std::cout << "Hello from foo override function!" << std::endl;		
	}
};

int main()
{

  // A a; // this will not compile - because A is still an abstract class
  
  B b;
  b.foo();
  
  std::cout << std::endl << "main finished. exiting..." << std::endl;
  return 0;
}
