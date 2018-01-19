#include <iostream>
class C
{
    int num;
public:
    C (int x = 0): num(2 * x) {}
    C (const C &c) {
        num = c.num;
    }
    friend C operator + (const C &c1, const C &c2) {
        C tmp;
        tmp.num = 2 * (c1.num + c2.num);
        return tmp;
    }
    int get() {
        return num;
    }
};