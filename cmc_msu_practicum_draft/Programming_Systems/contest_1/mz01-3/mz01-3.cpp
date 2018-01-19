#include <iostream>

class Sum {
    int c_;
    public:
        Sum(int a=0, int b=0) {
            c_ = a + b;
        }
        int get(void) {
            return c_;
        }
};