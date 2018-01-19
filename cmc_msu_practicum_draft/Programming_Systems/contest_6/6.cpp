#include <iostream>

int main() {
    int m, n;
    std::cin >> m >> n;
    int r1, c1, r2, c2;
    while (std::cin >> r1 >> c1 >> r2 >> c2) {
        std::cout << std::min(std::abs(r1 - r2), m - std::abs(r1 - r2)) + 
        std::min(std::abs(c1 - c2), n - std::abs(c1 - c2)) << std::endl;
    }
}