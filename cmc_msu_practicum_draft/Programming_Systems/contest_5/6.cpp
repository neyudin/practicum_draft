#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <cmath>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>


class Figure
{
public:
    virtual double get_square() const = 0;
    virtual std::string to_string() const = 0;
    virtual ~Figure() {};
};

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
    std::string to_string() const {
        std::ostringstream ss;
        ss << "R " << a << " " << b;
        return ss.str();
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
    std::string to_string() const {
        std::ostringstream ss;
        ss << "S " << a;
        return ss.str();
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
    std::string to_string() const {
        std::ostringstream ss;
        ss << "C " << a;
        return ss.str();
    }
    double get_square() const {
        return a * a * asin(1.0) * 2;
    }
};

int main () {
    std::string c, s;
    std::vector<std::unique_ptr<Figure>> figures;

    const std::map<char, std::function<Figure*(const std::string&)>> FigureFactory = {
        {'R', Rectangle::make}, 
        {'S', Square::make}, 
        {'C', Circle::make}
    };

    while (std::getline(std::cin, s)) {
        std::istringstream ss(s);
        ss >> c;
        std::getline(ss, s);
        figures.push_back(std::unique_ptr<Figure>(FigureFactory.at(c[0])(s)));
    }

    std::stable_sort(figures.begin(), figures.end(), [](const std::unique_ptr<Figure> &a, 
        const std::unique_ptr<Figure> &b){
            return a->get_square() < b->get_square();
    });

    for (const auto &i: figures) {
        std::cout << i->to_string() << std::endl;
    }
}