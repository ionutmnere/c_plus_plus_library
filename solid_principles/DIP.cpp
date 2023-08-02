// 1. High-level modules should not depend on low-level modules. Both should depend on abstractions.
// 2. Abstracttions should not depend on details. Details should depend on abstractions.

// High-level modules: describes operations which are more abstract in nature and more complex in loc - bussiness logic
// Low-level modules: describes implementations more specific and individual to components 
// focusing on details and smaller parts of the application. Low-level modules are used inside high-level modules.

#include <iostream>


/// ------------ this breaks the DIP --------------------
class LightBulb {
 public:
  void TurnOn() {
    std::cout << "Light bulb on..." << std::endl;
  }

  void TurnOff() {
    std::cout << "Light bulb off..." << std::endl;
  }

};

class ElectricPowerSwitch {
 public:
  ElectricPowerSwitch(LightBulb light_bulb) : light_bulb_{light_bulb}, on_{ false } {}
  void press() {
    if (on_) {
      light_bulb_.TurnOff();
      on_ = false;
    } else {
      light_bulb_.TurnOn();
      on_ = true;
    }
  }
 private:
  LightBulb light_bulb_;
  bool on_;
};

/// -------- Better approach ------------------------
class Switchable {
 public:
  virtual void TurnOn() = 0;
  virtual void TurnOff() = 0;
  virtual ~Switchable() = default;
};

class BetterElectricPowerSwitch {
public:
  BetterElectricPowerSwitch(Switchable& switchable_device) : 
  switchable_device_{switchable_device}, 
  on_{ false } {}
  
  void press() {
    if (on_) {
      switchable_device_.TurnOff();
      on_ = false;
    } else {
      switchable_device_.TurnOn();
      on_ = true;
    }
  }
 private:
  Switchable& switchable_device_;
  bool on_;
};

class BetterLightBulb final : public Switchable {
  void TurnOn() override {
    std::cout << "Better way to turn on light bulb" << std::endl;
  }
  void TurnOff() override {
    std::cout << "Better way to turn off light bulb" << std::endl;
  }
};


int main() {
  // This example breaks the DIP
  LightBulb light_bulb{}; // low level module  
  ElectricPowerSwitch power_switch{light_bulb}; // high-level module
  power_switch.press();
  power_switch.press();

  // This example respects the DIP
  BetterLightBulb better_light_bulb;
  BetterElectricPowerSwitch better_power_switch(better_light_bulb);
  better_power_switch.press();
  better_power_switch.press();

  std::cout << std::endl << "main finished. exiting..." << std::endl;
  return 0;
}

