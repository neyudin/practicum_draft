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
        if (b_ < 0) {
            a_ *= -1;
            b_ = -b_;
        }
        int c  = gcd(std::abs(a_), b_);
        a_ /= c;
        b_ /= c;
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
    b_ *= num.a_;
    a_ *= num.b_;
    simplify();
    return *this;
}

bool Rational::EqualTo(const Rational& num) const {
    return a_ == num.a_ && b_ == num.b_;
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

/*int main()
{
    Rational n = Rational(5, 73);
    Rational p = Rational(578 * 24, 24);
    //p.Divide(Rational(578, -1));
    std::cout << p.EqualTo(Rational(-578, -1)) << std::endl;
    n.Substract(p);
    std::cout << n.ToString() << std::endl;
    // Создание объектов  
    Rational q = Rational(1, 3), w(1, 3);  
    Rational s = 4;  
    Rational z = q;
    std::cout << q.ToString() << std::endl;
    std::cout << w.ToString() << std::endl;
    std::cout << s.ToString() << std::endl;
    std::cout << z.ToString() << std::endl;
 
    // Арифметические операции  
    s.Add(q);       // значение s увеличивается на значение q  
                 // (значение s меняется)  
        std::cout << s.ToString() << std::endl;
    s.Substract(q); // значение s изменяется путем вычитания q  
        std::cout << s.ToString() << std::endl;
    s.Multiply(q);  // значение s изменяется путем домножения на q  
        std::cout << s.ToString() << std::endl;
    s.Divide(q);    // значение s изменяется путем деления на q  
        std::cout << s.ToString() << std::endl;
 
    s.Add(q).Multiply(w); // значение s меняется путем инкрементирования q  
                       // с последующим домножением на w  
        std::cout << s.ToString() << std::endl;
 
    // Логические операции  
    std::cout << s.EqualTo(w) << std::endl; // возращает булево значение, равно ли значение s значению w  
        //std::cout << s.ToString() << std::endl;
    std::cout << s.CompareTo(w) << std::endl; // возвращает целое > 0, если s > w,  
                 // иначе возвращает целое < 0, если s < w,  
                 // иначе возвращает 0  
        //std::cout << s.ToString() << std::endl;
    std::cout << s.IsInteger() << std::endl;   // возвращает булево значение, является ли s целым числом  
        //std::cout << s.ToString() << std::endl;
 
    // Строковое представление в формате a:b 
    std::string str = w.ToString();  // вернет 1:3
        //std::cout << s.ToString() << std::endl;
        std::cout << str << std::endl;
 
    // Создание массивов  
    Rational arr[10];
    arr[5].Add(s);
    std::cout << arr[1].ToString() << std::endl;
}*/