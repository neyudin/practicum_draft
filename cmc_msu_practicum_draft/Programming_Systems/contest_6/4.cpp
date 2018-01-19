#include <iostream>

class Result
{
    int m, n;
public:
    Result(int a, int b): m(a), n(b) {}
    int getm() const {
            return m;
    }
    int getn() const {
            return n;
    }
};

int f(Result r) {
    try {
        if (r.getm() == 0) {
            return r.getn() + 1;
        }
        if ((r.getm() > 0) && (r.getn() == 0)) {
            throw Result(r.getm() - 1, 1);
        }
        if ((r.getm() > 0) && (r.getn() > 0)) {
            throw Result(r.getm() - 1, f(Result(r.getm(), r.getn() - 1)));
        }
    } catch (Result &res) {
        return f(res);
    }
    return 1;
}

int main() {
    int m, n;
    std::cin >> m >> n;
    Result r(m, n);
    std::cout << f(r) << std::endl;
}