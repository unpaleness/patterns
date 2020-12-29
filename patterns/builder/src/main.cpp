#include "pattern.hpp"

#include <platform.hpp>

int main() {
  platform::Init();

  builder::run();

  return 0;
}
