#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>

class Mastermind {
private:
    int clen;
    int alen;
    std::vector<int> code;
    std::vector<int> colors_count;
public:
    Mastermind(int codelen = 4, int alphlen = 6): clen(codelen), alen(alphlen) {
        std::srand(std::time(nullptr));
        code.resize(clen);
        std::generate(code.begin(), code.end(), [&alphlen]{return std::rand() % alphlen;});
        colors_count.resize(alen);
        std::accumulate(code.cbegin(), code.cend(), 0, [this](int sum, int i) {
                                                         ++colors_count[i];
                                                         return sum;
                                                     });
    }
    void Check(std::vector<int> &codebreak) {
        std::vector<int> colors_count_tmp(alen);
        std::copy(colors_count.cbegin(), colors_count.cend(), colors_count_tmp.begin());
        std::vector<int> exists(alen);
        std::accumulate(codebreak.cbegin(), codebreak.cend(), 0, [&exists](int sum, int i) {
                                                                   ++exists[i];
                                                                   return sum;
                                                               });
        auto cbit = codebreak.cbegin();
        int black = std::accumulate(code.cbegin(), code.cend(), 0, 
            [&cbit, &colors_count_tmp, &exists](int sum, int i) {
                if (i == *cbit) {
                    ++sum;
                    --exists[i];
                    if (--colors_count_tmp[i] == 0)
                        exists[i] = 0;
                } 
                ++cbit;
                return sum;
            });
        cbit = codebreak.cbegin();
        int white = std::accumulate(code.cbegin(), code.cend(), 0, 
            [&cbit, &colors_count_tmp, &exists](int sum, int i) {
                if ((i != *cbit) && (exists[i] != 0)) {
                    ++sum;
                    --exists[i]; 
                    if (--colors_count_tmp[i] == 0)
                        exists[i] = 0;
                }
                ++cbit;
                return sum;
            });
        std::cout << black << " " << white << std::endl;
    }
};

void move(Mastermind &part, std::string &s, std::vector<int> &v) {
    if (std::cin >> s) {
        v.resize(s.size());
        auto csit = s.cbegin();
        std::generate(v.begin(), v.end(), [&csit]{return *(csit++) - '0';});
        part.Check(v);
        move(part, s, v);
    }
    return;
}

int main()
{
    Mastermind game;
    std::string test;
    std::vector<int> check;
    move(game, test, check);
}