#include <iostream>
#include <sstream>
#include <iomanip>

int main() {
    int count = 0;
    int c = 0;
    char cc = 0;
    while ((c = std::cin.get()) != EOF) {
        if (c == cc) {
            ++count;
        } else {
            if (count < 5 && cc != '#') {
                for (int i = 0; i < count; ++i) {
                    std::cout << cc;
                }
            } else {
                std::cout << '#' << cc << std::hex << count << '#';
            }
            cc = c;
            count = 1;
        }
    }
    if (count < 5 && cc != '#') {
        for (int i = 0; i < count; ++i) {
            std::cout << cc;
        }
    } else {
        std::cout << '#' << cc << std::hex << count << '#';
    }
}