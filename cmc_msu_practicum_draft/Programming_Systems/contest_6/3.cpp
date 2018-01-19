#include <iostream>

class A
{
    int n;
public:
    A(int a): n(a) {}
    ~A() {
        std::cout << n << std::endl;
    }
};

void f() {
    int a;
    if (std::cin >> a) {
        try {
            throw A(a);
        } catch (A &a) {
            f();
        }
    }
}

int main() {
    f();
}