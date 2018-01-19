#include <iostream>
#include <string>
#include <cctype>
int main() {
    std::string left, right;
    int gram = 1, iss = 0, low = 0, sright = 0, srule = 0, empty = 0, less = 0, cf = 1;
    while (std::cin >> left >> right) {
        int lsize = left.size(), rsize = right.size();
        low = 0;
        for (int i = 0; i < lsize; ++i) {
            if (left[i] == '_') {
                gram = 0;
                break;
            }
            if (islower(left[i]) || isdigit(left[i])) {
                ++low;
            }
        }
        if (low > 0) {
            cf = 0;
        }
        if (low == lsize) {
            gram = 0;
        }
        for (int i = 0; i < rsize; ++i) {
            if (right[i] == '_' && rsize != 1) {
                gram = 0;
                break;
            }
            if (right[i] == 'S') {
                ++sright;
            }
        }
        if (gram == 0) {
            break;
        }
        if (lsize == 1 && left[0] == 'S') {
            iss = 1;
            if (right[0] == '_') {
                srule = 1;
            }
        }
        if (right[0] == '_') {
            ++empty;
        }
        if (lsize > rsize || right[0] == '_') {
            ++less;
        }
    }
    if (gram == 0 || iss == 0) {
        std::cout << "-1" << std::endl;
    } else {
        if ((cf == 1) && (((less == 0) && (empty == 0)) || 
            ((less == 1) && (empty == 1) && (srule == 1) && (sright == 0)))) {
            std::cout << "23" << std::endl;
            return 0;
        }
        if ((cf == 1) && (less >= 0)) {
            std::cout << "2" << std::endl;
        } else {
            std::cout << "10" << std::endl;
        }
    }
}