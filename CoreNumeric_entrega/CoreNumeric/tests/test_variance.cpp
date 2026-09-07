#include "../include/core_numeric.hpp"
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<double> data{1.0, 2.0, 3.0};
    std::cout << "variance = " << core_numeric::variance(data) << '\n';

    // NO COMPILA:
    // std::vector<std::string> words{"a", "b", "c"};
    // core_numeric::variance(words);
    // Falla Addable, Divisible y las operaciones requeridas por variance.

    return 0;
}
