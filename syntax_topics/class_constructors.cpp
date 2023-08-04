#include <iostream>
#include <string>



class BaseClass {
public:
    std::string name_;

};

class DerivedClass : public BaseClass {
public:
    std::string id_;
};

int main() 
{
    BaseClass base_class{"name of base_class"};    
    DerivedClass derived_class{"name of derived_class", "ID of derived_class"};
    
    std::cout << "base_class.name_: " << base_class.name_ << std::endl;
    std::cout << "derived_class.name_: " << derived_class.name_ << std::endl;
    std::cout << "derived_class.id_: " << derived_class.id_ << std::endl;
    std::cout << std::endl;
    
    base_class = derived_class;

    std::cout << "base_class.name_: " << base_class.name_ << std::endl;
    std::cout << "derived_class.name_: " << derived_class.name_ << std::endl;
    std::cout << "derived_class.id_: " << derived_class.id_ << std::endl;

    //derived_class = base_class; // does not compile
    
    std::cout << std::endl << "main finished. exiting..." << std::endl;
    return 0;
}