#include <iostream>
#include <iterator>
#include <vector>
#include <list>
template<typename T>
void process(T &v) {
    int num = 0;
    int deleted = 0;
    for (auto it = v.begin(); it != v.end();) {
        if ((num & 1) == 0) {
            v.erase(it);
            ++deleted;
            it = v.begin();
            int i = 0;
            ++num;
            while ((it != v.end()) && (i < num - deleted)) {
                ++it;
                ++i;
            }
        } else {
            ++num;
            ++it;
        }
    }
    for (auto rit = v.rbegin(); rit != v.rend(); ++rit) {
        std::cout << *rit << std::endl;
    }
}