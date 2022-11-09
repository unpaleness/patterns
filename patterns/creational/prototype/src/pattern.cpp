#include "pattern.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

namespace prototype {

namespace {

class Prototype {
public:
    Prototype() { std::cout << "Constructing Prototype\n"; }
    Prototype(const std::string& name) : name_(name) {
        std::cout << "Constructing Prototype with name\n";
    }
    virtual ~Prototype() {}
    virtual std::unique_ptr<Prototype> Clone() const = 0;
    virtual void Fly(const int distance) const {
        std::cout << "> " << name_ << " flew " << distance << " meters\n";
    }

protected:
    std::string name_{"__prototype__"};
};

enum class Type { kWing, kRocket };

class WingPrototype final : public Prototype {
public:
    WingPrototype() { std::cout << "Constructing WingPrototype\n"; }
    WingPrototype(const std::string& name, const int wings_count)
        : Prototype(name), wings_count_(wings_count) {
        std::cout
            << "Constructing WingPrototype witn name and amount of wings\n";
    }
    virtual std::unique_ptr<Prototype> Clone() const override final {
        return std::make_unique<WingPrototype>(name_, wings_count_);
    }
    virtual void Fly(const int distance) const override final {
        std::cout << "\n> " << name_ << " flaps its " << wings_count_
                  << " wings\n\n";
        Prototype::Fly(distance);
    }

private:
    int wings_count_{0};
};

class RocketPrototype final : public Prototype {
public:
    RocketPrototype() { std::cout << "Constructing RocketPrototype\n"; }
    RocketPrototype(const std::string& name, const double jet_length)
        : Prototype(name), jet_length_(jet_length) {
        std::cout << "Constructing RocketPrototype witn name and jet length\n";
    }
    virtual std::unique_ptr<Prototype> Clone() const override final {
        return std::make_unique<RocketPrototype>(name_, jet_length_);
    }
    virtual void Fly(const int distance) const override final {
        std::cout << "\n> " << name_ << "'s jet is " << jet_length_
                  << " meters long\n\n";
        Prototype::Fly(distance);
    }

private:
    double jet_length_{0.0};
};

class PrototypeFactory final {
public:
    PrototypeFactory() {
        prototypes_map_[Type::kWing] =
            std::make_unique<WingPrototype>("WingPrototype", 2);
        prototypes_map_[Type::kRocket] =
            std::make_unique<RocketPrototype>("RocketPrototype", 5.f);
    }
    std::unique_ptr<Prototype> CreatePrototype(Type type) {
        return prototypes_map_[type]->Clone();
    }

private:
    std::unordered_map<Type, std::unique_ptr<Prototype>> prototypes_map_;
};

void ClientCode(std::shared_ptr<PrototypeFactory> prototype_factory) {
    std::cout
        << "\nClient asks prototype factory to give him a wing prototype\n\n";
    prototype_factory->CreatePrototype(Type::kWing)->Fly(100);
    std::cout
        << "\nClient asks prototype factory to give him a rocket prototype\n\n";
    prototype_factory->CreatePrototype(Type::kRocket)->Fly(150);
}

}  // namespace

void run() {
    std::cout << "\n=== Prototype ===\n\n";
    ClientCode(std::make_shared<PrototypeFactory>());
    std::cout << '\n';
}

}  // namespace prototype
