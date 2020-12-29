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
    std::wcout << "SquareCreator creates a Square\n";
    const auto square_ptr = factory_method();
    std::wcout << "SquareCreator calls method \"draw\" of a Square\n";
    square_ptr->draw();
  }

 protected:
  virtual std::shared_ptr<const shapes::Square> factory_method() const = 0;
};

class RedSquareCreator : public SquareCreator {
 public:
  RedSquareCreator() { std::wcout << "Constructing RedSquareCreator\n"; }

 private:
  virtual std::shared_ptr<const shapes::Square> factory_method()
      const override final {
    return std::make_shared<shapes::RedSquare>();
  }
};

class GreenSquareCreator : public SquareCreator {
 public:
  GreenSquareCreator() { std::wcout << "Constructing GreenSquareCreator\n"; }

 private:
  virtual std::shared_ptr<const shapes::Square> factory_method()
      const override final {
    return std::make_shared<shapes::GreenSquare>();
  }
};

void ClientCode(std::shared_ptr<const SquareCreator> creator) {
  std::wcout << "Client calls method \"draw\" of SquareCreator\n";
  creator->draw();
}

}  // namespace

void run() {
  std::wcout << "\n=== Factory method ===\n\n";
  std::wcout << "Client uses red square creator\n";
  ClientCode(std::make_shared<RedSquareCreator>());
  std::wcout << "Client uses green square creator\n";
  ClientCode(std::make_shared<GreenSquareCreator>());
  std::wcout << '\n';
}

}  // namespace factory_method
