#include <unix.hpp>

#include <clocale>

namespace unix {

void Init() {
    std::setlocale(LC_ALL, "en_US.UTF-8");
}

}  // namespace unix
