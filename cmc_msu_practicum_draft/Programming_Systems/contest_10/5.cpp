#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
struct Pair {
    std::string CHAR;
    std::string NEW;
};
std::multimap<std::string, Pair> nfa;
unsigned length = 0;
std::map<std::string, int> final;
std::string start, word;
bool nfadfs(std::string::iterator sit, std::string curstate, unsigned num) {
    if (sit == word.end()) {
        if (final.find(curstate) != final.end()) {
            return true;
        }
        if (num > length) {
            length = num;
        }
        return false;
    }
    auto range = nfa.equal_range(curstate);
    std::vector<std::string> news;
    bool eps = false;
    std::vector<std::string> epsnew;
    for (auto ait = range.first; ait != range.second; ++ait) {
        if ((ait->second.CHAR == "eps") && (ait->second.NEW != curstate)) {
            eps = true;
            epsnew.push_back(ait->second.NEW);
        }
        if ((ait->second.CHAR != "eps") && (ait->second.CHAR[0] == *sit)) {
            news.push_back(ait->second.NEW);
        }
    }
    bool res = false;
    for (auto vit = news.begin(); vit != news.end(); ++vit) {
        res = nfadfs(sit + 1, *vit, num + 1);
        if (res == true) {
            break;
        }
    }
    if ((res == false) && (eps == true)) {
        for (auto vit = epsnew.begin(); vit != epsnew.end(); ++vit) {
            res = nfadfs(sit, *vit, num);
            if (res == true) {
                break;
            }
        }
    }
    if (res == false) {
        if (num > length) {
            length = num;
        }
    }
    return res;
}
int main() {
    std::string CUR, CHAR, NEW;
    while (std::cin >> CUR) {
        if (CUR == "END") {
            break;
        }
        std::cin >> CHAR >> NEW;
        nfa.insert(std::pair<std::string, Pair>(CUR,{CHAR, NEW}));
    }
    while (std::cin >> CUR) {
        if (CUR == "END") {
            break;
        }
        ++final[CUR];
    }
    std::cin >> start >> word;
    bool fits = false;
    int count = length;
    fits = nfadfs(word.begin(), start, 0);
    count = length;
    if (fits == false) {
        std::cout << '0' << std::endl << count << std::endl;
    } else {
        std::cout << '1' << std::endl << word.size() << std::endl;
    }
}