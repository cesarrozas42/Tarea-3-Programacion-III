#include "../include/core_numeric.hpp"
#include <iostream>

int main() {
    constexpr int i = core_numeric::normalize(10);
    constexpr double d = core_numeric::normalize(10.5);

    std::cout << "integer branch = " << i << '\n';
    std::cout << "floating branch = " << d << '\n';

    // if constexpr selecciona la rama durante compilación:
    // int -> std::is_integral_v<T> es true
    // double -> std::is_integral_v<T> es false

    return 0;
}
