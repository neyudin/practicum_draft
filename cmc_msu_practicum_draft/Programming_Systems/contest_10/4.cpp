#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
struct Pair {
    char CHAR;
    std::string NEW;
};
int main() {
    std::multimap<std::string, Pair> dfa;
    std::map<std::string, int> final;
    std::string CUR, NEW;
    char CHAR;
    while (std::cin >> CUR) {
        if (CUR == "END") {
            break;
        }
        std::cin >> CHAR >> NEW;
        dfa.insert(std::pair<std::string, Pair>(CUR,{CHAR, NEW}));
    }
    while (std::cin >> CUR) {
        if (CUR == "END") {
            break;
        }
        ++final[CUR];
    }
    std::string start, word;
    std::cin >> start >> word;
    bool fits = true;
    int count = 0;
    for (auto wit = word.cbegin(); wit != word.cend(); ++wit) {
        auto range = dfa.equal_range(start);
        bool found = false;
        for (auto ait = range.first; ait != range.second; ++ait) {
            if (ait->second.CHAR == *wit) {
                found = true;
                start = ait->second.NEW;
                ++count;
                break;
            }
        }
        if (found == false) {
            fits = false;
            break;
        }
    }
    if ((fits == false) || (final.find(start) == final.end())) {
        std::cout << '0' << std::endl;
    } else {
        std::cout << '1' << std::endl;
    }
    std::cout << count << std::endl << start << std::endl;
}