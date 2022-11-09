#include "pattern.hpp"

#include <iostream>
#include <memory>
#include <string>

namespace facade {

namespace {

enum class Size : uint8_t {
    Small = 0,
    Medium = 1,
    Large = 2,
};

enum class Beverage : uint8_t {
    None = 0,
    Espresso = 1,
    Capuccino = 2,
};

namespace Helper {

static std::string sizeToWString(const Size size) {
    switch (size) {
        case Size::Small:
            return "Small";
        case Size::Medium:
            return "Medium";
        case Size::Large:
            return "Large";
        default:
            return "<Invalid size>";
    }
}

static std::string beverageToWString(const Beverage beverage) {
    switch (beverage) {
        case Beverage::None:
            return "None";
        case Beverage::Espresso:
            return "Espresso";
        case Beverage::Capuccino:
            return "Capuccino";
        default:
            return "<Invalid beverage>";
    }
}

}  // namespace Helper

/** Struct representing a cup */
class Cup {
public:
    Cup(const Size newSize, const Beverage newBeverage)
        : size(newSize), beverage(newBeverage) {}
    void setBeverage(const Beverage newBeverage) { beverage = newBeverage; }
    std::string toString() const {
        return "{size: " + Helper::sizeToWString(size) +
               ", beverage: " + Helper::beverageToWString(beverage) + "}";
    }

private:
    Size size{Size::Small};
    Beverage beverage{Beverage::None};
};

/** Class with cups */
class Cupboard {
public:
    std::shared_ptr<Cup> getCup(const Size size) {
        return std::make_shared<Cup>(size, Beverage::None);
    }
};

/** Class representing coffemachine */
class CoffeeMachine {
public:
    void addCup(const std::shared_ptr<Cup>& newCup) {
        cup = newCup;
        std::cout << "CoffeeMachine: a new cup inserted: " << cup->toString()
                  << "\n";
    }

    void brew(const Beverage newBeverage) {
        if (!cup) {
            std::cout << "CoffeeMachine: there's no cup inserted\n";
            return;
        }
        cup->setBeverage(newBeverage);
        std::cout << "CoffeeMachine: brewed " << cup->toString() << "\n";
    }

    std::shared_ptr<Cup> removeCup() {
        if (!cup) {
            std::cout << "CoffeeMachine: no cup\n";
            return nullptr;
        }
        auto returnCup = cup;
        cup.reset();
        return returnCup;
    }

private:
    std::shared_ptr<Cup> cup;
};

/** Facade class to brew a cup of coffee */
class FacadeToBrewCoffee {
public:
    static std::shared_ptr<Cup> brew(const Size size, const Beverage beverage) {
        auto cupboard = std::make_shared<Cupboard>();
        auto cup = cupboard->getCup(size);
        auto coffeeMachine = std::make_shared<CoffeeMachine>();
        coffeeMachine->addCup(cup);
        coffeeMachine->brew(beverage);
        return coffeeMachine->removeCup();
    }
};

}  // namespace

void run() {
    std::cout << "\n=== Facade ===\n";
    std::cout << "\nClient code uses facade class CoffeeMaker to brew coffee. "
                 "Coffee itself uses other classes to implement each step.\n";
    auto facadeToBrewCoffee = std::make_shared<FacadeToBrewCoffee>();
    std::cout << "\nBrewing cup 1\n";
    auto cup1 = facadeToBrewCoffee->brew(Size::Medium, Beverage::Espresso);
    std::cout << "\nCup 1: " << cup1->toString() << "\n";
    std::cout << "\nBrewing cup 2\n";
    auto cup2 = facadeToBrewCoffee->brew(Size::Small, Beverage::Capuccino);
    std::cout << "\nCup 2: " << cup2->toString() << "\n";
    std::cout << "\nBrewing cup 3\n";
    auto cup3 = facadeToBrewCoffee->brew(Size::Large, Beverage::Capuccino);
    std::cout << "\nCup 3: " << cup3->toString() << "\n";
}

}  // namespace facade
