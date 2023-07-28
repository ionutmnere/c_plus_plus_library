#include <iostream>

int main()
{
	std::cout << "__cplusplus: " << __cplusplus << std::endl;
	if (__cplusplus == 202002L)
	 std::cout << "Your running C++20" << std::endl;
	else if    (__cplusplus == 201703L)
	  std::cout << "Your running C++17" << std::endl;
	else if (__cplusplus == 201402L)
	  std::cout << "Your running C++14" << std::endl;
	else if (__cplusplus == 201103L)
	  std::cout << "Your running C++11" << std::endl;
	else if (__cplusplus == 199711L)
	  std::cout << "Your running C++98" << std::endl;
	else
	  std::cout << "pre-standard C++" << std::endl;
	std::cout << std::endl << "main finished. exiting..." << std::endl << std::endl;
	return 0;
}