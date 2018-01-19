#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <utility>
#include <vector>
struct Pair {
    char l;
    std::string r;
    int valid;
};
int main() {
    std::vector<struct Pair> grammar;
    char l;
    std::string r;
    while (std::cin >> l >> r) {
        grammar.push_back({l , r, 0});
    }
    std::map<char, int> V1;
    unsigned V1size = V1.size();
    while (1) {
        for (auto grit = grammar.begin(); grit != grammar.end(); ++grit) {
            int size = grit->r.size();
            if (grit->l == 'S') {
                ++V1[grit->l];
            }
            if (V1.find(grit->l) != V1.end()) {
                for (int i = 0; i < size; ++i) {
                    ++V1[grit->r[i]];
                }
            }
        }
        if (V1size == V1.size()) {
            break;
        } else {
            V1size = V1.size();
        }
    }
    for (auto grit = grammar.begin(); grit != grammar.end(); ++grit) {
        int size = grit->r.size();
        if (V1.find(grit->l) != V1.end()) {
            grit->valid = 1;
            for (int i = 0; i < size; ++i) {
                if (V1.find(grit->r[i]) == V1.end()) {
                    grit->valid = 0;
                }
            }
        }
    }
    for (auto it = grammar.cbegin(); it != grammar.cend(); ++it) {
        if (it->valid == 1) {
            std::cout << it->l << ' ' << it->r << std::endl;
        }
    }
}