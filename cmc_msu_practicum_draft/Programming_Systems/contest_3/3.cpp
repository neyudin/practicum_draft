#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string s;
    while(std::cin >> s) {
        int len = s.length(), maxlen = 0;
        std::string res;
        for (int i = len; i > 0; --i) {
            std::string tmp1 = s.substr(0, i);
            res = tmp1;
            std::reverse(res.begin(), res.end());
            if (tmp1 == res) {
                maxlen = i;
                break;
            }
        }
        res = s.substr(0, maxlen);
        std::cout << res << std::endl;
    }
}