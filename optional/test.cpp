#include <iostream>
#include "optional.hpp"

int main() {
    optional<int> opt1(42);

    if (opt1) {
        std::cout << "Value: " << opt1.value() << std::endl;
    }

    return 0;
}