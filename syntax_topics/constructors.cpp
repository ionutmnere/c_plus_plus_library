#include <iostream>
#include <string>
#include <memory>

/// ---------------------------------------  Base and derived class assignments ----------------------------
class BaseClass {
public:
    std::string name_;

};

class DerivedClass : public BaseClass {
public:
    std::string id_;
};

/// -----------------------------------------  Default Constructor -----------------------------------------
class DefaultCtrClass
{
public:
    std::string id_;
};

class DefaultCtrClass2
{
public:
    DefaultCtrClass2() {
        std::cout << "DefaultCtrClass2 called..." << std::endl;
        id_ = "default id";
    }
    std::string id_;
};


class DefaultCtrClass3
{
public:
    DefaultCtrClass3() = default;
    std::string id_;
};

class DefaultCtrClass4
{
public:
    DefaultCtrClass4() = delete;
    std::string id_;
};

/// -----------------------------------------  Parametrised Constructor ----------------------------------------
class ParametrisedCtrClass
{
public:
    
    ParametrisedCtrClass(const std::string& p_id) : id_(p_id) {
        std::cout << "ParametrisedCtrClass called..." << std::endl;
    }

    std::string id_;
};

/// -----------------------------------------  Copy Constructor ----------------------------------------
// A copy constructor is a member function that initializes an object using another object of the same class.
// Copy constructor takes a reference to an object of the same class as an argument.
class ClassWithCopyConstructor
{
public:    
    // Parametrised constructor
    ClassWithCopyConstructor(const std::string& id, const int count)
    {
        id_ = id;
        count_ = count;
    }
    // copy constructor 1
    ClassWithCopyConstructor(const ClassWithCopyConstructor& p_other_obj)
    {
        std::cout << "ClassWithCopyConstructor(const ClassWithCopyConstructor& p_other_obj): copy constructor invoked! copying data from p_other_obj into new object..." << std::endl;
        id_ = p_other_obj.id_;
        count_ = p_other_obj.count_;
    }
    // copy constructor 2
    ClassWithCopyConstructor(const std::shared_ptr<ClassWithCopyConstructor> p_other_obj)
    {
        std::cout << "ClassWithCopyConstructor(const std::shared_ptr<ClassWithCopyConstructor> p_other_obj): copy constructor invoked! copying data from p_other_obj into new object..." << std::endl;
        id_ = p_other_obj->id_;
        count_ = p_other_obj->count_;
    }
    // helper just for debug
    void display() {
        std::cout << "id_   : " << id_ << std::endl;
        std::cout << "count_: " << count_ << std::endl;
    }
    std::string id_;
    int count_;
};

/// ----------------------------------------  Copy Constructor vs Assignment Operator ------------------------
class CopyVsAssignmentClass
{
public:
    CopyVsAssignmentClass() {
        std::cout << "Default Constructor called..." << std::endl; 
    }
    // copy constructor
    CopyVsAssignmentClass(const CopyVsAssignmentClass& p_other) { 
        std::cout << "Copy Constructor called..." << std::endl; 
    }
    // assignment operator 
    CopyVsAssignmentClass& operator=(const CopyVsAssignmentClass& p_other) {
        std::cout << "Assignment operator called..." << std::endl; 
        return *this;
    }

};

int main() 
{
    std::cout << std::endl << "-------------------  Base and derived class assignments -------------------" << std::endl;
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


    std::cout << std::endl << "-------------------  Default Constructor -------------------" << std::endl;
    DefaultCtrClass defaultCtrObj;
    std::cout << "defaultCtrObj.id_:'" << defaultCtrObj.id_ << "'" << std::endl;

    DefaultCtrClass2 defaultCtrObj2;
    std::cout << "defaultCtrObj2.id_:'" << defaultCtrObj2.id_ << "'" << std::endl;
    // DefaultCtrClass2 defaultCtrObj2_1(); // does not compile
    // DefaultCtrClass2 defaultCtrObj2_1{"some other id"}; // does not compile

    DefaultCtrClass3 defaultObj3;
    std::cout << "defaultObj3.id_:'" << defaultObj3.id_ << "'" << std::endl;
    DefaultCtrClass3 defaultObj3_1{"obj 3_1 id"};
    std::cout << "defaultObj3_1.id_:'" << defaultObj3_1.id_ << "'" << std::endl;

    // DefaultCtrClass4 defaultObj4; // does not compile - trying to use deleted default constructor
    DefaultCtrClass4 defaultObj4{"obj4 id"}; // This works even though the default constructor is deleted!
                                             // Compiler creates a parametrised constructor by default
    std::cout << "defaultObj4.id_:'" << defaultObj4.id_ << "'" << std::endl;

    std::cout << std::endl << "-------------------  Parametrised Constructor -------------------" << std::endl;
    ParametrisedCtrClass parametrisedObj1("parametrisedObj1 id");
    std::cout << "parametrisedObj1.id_:'" << parametrisedObj1.id_ << "'" << std::endl;
    // ParametrisedCtrClass parametrisedObj2; // does not compile - default constructor is not added 
                                              // when parametrised constructor is prezent
    // ParametrisedCtrClass parametrisedObj1{"parametrisedObj1 id"}; // does not compile

    std::cout << std::endl << "-------------------  Copy Constructor -------------------" << std::endl;
    std::cout << "----------- Stack -----------" << std::endl;
    ClassWithCopyConstructor c("copy cstr id", 10);
    c.display();
    std::cout << std::endl;
    ClassWithCopyConstructor d(c);
    d.display();
    {
        std::cout << "----------- Unique ptr -----------" << std::endl;
        std::unique_ptr<ClassWithCopyConstructor> unique_obj = std::make_unique<ClassWithCopyConstructor>("unique obj id", 20);
        unique_obj->display();
        std::unique_ptr<ClassWithCopyConstructor> unique_obj2 = std::make_unique<ClassWithCopyConstructor>(*unique_obj);
        unique_obj2->display();
        std::unique_ptr<ClassWithCopyConstructor> unique_obj3 = std::make_unique<ClassWithCopyConstructor>(c);
        unique_obj3->display();
        std::cout << "----------- Shared ptr -----------" << std::endl;
        std::shared_ptr<ClassWithCopyConstructor> shared_obj1 = std::make_shared<ClassWithCopyConstructor>("shared obj id", 30);
        shared_obj1->display();
        std::shared_ptr<ClassWithCopyConstructor> shared_obj2 = std::make_shared<ClassWithCopyConstructor>(shared_obj1);
        shared_obj2->display();
        std::cout << "----------- Stack -> call directly at asignment -----------" << std::endl;
        ClassWithCopyConstructor test = c;
    }
    std::cout << std::endl << "------------------- Constructor vs Assignment Operator -------------------" << std::endl;
    {        
        std::cout << "----------- Stack -----------" << std::endl;
        CopyVsAssignmentClass obj1_by_default_constr; // calling default constructor
        CopyVsAssignmentClass obj2_by_default_constr; // calling default constructor
        obj2_by_default_constr = obj1_by_default_constr; // calling assignment operator
        CopyVsAssignmentClass obj3_by_copy_constructor = obj1_by_default_constr; // calling copy constructor
    }
    {
        std::cout << "----------- Shared ptr -----------" << std::endl; // these are only as examples - not recommended to complicate like this
        std::shared_ptr<CopyVsAssignmentClass> shared_obj1 = std::make_shared<CopyVsAssignmentClass>(); // calling default constructor
        std::shared_ptr<CopyVsAssignmentClass> shared_obj2 = std::make_shared<CopyVsAssignmentClass>(); // calling default constructor
        shared_obj1 = shared_obj2;   // assignment operator not called - because the one from shared_ptr is called
        *shared_obj1 = *shared_obj2; // assignment operator called
        std::shared_ptr<CopyVsAssignmentClass> shared_obj3 = std::make_shared<CopyVsAssignmentClass>(*shared_obj2); // copy constructor called
    }
    std::cout << std::endl << "main finished. exiting..." << std::endl;
    return 0;
}