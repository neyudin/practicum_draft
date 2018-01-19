#include <iostream>
/*
Grammar:
S -> aAd
A -> aAd | bBc
B -> bBc | epsilon
*/
void A(unsigned);
void B(unsigned);
void S(unsigned n) {
    std::cout << 'a';
    A(((n & 0x3ff) - 1) | (n & 0xfffffc00));
    std::cout << 'd';
}
void A(unsigned n) {
    if ((n & 0x3ff) == 0) {
        std::cout << 'b';
        B((n >> 10) - 1);
        std::cout << 'c';
    } else {
        std::cout << 'a';
        A(((n & 0x3ff) - 1) | (n & 0xfffffc00));
        std::cout << 'd';
    }
}
void B(unsigned n) {
    if (n != 0) {
        std::cout << 'b';
        B(n - 1);
        std::cout << 'c';
    }
}
int main() {
    unsigned k;
    std::cin >> k;
    if ((k < 4) || ((k & 1) == 1) || (k > 1000)) {
        return 0;
    }
    k = (k - 2) >> 1;
    k |= 0x400;
    while ((k & 0x3ff) != 0) {
        S(k);
        std::cout << std::endl;
        k = ((k & 0x3ff) - 1) | (((k >> 10) + 1) << 10);
    }
}