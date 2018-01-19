#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <cmath>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>




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