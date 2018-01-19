#include <iostream>
#include <string>
int main() {
    int abb = 0, notal = 0;
    std::string s;
    while (std::cin >> s) {
        abb = 0;
        notal = 0;
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
        if (notal == 1) {
            std::cout << '0' << std::endl;
        } else {
            std::cout << '1' << std::endl;
        }
    }
}