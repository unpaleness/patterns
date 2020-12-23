#include "method.hpp"

#include <iostream>
#include <memory>
#include <string>

namespace factory_method {

namespace {

class Animal {
 public:
  virtual ~Animal() {}
  virtual std::string get_phrase() const = 0;
};

class Dog : public Animal {
 public:
  virtual std::string get_phrase() const override final { return "I'm a dog!"; }
};

class Cat : public Animal {
 public:
  virtual std::string get_phrase() const override final { return "I'm a cat!"; }
};

class AnimalCreator {
 public:
  virtual ~AnimalCreator() {}
  virtual std::shared_ptr<Animal> factory_method() const = 0;
  void ask_animal() const {
    const auto animal_ptr = factory_method();
    std::cout << "The animal says: " << animal_ptr->get_phrase() << '\n';
  }
};

class DogCreator : public AnimalCreator {
 public:
  virtual std::shared_ptr<Animal> factory_method() const override final {
    return std::make_shared<Dog>();
  }
};

class CatCreator : public AnimalCreator {
 public:
  virtual std::shared_ptr<Animal> factory_method() const override final {
    return std::make_shared<Cat>();
  }
};

/**
 * Клиентский код работает с экземпляром конкретного создателя, хотя и через его
 * базовый интерфейс. Пока клиент продолжает работать с создателем через базовый
 * интерфейс, вы можете передать ему любой подкласс создателя.
 */
void ClientCode(const AnimalCreator& creator) {
  creator.ask_animal();
}

}  // namespace

void run() {
  std::cout << "=== Factory method (virtual constructor) ===" << '\n';
  const auto dog_creator = std::make_shared<DogCreator>();
  ClientCode(*dog_creator);
  const auto cat_creator = std::make_shared<CatCreator>();
  ClientCode(*cat_creator);
}

}  // namespace factory_method
