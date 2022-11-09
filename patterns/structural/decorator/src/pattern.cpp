#include "pattern.hpp"

#include <iostream>
#include <memory>
#include <string>

namespace decorator {

namespace {

/** Base class for all components */
class ComponentBase {
public:
    virtual ~ComponentBase() = default;
    virtual std::string getData() const = 0;
};

/** Concrete implementation */
class Component : public ComponentBase {
public:
    virtual std::string getData() const override { return "concrete"; }
};

/**
 * Base decorator/wrapper
 * has the same interface as ComponentBase
 */
class DecoratorBase : public ComponentBase {
public:
    DecoratorBase(const std::shared_ptr<ComponentBase>& newComponent)
        : component(newComponent) {}
    virtual std::string getData() const override {
        return isValid() ? component->getData() : "<invalid>";
    }

protected:
    inline bool isValid() const { return !!component; }

protected:
    std::shared_ptr<ComponentBase> component;
};

/** Decorator variant 1 */
class Decorator1 : public DecoratorBase {
public:
    Decorator1(const std::shared_ptr<ComponentBase>& newComponent)
        : DecoratorBase(newComponent) {}
    virtual std::string getData() const override {
        return "(" + DecoratorBase::getData() + ")";
    }
};

/** Decorator variant 2 */
class Decorator2 : public DecoratorBase {
public:
    Decorator2(const std::shared_ptr<ComponentBase>& newComponent)
        : DecoratorBase(newComponent) {}
    virtual std::string getData() const override {
        return "[" + DecoratorBase::getData() + "]";
    }
};

/** Decorator variant 3 */
class Decorator3 : public DecoratorBase {
public:
    Decorator3(const std::shared_ptr<ComponentBase>& newComponent)
        : DecoratorBase(newComponent) {}
    virtual std::string getData() const override {
        return "{" + DecoratorBase::getData() + "}";
    }
};

}  // namespace

void run() {
    std::cout << "\n=== Decorator ===\n";
    auto component = std::make_shared<Component>();
    std::cout << "\nOriginal class output:\n";
    std::cout << '\n' << component->getData() << '\n';
    std::cout << "\nOutputs of various combinations of decorators wrapping "
                 "original class:\n";
    std::cout << '\n'
              << std::make_shared<Decorator1>(component)->getData() << '\n';
    std::cout << '\n'
              << std::make_shared<Decorator1>(
                     std::make_shared<Decorator2>(std::make_shared<Decorator3>(
                         std::make_shared<Decorator2>(component))))
                     ->getData()
              << '\n';
}

}  // namespace decorator
