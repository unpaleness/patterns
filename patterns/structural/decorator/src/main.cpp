#include "pattern.hpp"

#include <platform.hpp>

int main() {
  platform::Init();

  decorator::run();

  return 0;
}
