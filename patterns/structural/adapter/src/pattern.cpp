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
        std::cout << get_greeting() << get_request() << "\n\n";
    }
    virtual std::string get_request() const {
        return "The default target's behavior.";
    }

protected:
    virtual std::string get_greeting() const { return "Target: "; }
};

class Adaptee {
public:
    void do_specific_action() const {
        std::cout << "Adaptee: " << get_specific_request() << "\n\n";
    }
    std::string get_specific_request() const {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

class Adapter : public Target, public Adaptee {
public:
    Adapter() {}
    std::string get_request() const override final {
        auto to_reverse = get_specific_request();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "(TRANSLATED) " + to_reverse;
    }

protected:
    std::string get_greeting() const override final { return "Adapter: "; }
};

void ClientCode(std::shared_ptr<const Target> target) {
    target->do_action();
}

}  // namespace

void run() {
    std::cout << "\n=== Adapter ===\n\n";
    std::cout << "Client: I can work just fine with the Target objects:\n";
    auto target = std::make_shared<const Target>();
    ClientCode(target);
    auto adaptee = std::make_shared<const Adaptee>();
    std::cout
        << "Client: The Adaptee class has a weird interface. See, I don't "
           "understand it:\n";
    adaptee->do_specific_action();
    std::cout << "Client: But I can work with it via the Adapter:\n";
    auto adapter = std::make_shared<const Adapter>();
    ClientCode(adapter);
}

}  // namespace adapter
