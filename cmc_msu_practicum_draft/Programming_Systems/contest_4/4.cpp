#include <iostream>
#include <vector>
void process(const std::vector<int> &v1, std::vector<int> &v2)
{
    auto vit2 = v2.begin();
    auto vit1 = v1.cbegin();
    int  size2 = v2.size();
    int num = 0;
    for (int i = 0; (vit1 != v1.cend()) && (i < size2); ++vit1, ++i, ++num) {
        vit2 = v2.begin();
        std::advance(vit2, num);
        if (*vit1 > *vit2) {
            v2.push_back(*vit1);
        }
    }
    for (auto it2 = v2.begin(); it2 != v2.end(); ++it2) {
        std::cout << *it2 << std::endl;
    }
}