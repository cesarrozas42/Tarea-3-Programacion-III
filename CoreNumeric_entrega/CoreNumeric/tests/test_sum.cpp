#include "../include/core_numeric.hpp"
#include <iostream>
#include <string>
#include <vector>

struct Point {
    int x{};
    int y{};

    Point operator+(const Point& other) const {
        return {x + other.x, y + other.y};
    }
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
    return os << "(" << p.x << ", " << p.y << ")";
}

int main() {
    std::vector<int> numbers{1, 2, 3, 4};
    std::cout << "sum int = " << core_numeric::sum(numbers) << '\n';

    std::vector<double> decimals{1.5, 2.5, 3.0};
    std::cout << "sum double = " << core_numeric::sum(decimals) << '\n';

    std::vector<Point> points{{1, 2}, {3, 4}};
    std::cout << "sum Point = " << core_numeric::sum(points) << '\n';

    // NO COMPILA:
    // std::vector<std::string> words{"Hola", "Mundo"};
    // core_numeric::sum(words);
    // Falla Addable porque string + string no garantiza el mismo tipo
    // según el concept definido para esta tarea.

    // Tampoco compila si el argumento no es Iterable:
    // int x = 5;
    // core_numeric::sum(x);

    return 0;
}
