#include <iostream>
#include <vector>
#include <list>

void process (const std::vector<int> &v, std::list<int> &l, int step) {
    auto lit = l.begin();
    for (auto vit = v.cbegin(); (vit < v.cend()) && (lit != l.end()); vit += step) {
        *lit = *vit;
        ++lit;
    }
    auto lrit = l.rbegin();
    if (lrit != l.rend()) {
        for (; lrit != l.rend(); ++lrit) {
            std::cout << *lrit << std::endl;
        }
    }
}