#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <ctime>

class Mastermind {
private:
    int codelen_, alphlen_;
    std::string codestr_ = "";
    int *colors_count_;
    int *colors_count_tmp_;
    int *exists_;
public:
    Mastermind(int codelen = 4, int alphlen = 6): codelen_(codelen), alphlen_(alphlen) {
        srand(time(nullptr));
        for (int i = 0; i < codelen_; ++i) {
            codestr_ += std::to_string(rand() % alphlen_);
        }
        colors_count_ = new int [alphlen_];
        for (int i = 0; i < alphlen_; ++i) {
            colors_count_[i] = 0;
        }
        for (int i = 0; i < codelen_; ++i) {
            ++colors_count_[codestr_[i] - '0'];
        }
        colors_count_tmp_ = new int [alphlen_];
        exists_ = new int [alphlen_];
    }
    ~Mastermind() {
        delete [] colors_count_;
        delete [] colors_count_tmp_;
        delete [] exists_;
    }
    void Check(std::string codebreak) {
        int black_hits = 0, white_hits = 0;
        for (int i = 0; i < alphlen_; ++i) {
            colors_count_tmp_[i] = colors_count_[i];
        }
        for (int i = 0; i < alphlen_; ++i) {
            exists_[i] = 0;
        }
        for (int i = 0; i < codelen_; ++i) {
            ++exists_[codebreak[i] - '0'];
        }
        for (int i = 0; i < codelen_; ++i) {
            if (codebreak[i] == codestr_[i]) {
                ++black_hits;
                --exists_[codebreak[i] - '0'];
                if (--colors_count_tmp_[codestr_[i] - '0'] <= 0) {
                    exists_[codebreak[i] - '0'] = 0;
                }
            }
        }
        for (int i = 0; i < codelen_; ++i) {
            if (codebreak[i] != codestr_[i] && exists_[codestr_[i] - '0'] > 0) {
                    ++white_hits;
                    --exists_[codestr_[i] - '0'];
                    if (--colors_count_tmp_[codestr_[i] - '0'] <= 0) {
                        exists_[codestr_[i] - '0'] = 0;
                    }
                }
        }
        std::cout << black_hits << " " << white_hits << std::endl;
    }
};

int main()
{
    Mastermind game;
    std::string test;
    while(std::cin >> test) {
        game.Check(test);
    }
}