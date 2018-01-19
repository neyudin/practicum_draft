#include <iostream>
#include <sstream>
#include <cmath>

class Rectangle : public Figure
{
    double a = 0, b = 0;
public:
    static Rectangle *make(const std::string s) {
        std::istringstream ss(s);
        Rectangle *obj = new Rectangle;
        ss >> obj->a >> obj->b;
        return obj;
    }
    double get_square() const {
        return a * b;
    }
};

class Square : public Figure
{
    double a = 0;
public:
    static Square *make(const std::string s) {
        std::istringstream ss(s);
        Square *obj = new Square;
        ss >> obj->a;
        return obj;
    }
    double get_square() const {
        return a * a;
    }
};

class Circle : public Figure
{
    double a = 0;
public:
    static Circle *make(const std::string s) {
        std::istringstream ss(s);
        Circle *obj = new Circle;
        ss >> obj->a;
        return obj;
    }
    double get_square() const {
        return a * a * asin(1.0) * 2;
    }
};