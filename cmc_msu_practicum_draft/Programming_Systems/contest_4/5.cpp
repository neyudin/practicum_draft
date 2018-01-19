#include <iostream>
#include <iterator>
#include <vector>
void process(std::vector<int> &v1, const std::vector<int> &v2, int k)
{
    for (auto vit2 = v2.cbegin(); vit2 != v2.cend(); ++vit2) {
        auto vit1 = v1.begin();
        if (*vit2 > 0 && *vit2 <= static_cast<int> (v1.size())) {
            std::advance(vit1, *vit2 - 1);
            *vit1 *= k;
        }
    }
    std::ostream_iterator<int> output(std::cout, "\n");
    for (auto vit1 = v1.begin(); vit1 != v1.end(); ++vit1) {
        *output = *vit1;
    }
}