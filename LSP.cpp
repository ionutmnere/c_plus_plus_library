// Liskov Substitution Principle
// Liskov Substitution Principle states that “Objects of superclass can be should be replaceable with objects of subclass without altering the correctness of program.”
// In Simple terms, it means that a subclass should be able to be used wherever superclass is expected, and it should introduce the error or break the program.
// In another words, You are expected that you should not reduce the number of functionality in the subclass than superclass.

#include <iostream>
#include <exception>

using namespace std;

class Bird {
  public:
    virtual bool canFly() = 0;
};

// class Crow : public Bird {
//     public:
//         void fly() override {
//             cout << "Crow is flying" << endl;
//         }
// };

// class Penguin : public Bird {
//     public:
//         void fly() override {
//             throw runtime_error("Penguins can't fly");
//         }
// };

class FlyingBird : public Bird 
{
  public:
    virtual void fly() = 0;
    bool canFly() override { return true; };
};

class Penguin : public Bird 
{
  public:
    bool canFly() override { return false; };
};

class Crow : public FlyingBird 
{
  public:
    void fly() override { cout << "Crow flying..." << endl;}
};

int main()
{
  // Penguin penguin_1;
  // penguin_1.fly(); // this breaks the LSP

  Penguin penguin_2;
  cout << "penguins can fly: " << (penguin_2.canFly() ? "True" : "False") << endl;
  Crow crow_1;
  cout << "crows can fly: " << (crow_1.canFly() ? "True" : "False") << endl;
  crow_1.fly();
  return 0;
}

