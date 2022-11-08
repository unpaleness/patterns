#include "pattern.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

namespace composite {

namespace {

/** Base class for all components */
class ComponentBase {
public:
    virtual ~ComponentBase() = default;
    virtual void print() const { std::wcout << "ComponentBase"; };
};

class ComponentContainer : public ComponentBase {
public:
    virtual void print() const override {
        std::wcout << '[';
        for (size_t i = 0; i < components.size(); ++i) {
            if (i > 0) {
                std::wcout << ", ";
            }
            if (components[i]) {
                components[i]->print();
            } else {
                std::wcout << "<invalid>";
            }
        }
        std::wcout << ']';
    }
    void add(const std::shared_ptr<ComponentBase>& newComponent) {
        components.push_back(newComponent);
    }

private:
    std::vector<std::shared_ptr<ComponentBase>> components;
};

class ComponentA : public ComponentBase {
public:
    virtual void print() const override { std::wcout << "A"; }
};

class ComponentB : public ComponentBase {
public:
    virtual void print() const override { std::wcout << "B"; }
};

class ComponentC : public ComponentBase {
public:
    virtual void print() const override { std::wcout << "C"; }
};

void ClientCode(const std::shared_ptr<ComponentBase>& component) {
    if (component) {
        component->print();
    }
}

}  // namespace

void run() {
    std::wcout << "\n=== Composite ===\n\n";
    std::wcout << "Output the content of component tree using method of the "
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
