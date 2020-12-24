#include <square.hpp>

#include <iostream>

RedSquare::RedSquare() {
  std::cout << "Constructing RedSquare\n";
}

void RedSquare::draw() const {
  std::cout << "\033[31m\u25a0\033[0m\n";
}

GreenSquare::GreenSquare() {
  std::cout << "Constructing GreenSquare\n";
}

void GreenSquare::draw() const {
  std::cout << "\033[32m\u25a0\033[0m\n";
}
