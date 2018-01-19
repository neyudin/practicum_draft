#include <iostream>
#include <string>
int main() {
    std::string s;
    while (std::cin >> s) {
        int a_len = 0, zero_len = 0, b_len = 0, one_len = 0;
        bool a_pass = false, zero_pass = false, b_pass = false, belongs = true;
        for (auto it = s.cbegin(); it != s.cend(); ++it) {
            if (*it == 'a') {
                if ((a_pass == false) && (zero_pass == false) && (b_pass == false)) {
                    ++a_len;
                    continue;
                } else {
                    belongs = false;
                    break;
                }
            }
            if (*it == '0') {
                a_pass = true;
                if ((zero_pass == false) && (b_pass == false)) {
                    ++zero_len;
                    continue;
                } else {
                    belongs = false;
                    break;
                }
            }
            if (*it == 'b') {
                zero_pass = true;
                if ((b_pass == false) && (a_pass == true)) {
                    ++b_len;
                    continue;
                } else {
                    belongs = false;
                    break;
                }
            }
            if (*it == '1') {
                b_pass = true;
                if ((zero_pass == true) && (a_pass == true)) {
                    ++one_len;
                    continue;
                }
            }
            belongs = false;
            break;
        }
        if ((a_pass == true) && (zero_pass == true) && (b_pass == true) && (a_len == b_len) && 
            (zero_len == one_len) && (a_len > 0) && (zero_len > 0) && (belongs == true)) {
            std::cout << '1' << std::endl;
        } else {
            std::cout << '0' << std::endl;
        }
    }
}