#include <iostream>
#include <cctype>
#include <cstdio>

/*
Grammar
S 1A0
A 1A0 | 0B1
B 0B1 | epsilon
*/
void A();
void B();
void D();
void S() {
    if (std::isspace(std::cin.peek()) || (std::cin.peek() == EOF)) {
        return;
    }
    A();
}
void A() {
    char c;
    if (std::cin >> c) {
        if (c == '1') {
            A();
        }
        if (c == '0') {
            std::cout << '1';
            B();
        }
    }
}
void B() {
    char c;
    if (std::isspace(std::cin.peek()) || (std::cin.peek() == EOF)) {
        return;
    }
    if (std::cin >> c) {
        if (c == '1') {
            std::cout << '0';
            D();
        }
        if (c == '0') {
            std::cout << '1';
            B();
        }
    }
}
void D() {
    char c;
    if (std::isspace(std::cin.peek()) || (std::cin.peek() == EOF)) {
        return;
    }
    if (std::cin >> c) {
        if ((c == '0') || (c == '1')) {
            std::cout << '0';
            D();
        }
    }
}
int main() {
    char c;
    while (std::cin >> c) {
        if (isspace(c)) {
            continue;
        }
        S();
        std::cout << std::endl;
    }
}