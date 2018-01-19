#include <iostream>
#include <string>
#include <iterator>

void beta(std::string &s, int m, int pos) {
    if (m <= 0) {
        std::cout << s << std::endl;
        return;
    }
    s[pos] = '1';
    beta(s, m - 1, pos + 1);
    s[pos] = '2';
    beta(s, m - 1, pos + 1);
}
void permutator(std::string &s, int n, int pos) {
    if (n > 0) {
        s[pos] = '3';
        beta(s, n - 1, pos + 1);
        permutator(s, n - 1, pos + 1);
        s[pos] = '4';
        beta(s, n - 1, pos + 1);
        permutator(s, n - 1, pos + 1);
    }
}
int main() {
    int k = 0;
    std::cin >> k;
    if (k <= 0) {
        return 0;
    }
    std::string s = "";
    s.resize(k, 'a');
    beta(s, k, 0);
    permutator(s, k, 0);
    return 0;
}