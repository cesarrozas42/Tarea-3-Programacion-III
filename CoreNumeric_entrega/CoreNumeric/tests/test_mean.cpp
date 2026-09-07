#include "../include/core_numeric.hpp"
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<double> data{1.0, 2.0, 3.0};
    std::cout << "mean = " << core_numeric::mean(data) << '\n';

    // NO COMPILA:
    // std::vector<std::string> words{"a", "b"};
    // core_numeric::mean(words);
    // Falla Divisible (no se puede dividir string entre size_t).

    return 0;
}
