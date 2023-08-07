#include <iostream>
#include <memory>


/// ----------------------------------------- No virtual usage -------------------------------------
class BaseClass
{
public:
  BaseClass() { std::cout << "BaseClass constructor..." << std::endl;}
  ~BaseClass() { std::cout << "~BaseClass destructor..." << std::endl;}
};

class DerivedClass : public BaseClass
{
public:
  DerivedClass () { std::cout << "DerivedClass constructor..." << std::endl;}
  ~DerivedClass () { std::cout << "~DerivedClass destructor..." << std::endl;}
};

/// ----------------------------------------- With virtual usage --------------------------------------
class BetterBaseClass
{
public:
  BetterBaseClass() {std::cout << "BetterBaseClass constructor..." << std::endl;}
  virtual ~BetterBaseClass() {std::cout << "~BetterBaseClass destructor..." << std::endl;}
};

class BetterDerivedClass : public BetterBaseClass
{
public:
  BetterDerivedClass() {std::cout << "BetterDerivedClass constructor..." << std::endl;}
  ~BetterDerivedClass() override {std::cout << "~BetterDerivedClass destructor..." << std::endl;}
};


int main() 
{
    std::cout << "----------------------------------------- No virtual usage ------------------------------------- " << std::endl;
    {
      DerivedClass d; // all works fine in this case
    }
    std::cout << std::endl;
    {
      std::shared_ptr<DerivedClass> d = std::make_shared<DerivedClass>(); // all works fine in this case
      std::unique_ptr<DerivedClass> u = std::make_unique<DerivedClass>(); // all works fine in this case
    }
    std::cout << std::endl;
    {
      std::unique_ptr<BaseClass> b = std::make_unique<DerivedClass>(); // here we have a problem; 
                                                                       // ~DerivedClass destructor is not called anymore
    }
    std::cout << std::endl << "----------------------------------------- With virtual usage -------------------------------------- " << std::endl;
    {
      std::unique_ptr<BetterBaseClass> b = std::make_unique<BetterDerivedClass>(); // problem solved;
                                                                                   // ~BetterDerivedClass destructor is called now
    }

    std::cout << std::endl << "main finished. exiting..." << std::endl;
    return 0;
}
