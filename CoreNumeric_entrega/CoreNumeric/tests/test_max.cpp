#include "../include/core_numeric.hpp"
#include <iostream>
#include <string>
#include <vector>

struct Coordinate {
    int x{};
    int y{};

    bool operator<(const Coordinate& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

std::ostream& operator<<(std::ostream& os, const Coordinate& c) {
    return os << "(" << c.x << ", " << c.y << ")";
}

int main() {
    std::vector<double> data{1.0, 2.7, 0.3};
    std::cout << "max double = " << core_numeric::max(data) << '\n';

    std::vector<Coordinate> points{{1, 2}, {5, 1}, {3, 8}};
    std::cout << "max Coordinate = " << core_numeric::max(points) << '\n';

    struct NoOrder { int value{}; };
    // NO COMPILA:
    // std::vector<NoOrder> invalid{{1}, {2}};
    // core_numeric::max(invalid);
    // Falla Comparable porque NoOrder no tiene operator<.

    return 0;
}
