#include <iostream>
#include <vector>


template <typename T>
void displ_v(const T & v) {
    if(!v.size()) return;
    for(auto e :  v) { std::cout << e << " "; }
    std::cout << std::endl;
}

template<typename T1, typename T2>
void printpair(std::pair<T1, T2> & p) {
    std::cout << p.first << " : " << p.second << std::endl;
}

template <typename T>
void displ_v_of_pair(const T & v) {
    if(!v.size()) return;
    for(auto e :  v) { printpair(e); }
    std::cout << std::endl;
}


int main()
{
    std::vector<std::string> v1 = { "one", "two", "three", "four", "five" };
    displ_v(v1);    
    {
	    v1.push_back("six");
	    displ_v(v1);

	    std::cout << v1.emplace_back("seven") << std::endl;
	    displ_v(v1);

	    v1.push_back(std::string("eight"));
	    displ_v(v1);

	    std::cout << v1.emplace_back(std::string("nine")) << std::endl;
	    displ_v(v1);
	}
	displ_v(v1);
	std::cout << std::endl;

	std::vector<std::pair<int, std::string>> v2 = { { 1, "one"}, { 2, "two"} };
	displ_v_of_pair(v2);

	v2.push_back(std::pair(3, "three"));
	displ_v_of_pair(v2);

	// v2.push_back(4, "four"); // does not compile
	v2.emplace_back(4, "four"); // HERE IS ONE DIFFERENCE BETWEEN push_back and emplace_back 
	///                            -> emplace_back constructs a pair itself; push_back does not
	displ_v_of_pair(v2);

	// std::cout << v2.emplace_back(5, "five") << std::endl; // does not compile - because cout does not know how to print pair
	// v2.push_back(5, std::string("five"));                 // does not compile
	v2.emplace_back(5, std::string("five"));
	displ_v_of_pair(v2);

    std::cout << std::endl << "main finished. exiting..." << std::endl << std::endl;
    return 0;
}