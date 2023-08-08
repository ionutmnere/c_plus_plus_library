#include <iostream>
#include <vector>
#include <list>


class A
{
public:	
	A(const int id) : id_(id), has_res_ownership(true) {
		std::cout << "A parametrised constructor called. id: " << id_ << std::endl;
	}
	A(const A& p_other) {
		this->id_ = p_other.id_;
		this->has_res_ownership = true; // when copying each object has ownership on his own resource
		std::cout << "A copy constructor called. id: " << this->id_ << std::endl;
	}	
	A(A&& p_other) {
		this->id_ = p_other.id_;
		std::cout << "A move constructor called. id: " << this->id_ << std::endl;
		// when moving, transfer owhership; let the id for tracking further on destructor
		this->has_res_ownership = true;
		p_other.has_res_ownership = false;
	}
	~A() {
		std::cout << "~A destructor called. id: " << this->id_ << std::endl;
		std::cout << "has_res_ownership: " << this->has_res_ownership << std::endl;
	}
	int id_;
	bool has_res_ownership; // just for exemplification who has ownership of the resource 
};

template <typename T>
void displ_a_list_vect(const T & l_or_v) {
    if(!l_or_v.size()) return;
    for(auto &e :  l_or_v) {
    	std::cout << e.id_ << " "; 
	}
    std::cout << std::endl;
}


int main() 
{
	{
		std::cout << "--------- Parent block start." << std::endl;
		// ----- a lot of copying are done in this way -------
		{
			std::vector<A> l_a_vector;
			std::cout << "--------- First child block start." << std::endl;
			A a{1};
			l_a_vector.push_back(std::move(a));
			A b{2};
			l_a_vector.push_back(std::move(b));
			A c{3};
			l_a_vector.emplace_back(std::move(c));
			displ_a_list_vect(l_a_vector);
			std::cout << "--------- First child block end." << std::endl;
		}
		// ----- in this way copying is not done anymore -------
		{
			std::list<A> l_a_list;
			std::cout << "--------- Second child block start." << std::endl;
			A a{1};
			l_a_list.push_back(std::move(a));
			A b{2};
			l_a_list.emplace_back(b);
			A c{3};
			l_a_list.emplace_back(std::move(c));
			l_a_list.emplace_back(A{4});            // similar with next one
			l_a_list.emplace_back(std::move(A{5})); // similar with previous one
			displ_a_list_vect(l_a_list);
			std::cout << "--------- Second child block end." << std::endl;

		}
		std::cout << "Parent block end." << std::endl;
	}
    
    std::cout << std::endl << "main finished. exiting..." << std::endl;
    return 0;
}
