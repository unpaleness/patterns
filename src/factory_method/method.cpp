#include "method.hpp"

#include <iostream>
#include <memory>
#include <string>

namespace factory_method {

namespace {

class Animal {
 public:
  virtual ~Animal() {}
  virtual void some_operation() const = 0;
};

class Dog : public Animal {
 public:
  Dog() { std::cout << "Constructing Dog\n"; }
  virtual void some_operation() const override final {
    std::cout << "Wow-wow!\n";
  }
};

class Cat : public Animal {
 public:
  Cat() { std::cout << "Constructing Cat\n"; }
  virtual void some_operation() const override final {
    std::cout << "Meow-meow!\n";
  }
};

class AnimalCreator {
 public:
  virtual ~AnimalCreator() {}
  virtual std::shared_ptr<Animal> factory_method() const = 0;
  void some_operation() const {
    std::cout << "AnimalCreator creates an Animal\n";
    const auto animal_ptr = factory_method();
    std::cout << "AnimalCreator makes some operation on Animal\n";
    animal_ptr->some_operation();
  }
};

class DogCreator : public AnimalCreator {
 public:
  DogCreator() { std::cout << "Constructing DogCreator\n"; }
  virtual std::shared_ptr<Animal> factory_method() const override final {
    return std::make_shared<Dog>();
  }
};

class CatCreator : public AnimalCreator {
 public:
  CatCreator() { std::cout << "Constructing CatCreator\n"; }
  virtual std::shared_ptr<Animal> factory_method() const override final {
    return std::make_shared<Cat>();
  }
};

void ClientCode(const AnimalCreator& creator) {
  std::cout << "Client makes some operation on AnimalCreator\n";
  creator.some_operation();
}

}  // namespace

void run() {
  std::cout << "\n=== Factory method ===\n";
  const auto dog_creator = std::make_shared<DogCreator>();
  ClientCode(*dog_creator);
  const auto cat_creator = std::make_shared<CatCreator>();
  ClientCode(*cat_creator);
}

}  // namespace factory_method
