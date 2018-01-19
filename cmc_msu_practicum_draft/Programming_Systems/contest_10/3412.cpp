#include <iostream>
#include <string>
int check(std::string &s) {
    int abb = 0;
    int notal = 0;
    int size = s.size();
    for (int i = 0; i < size; ++i) {
        if (s[i] == '3' || s[i] == '4') {
            if (abb == 1) {
                notal = 1;
                break;
            }
            continue;
        }
        if (s[i] == '1' || s[i] == '2') {
            abb = 1;
        } else {
            notal = 1;
            break;
        }
    }
    return 1 - notal;
}
int main() {
    std::string s;
    int k = 1111;
    while (k < 4445) {
        s = std::to_string(k);
        if (check(s)) {
            std::cout << s << std::endl;
        }
        ++k;
    }
}