#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

void process(const std::vector<int> &v, std::list<int> &lst) {
    if (lst.empty() || v.empty()) {
        return;
    }
    std::vector<int> tmpv = v;
    std::sort(tmpv.begin(), tmpv.end());
    auto last = std::unique(tmpv.begin(), tmpv.end());
    tmpv.erase(last, tmpv.end());
    last = tmpv.begin();
    while (last < tmpv.end() && *last < 1) {
        ++last;
    }
    tmpv.erase(tmpv.begin(), last);
    last = tmpv.begin();
    size_t size = lst.size();
    while (last < tmpv.end() && *last <= static_cast<int>(size)) {
        ++last;
    }
    tmpv.erase(last, tmpv.end());
    int num = 0;
    for (auto i = tmpv.cbegin(); i < tmpv.cend(); ++i) {
        auto lit = lst.begin();
        std::advance(lit, *i - num - 1);
        lst.erase(lit);
        ++num;
    }
}