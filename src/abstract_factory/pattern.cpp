#include "pattern.hpp"

#include <common/square.hpp>

#include <iostream>
#include <memory>

namespace abstract_factory {

namespace {

class Triangle {
 public:
  virtual ~Triangle() {}
  virtual void draw() const = 0;
  virtual void draw_with_square(std::shared_ptr<const Square>) const = 0;
};

class RedTriangle : public Triangle {
 public:
  RedTriangle() { std::cout << "Constructing RedTriangle\n"; }
  virtual void draw() const override final {
    std::cout << "\033[31m\u25b2\033[0m\n";
  }
  virtual void draw_with_square(
      std::shared_ptr<const Square> square_ptr) const override final {
    std::cout << "\033[31m\u25b2\033[0m";
    square_ptr->draw();
  }
};

class GreenTriangle : public Triangle {
 public:
  GreenTriangle() { std::cout << "Constructing GreenTriangle\n"; }
  virtual void draw() const override final {
    std::cout << "\033[32m\u25b2\033[0m\n";
  }
  virtual void draw_with_square(
      std::shared_ptr<const Square> square_ptr) const override final {
    std::cout << "\033[32m\u25b2\033[0m";
    square_ptr->draw();
  }
};

class Factory {
 public:
  virtual std::shared_ptr<const Triangle> CreateTriangle() const = 0;
  virtual std::shared_ptr<const Square> CreateSquare() const = 0;
};

class RedFactory : public Factory {
 public:
  RedFactory() { std::cout << "Constructing RedFactory\n"; }
  virtual std::shared_ptr<const Triangle> CreateTriangle()
      const override final {
    return std::make_shared<const RedTriangle>();
  }
  virtual std::shared_ptr<const Square> CreateSquare() const override final {
    return std::make_shared<const RedSquare>();
  }
};

class GreenFactory : public Factory {
 public:
  GreenFactory() { std::cout << "Constructing GreenFactory\n"; }
  virtual std::shared_ptr<const Triangle> CreateTriangle()
      const override final {
    return std::make_shared<const GreenTriangle>();
  }
  virtual std::shared_ptr<const Square> CreateSquare() const override final {
    return std::make_shared<const GreenSquare>();
  }
};

void ClientCode(std::shared_ptr<const Factory> factory) {
  const auto square_ptr = factory->CreateSquare();
  const auto triangle_ptr = factory->CreateTriangle();
  std::cout << "Draw a square\n";
  square_ptr->draw();
  std::cout << "Draw a triangle\n";
  triangle_ptr->draw();
  std::cout << "Draw a triangle with square\n";
  triangle_ptr->draw_with_square(square_ptr);
}

}  // namespace

void run() {
  std::cout << "\n=== Abstract factory ===\n\n";
  std::cout << "Client uses red factory\n";
  ClientCode(std::make_shared<RedFactory>());
  std::cout << "Client uses green factory\n";
  ClientCode(std::make_shared<GreenFactory>());
  std::cout << '\n';
}

}  // namespace abstract_factory
