#include "pattern.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

namespace adapter {

namespace {

class Target {
 public:
  virtual ~Target() = default;
  virtual std::wstring Request() const {
    return L"Target: The default target's behavior.";
  }
};

class Adaptee {
 public:
  std::wstring SpecificRequest() const {
    return L"Adaptee: .eetpadA eht fo roivaheb laicepS";
  }
};

class Adapter : public Target, public Adaptee {
 public:
  Adapter() {}
  std::wstring Request() const override {
    std::wstring to_reverse = SpecificRequest();
    std::reverse(to_reverse.begin(), to_reverse.end());
    return L"Adapter: (TRANSLATED) " + to_reverse;
  }
};

void ClientCode(std::shared_ptr<const Target> target) {
  std::wcout << target->Request() << "\n\n";
}

}  // namespace

void run() {
  std::wcout << "\n=== Factory method ===\n\n";
  std::wcout << "Client: I can work just fine with the Target objects:\n";
  auto target = std::make_shared<const Target>();
  ClientCode(target);
  auto adaptee = std::make_shared<const Adaptee>();
  std::wcout << "Client: The Adaptee class has a weird interface. See, I don't "
               "understand it:\n";
  std::wcout << adaptee->SpecificRequest() << "\n\n";
  std::wcout << "Client: But I can work with it via the Adapter:\n";
  auto adapter = std::make_shared<const Adapter>();
  ClientCode(adapter);
}

}  // namespace adapter
