#include <iostream>
#include <algorithm>
#include <vector>


template <typename T>
void displ_v(const T & v) {
    if(!v.size()) return;
    for(auto e :  v) { std::cout << e << " "; }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> v1 = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 31, 53, 59, 
                       61, 67, 71, 73, 79, 83, 89, 97 };
    displ_v(v1);

    auto it = std::remove(v1.begin(), v1.end(), 89);
    if (it == v1.end()) {
    	std::cout << "no elements removed" << std::endl;
    	std::cout << "it: " << *it << std::endl;
    } else
    {
    	std::cout << "removed element 89 " << std::endl;
    	v1.resize(it - v1.begin());

    }
    displ_v(v1);

    std::cout << std::endl << "main finished. exiting..." << std::endl << std::endl;
    return 0;
}