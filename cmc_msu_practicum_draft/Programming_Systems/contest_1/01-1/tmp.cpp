#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>

class Rational {
private:
    int a_, b_;
    int gcd(int, int) const;
    void simplify();
public:
    Rational(int, int);
    Rational& Add(const Rational&);
    Rational& Substract(const Rational&);
    Rational& Multiply(const Rational&);
    Rational& Divide(const Rational&);
    bool EqualTo(const Rational&) const;
    int CompareTo(const Rational&) const;
    bool IsInteger() const;
    std::string ToString() const;
};

int Rational::gcd(int a, int b) const {
    a = std::abs(a);
    b = std::abs(b);
    int c;
    while (b) {
        c = b;
        b = a % b;
        a = c;
    }
    return a;
}

void Rational::simplify() {
    if (a_ != 0) {
        int c  = gcd(a_, b_);
        a_ /= c;
        b_ /= c;
        if (b_ < 0) {
            a_ *= -1;
            b_ *= -1;
        }
    } else {
        b_ = 1;
    }
}

Rational::Rational(int a = 0, int b = 1): a_(a), b_(b) {
    simplify();
}

Rational& Rational::Add(const Rational& num) {
    int divisor = gcd(b_, num.b_);
    a_ = a_ * num.b_ / divisor + num.a_ * b_ / divisor;
    b_ *= num.b_ / divisor;
    simplify();
    return *this;
}

Rational& Rational::Substract(const Rational& num) {
    int divisor = gcd(b_, num.b_);
    a_ = a_ * num.b_ / divisor - num.a_ * b_ / divisor;
    b_ *= num.b_ / divisor;
    simplify();
    return *this;
}

Rational& Rational::Multiply(const Rational& num) {
    a_ *= num.a_;
    b_ *= num.b_;
    simplify();
    return *this;
}

Rational& Rational::Divide(const Rational& num) {
    a_ *= num.b_;
    b_ *= num.a_;
    simplify();
    return *this;
}

bool Rational::EqualTo(const Rational& num) const {
    return (a_ == num.a_) && (b_ == num.b_);
}

int Rational::CompareTo(const Rational& num) const {
    int divisor = gcd(b_, num.b_);
    return a_ * num.b_ / divisor - num.a_ * b_ / divisor;
}

bool Rational::IsInteger() const {
    return b_ == 1;
}

std::string Rational::ToString() const {
    std::stringstream ss;
    ss << a_ << ":" << b_;
    return ss.str();
}
