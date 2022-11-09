#include "pattern.hpp"

#include <platform.hpp>

int main() {
    platform::Init();

    abstract_factory::run();

    return 0;
}
