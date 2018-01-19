#include <iostream>
#include <string>
#include <algorithm>
using std::string;
class BinaryNumber
{
    string num;
public:
    BinaryNumber(const string &s): num(s) {}
    operator string () const {
        return num;
    }
    BinaryNumber &operator=(BinaryNumber obj) {
        std::swap(num, obj.num);
        return *this;
    }
    const BinaryNumber &operator++() {
        string tmp = num;
        std::reverse(tmp.begin(), tmp.end());
        bool carry = true;
        for (auto it = tmp.begin(); it != tmp.end(); ++it) {
            if (++*it > '1') {
                *it = '0';
            } else {
                carry = false;
                break;
            }
        }
        if (carry) {
            tmp.push_back('1');
        }
        std::reverse(tmp.begin(), tmp.end());
        num = tmp;
        return *this;
    }
};