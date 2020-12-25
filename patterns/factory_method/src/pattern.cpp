#include "pattern.hpp"

#include <iostream>
#include <memory>

#include <shapes.hpp>

namespace factory_method {

namespace {

class SquareCreator {
 public:
  virtual ~SquareCreator() {}
  void draw() const {
    std::cout << "SquareCreator creates a Square\n";
    const auto square_ptr = factory_method();
    std::cout << "SquareCreator calls method \"draw\" of a Square\n";
    square_ptr->draw();
  }

 protected:
  virtual std::shared_ptr<const shapes::Square> factory_method() const = 0;
};

class RedSquareCreator : public SquareCreator {
 public:
  RedSquareCreator() { std::cout << "Constructing RedSquareCreator\n"; }

 private:
  virtual std::shared_ptr<const shapes::Square> factory_method()
      const override final {
    return std::make_shared<shapes::RedSquare>();
  }
};

class GreenSquareCreator : public SquareCreator {
 public:
  GreenSquareCreator() { std::cout << "Constructing GreenSquareCreator\n"; }

 private:
  virtual std::shared_ptr<const shapes::Square> factory_method()
      const override final {
    return std::make_shared<shapes::GreenSquare>();
  }
};

void ClientCode(std::shared_ptr<const SquareCreator> creator) {
  std::cout << "Client calls method \"draw\" of SquareCreator\n";
  creator->draw();
}

}  // namespace

void run() {
  std::cout << "\n=== Factory method ===\n\n";
  std::cout << "Client uses red square creator\n";
  ClientCode(std::make_shared<RedSquareCreator>());
  std::cout << "Client uses green square creator\n";
  ClientCode(std::make_shared<GreenSquareCreator>());
  std::cout << '\n';
}

}  // namespace factory_method
