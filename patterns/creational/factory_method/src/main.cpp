#include "pattern.hpp"

#include <platform.hpp>

int main() {
    platform::Init();

    factory_method::run();

    return 0;
}
