#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <memory>
#include <functional>
#include <algorithm>

int main() {
    std::map<std::string, double> marks;
    std::map<std::string, int> num;
    std::string f, s;
    while (std::getline(std::cin, s)) {
        std::istringstream ss(s);
        ss >> f;
        std::getline(ss, s);
        marks[f] += atoi(s.c_str());
        ++num[f];
    }
    for (auto i = marks.begin(); i != marks.end(); ++i) {
        i->second /= num[i->first];
    }
    for (auto i = marks.begin(); i != marks.end(); ++i) {
        std::cout << i->first << ' ' << i->second << std::endl;
    }
}