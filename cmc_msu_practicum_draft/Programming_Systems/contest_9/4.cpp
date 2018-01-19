#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <cctype>
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
    std::map<char, int> N1;
    unsigned N1size = N1.size();
    while (1) {
        for (auto grit = grammar.begin(); grit != grammar.end(); ++grit) {
            int size = grit->r.size(), count = 0, N = 0;
            for (int i = 0; i < size; ++i) {
                if (grit->valid == 1) {
                    break;
                }
                if (std::islower(grit->r[i]) || std::isdigit(grit->r[i]) || (grit->r[i] == '_')) {
                    ++count;
                } else {
                    if (N1.find(grit->r[i]) != N1.end()) {
                        ++N;
                    }
                }
            }
            if (N + count == size) {
                grit->valid = 1;
                ++N1[grit->l];
            }
        }
        if (N1size == N1.size()) {
            break;
        } else {
            N1size = N1.size();
        }
    }
    for (auto it = grammar.cbegin(); it != grammar.cend(); ++it) {
        if (it->valid == 1) {
            std::cout << it->l << ' ' << it->r << std::endl;
        }
    }
}