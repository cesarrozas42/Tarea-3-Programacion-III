#include "../include/core_numeric.hpp"
#include <iostream>

int main() {
    auto s1 = core_numeric::sum_variadic(1, 2, 33, 4);
    auto s2 = core_numeric::mean_variadic(0.1, 2.0, 3.0, 4.0);
    auto s3 = core_numeric::variance_variadic(1.0, 2.0, 3.0, 4.0);
    auto s4 = core_numeric::max_variadic(1.0, 2.7, 3.0, 4.0);

    std::cout << "sum_variadic = " << s1 << '\n';
    std::cout << "mean_variadic = " << s2 << '\n';
    std::cout << "variance_variadic = " << s3 << '\n';
    std::cout << "max_variadic = " << s4 << '\n';

    // NO COMPILA:
    // core_numeric::sum_variadic();
    // Falla porque se exige al menos un argumento.

    // NO COMPILA:
    // core_numeric::max_variadic(1, 2.0, 3);
    // Esta implementación exige que los tipos sean iguales.

    return 0;
}
