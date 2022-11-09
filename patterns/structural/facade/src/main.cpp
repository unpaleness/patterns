#include "pattern.hpp"

#include <platform.hpp>

int main() {
  platform::Init();

  facade::run();

  return 0;
}
