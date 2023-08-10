// What is sizeof(A) and sizeof(B) ?

#include <iostream>

struct A
{
  char a;
  short b;
  int c;
};

struct B
{
  char a;
  int c;
};

int main()
{
  std::cout << "sizeof(A): " << sizeof(A) << std::endl;
  std::cout << "sizeof(B): " << sizeof(B) << std::endl;
  std::cout << std::endl << "main finished. exiting..." << std::endl;
  return 0;
}