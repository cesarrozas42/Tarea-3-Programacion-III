#include "../include/core_numeric.hpp"
#include <iostream>
#include <vector>

struct Number {
    double value{};

    Number operator+(const Number& other) const {
        return {value + other.value};
    }
};

int main() {
    std::vector<double> v{1.0, 2.0, 3.0, 4.0};

    auto r = core_numeric::transform_reduce(v, [](double x) {
        return x * x;
    });

    std::cout << "sum of squares = " << r << '\n';

    std::vector<Number> numbers{{1}, {2}, {3}};

    auto result = core_numeric::transform_reduce(numbers, [](Number n) {
        return n;
    });

    std::cout << "custom type result = " << result.value << '\n';

    // NO COMPILA:
    // auto bad = core_numeric::transform_reduce(v, [](double x) {
    //     return std::string("x");
    // });
    // La reducción necesita que el resultado pueda acumularse con +.

    return 0;
}
