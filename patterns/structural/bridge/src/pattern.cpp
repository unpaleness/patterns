#include "pattern.hpp"

#include <iostream>
#include <memory>
#include <string>

namespace bridge {

namespace {

/**
 * Реализация устанавливает интерфейс для всех классов реализации. Он не должен
 * соответствовать интерфейсу Абстракции. На практике оба интерфейса могут быть
 * совершенно разными. Как правило, интерфейс Реализации предоставляет только
 * примитивные операции, в то время как Абстракция определяет операции более
 * высокого уровня, основанные на этих примитивах.
 */

class Implementation {
public:
    virtual ~Implementation() {}
    virtual std::string OperationImplementation() const = 0;
};

/**
 * Каждая Конкретная Реализация соответствует определённой платформе и реализует
 * интерфейс Реализации с использованием API этой платформы.
 */
class ConcreteImplementationA final : public Implementation {
public:
    std::string OperationImplementation() const override {
        return "ConcreteImplementationA: Here's the result on the platform "
               "A.\n\n";
    }
};
class ConcreteImplementationB final : public Implementation {
public:
    std::string OperationImplementation() const override {
        return "ConcreteImplementationB: Here's the result on the platform "
               "B.\n\n";
    }
};

/**
 * Абстракция устанавливает интерфейс для «управляющей» части двух иерархий
 * классов. Она содержит ссылку на объект из иерархии Реализации и делегирует
 * ему всю настоящую работу.
 */

class Abstraction {
    /**
     * @var Implementation
     */
protected:
    std::shared_ptr<const Implementation> implementation_;

public:
    Abstraction(std::shared_ptr<const Implementation> implementation)
        : implementation_(implementation) {}

    virtual ~Abstraction() {}

    virtual std::string Operation() const {
        return "Abstraction: Base operation with:\n" +
               this->implementation_->OperationImplementation();
    }
};
/**
 * Можно расширить Абстракцию без изменения классов Реализации.
 */
class ExtendedAbstraction final : public Abstraction {
public:
    ExtendedAbstraction(std::shared_ptr<const Implementation> implementation)
        : Abstraction(implementation) {}
    std::string Operation() const override {
        return "ExtendedAbstraction: Extended operation with:\n" +
               this->implementation_->OperationImplementation();
    }
};

/**
 * За исключением этапа инициализации, когда объект Абстракции связывается с
 * определённым объектом Реализации, клиентский код должен зависеть только от
 * класса Абстракции. Таким образом, клиентский код может поддерживать любую
 * комбинацию абстракции и реализации.
 */
void ClientCode(std::shared_ptr<const Abstraction> abstraction) {
    // ...
    std::cout << abstraction->Operation();
    // ...
}
/**
 * Клиентский код должен работать с любой предварительно сконфигурированной
 * комбинацией абстракции и реализации.
 */

}  // namespace

void run() {
    std::cout << "\n=== Bridge ===\n\n";

    std::shared_ptr<const Implementation> implementation =
        std::make_shared<const ConcreteImplementationA>();
    std::shared_ptr<const Abstraction> abstraction =
        std::make_shared<const Abstraction>(implementation);
    ClientCode(abstraction);

    implementation = std::make_shared<const ConcreteImplementationB>();
    abstraction = std::make_shared<const ExtendedAbstraction>(implementation);
    ClientCode(abstraction);
}

}  // namespace bridge
