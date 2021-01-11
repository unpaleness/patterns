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
  void do_action() const {
    std::wcout << get_greeting() << get_request() << "\n\n";
  }
  virtual std::wstring get_request() const {
    return L"The default target's behavior.";
  }

 protected:
  virtual std::wstring get_greeting() const { return L"Target: "; }
};

class Adaptee {
 public:
  void do_specific_action() const {
    std::wcout << L"Adaptee: " << get_specific_request() << "\n\n";
  }
  std::wstring get_specific_request() const {
    return L".eetpadA eht fo roivaheb laicepS";
  }
};

class Adapter : public Target, public Adaptee {
 public:
  Adapter() {}
  std::wstring get_request() const override final {
    auto to_reverse = get_specific_request();
    std::reverse(to_reverse.begin(), to_reverse.end());
    return L"(TRANSLATED) " + to_reverse;
  }

 protected:
  std::wstring get_greeting() const override final { return L"Adapter: "; }
};

void ClientCode(std::shared_ptr<const Target> target) {
  target->do_action();
}

}  // namespace

void run() {
  std::wcout << "\n=== Adapter ===\n\n";
  std::wcout << "Client: I can work just fine with the Target objects:\n";
  auto target = std::make_shared<const Target>();
  ClientCode(target);
  auto adaptee = std::make_shared<const Adaptee>();
  std::wcout << "Client: The Adaptee class has a weird interface. See, I don't "
                "understand it:\n";
  adaptee->do_specific_action();
  std::wcout << "Client: But I can work with it via the Adapter:\n";
  auto adapter = std::make_shared<const Adapter>();
  ClientCode(adapter);
}

}  // namespace adapter
