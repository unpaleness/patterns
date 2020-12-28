#include "pattern.hpp"

#ifdef _WIN32
#include <windows.hpp>
#endif

int main() {
#ifdef _WIN32
  windows::Init();
#endif

  factory_method::run();

  return 0;
}
