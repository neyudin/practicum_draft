class C
{
    int num;
public:
    C(double a = 0, double b = 0): num((int) (a + b)) {}
    friend int operator + (int op1, const C &op2) {
        return op1 + op2.num;
    }
    int operator ~ () const {
        return num;
    }
    C& operator ++ () {
        ++num;
        return *this;
    }
    friend int operator * (const C &op1, const C *op2) {
        return op1.num * op2->num;
    }
    friend C func1(const C *v1, double &v2) {
        return C((int) v2 + *v1, ~*v1);
    }
};