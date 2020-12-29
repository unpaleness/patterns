#include "pattern.hpp"

#include <iostream>
#include <memory>

#include <shapes.hpp>

namespace abstract_factory {

namespace {

class Factory {
 public:
  virtual ~Factory() {}
  virtual std::shared_ptr<const shapes::Triangle> CreateTriangle() const = 0;
  virtual std::shared_ptr<const shapes::Square> CreateSquare() const = 0;
};

class RedFactory : public Factory {
 public:
  RedFactory() { std::wcout << "Constructing RedFactory\n"; }
  virtual std::shared_ptr<const shapes::Triangle> CreateTriangle()
      const override final {
    return std::make_shared<const shapes::RedTriangle>();
  }
  virtual std::shared_ptr<const shapes::Square> CreateSquare()
      const override final {
    return std::make_shared<const shapes::RedSquare>();
  }
};

class GreenFactory : public Factory {
 public:
  GreenFactory() { std::wcout << "Constructing GreenFactory\n"; }
  virtual std::shared_ptr<const shapes::Triangle> CreateTriangle()
      const override final {
    return std::make_shared<const shapes::GreenTriangle>();
  }
  virtual std::shared_ptr<const shapes::Square> CreateSquare()
      const override final {
    return std::make_shared<const shapes::GreenSquare>();
  }
};

void ClientCode(std::shared_ptr<const Factory> factory) {
  const auto square_ptr = factory->CreateSquare();
  std::wcout << "Draw a square\n";
  square_ptr->draw();
  const auto triangle_ptr = factory->CreateTriangle();
  std::wcout << "Draw a triangle\n";
  triangle_ptr->draw();
}

}  // namespace

void run() {
  std::wcout << "\n=== Abstract factory ===\n\n";
  std::wcout << "Client uses red factory\n";
  ClientCode(std::make_shared<RedFactory>());
  std::wcout << "Client uses green factory\n";
  ClientCode(std::make_shared<GreenFactory>());
  std::wcout << '\n';
}

}  // namespace abstract_factory
