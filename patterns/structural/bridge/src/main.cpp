#include "pattern.hpp"

#include <platform.hpp>

int main() {
  platform::Init();

  bridge::run();

  return 0;
}
