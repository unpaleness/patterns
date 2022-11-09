#include "pattern.hpp"

#include <iostream>
#include <memory>
#include <vector>

namespace composite {

namespace {

/** Base class for all components */
class ComponentBase {
public:
    virtual ~ComponentBase() = default;
    virtual void print() const { std::cout << "ComponentBase"; };
};

class ComponentContainer : public ComponentBase {
public:
    virtual void print() const override {
        std::cout << '[';
        for (size_t i = 0; i < components.size(); ++i) {
            if (i > 0) {
                std::cout << ", ";
            }
            if (components[i]) {
                components[i]->print();
            } else {
                std::cout << "<invalid>";
            }
        }
        std::cout << ']';
    }
    void add(const std::shared_ptr<ComponentBase>& newComponent) {
        components.push_back(newComponent);
    }

private:
    std::vector<std::shared_ptr<ComponentBase>> components;
};

class ComponentA : public ComponentBase {
public:
    virtual void print() const override { std::cout << "A"; }
};

class ComponentB : public ComponentBase {
public:
    virtual void print() const override { std::cout << "B"; }
};

class ComponentC : public ComponentBase {
public:
    virtual void print() const override { std::cout << "C"; }
};

void ClientCode(const std::shared_ptr<ComponentBase>& component) {
    if (component) {
        std::cout << '\n';
        component->print();
        std::cout << '\n';
    }
}

}  // namespace

void run() {
    std::cout << "\n=== Composite ===\n";
    std::cout << "\nOutput the content of component tree using method of the "
                 "root component in this tree:\n";
    auto rootComp = std::make_shared<ComponentContainer>();
    rootComp->add(std::make_shared<ComponentA>());
    rootComp->add(std::make_shared<ComponentB>());
    rootComp->add(std::make_shared<ComponentC>());
    rootComp->add(std::make_shared<ComponentBase>());
    std::shared_ptr<ComponentBase> dummy;
    rootComp->add(dummy);
    auto box1Comp = std::make_shared<ComponentContainer>();
    box1Comp->add(std::make_shared<ComponentA>());
    rootComp->add(box1Comp);
    auto box2Comp = std::make_shared<ComponentContainer>();
    box2Comp->add(std::make_shared<ComponentA>());
    box2Comp->add(std::make_shared<ComponentB>());
    box2Comp->add(std::make_shared<ComponentContainer>());
    rootComp->add(box2Comp);
    ClientCode(rootComp);
}

}  // namespace composite
