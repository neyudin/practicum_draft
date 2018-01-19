#include <iostream>
#include <string>
#include <utility>
#include <cctype>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

bool isreg(std::map<char, std::vector<std::string>> &g) {
    for (auto git = g.cbegin(); git != g.cend(); ++git) {
        for (auto vit = git->second.cbegin(); vit != git->second.cend(); ++vit) {
            int nt = 0;
            for (auto cit = vit->cbegin(); cit != vit->cend(); ++cit) {
                nt += isupper(*cit) != 0 ? 1: 0;
            }
            if (nt > 1) {
                return false;
            }
        }
    }
    return true;
}

bool NThas(std::string s) {
    for (auto cit = s.cbegin(); cit != s.cend(); ++cit) {
        if (isupper(*cit)) {
            return true;
        }
    }
    return false;
}

bool isleftlinear(std::map<char, std::vector<std::string>> &g) {
    for (auto git = g.cbegin(); git != g.cend(); ++git) {
        for (auto vit = git->second.cbegin(); vit != git->second.cend(); ++vit) {
            if (NThas(*vit) && !isupper(*(vit->cbegin()))) {
                return false;
            }
        }
    }
    return true;
}

bool isrightlinear(std::map<char, std::vector<std::string>> &g) {
    for (auto git = g.cbegin(); git != g.cend(); ++git) {
        for (auto vit = git->second.cbegin(); vit != git->second.cend(); ++vit) {
            if (NThas(*vit) && !isupper(vit->back())) {
                return false;
            }
        }
    }
    return true;
}

bool Tonlyone(std::string s) {
    bool t = false;
    for (auto cit = s.cbegin(); cit != s.cend(); ++cit) {
        if (!isupper(*cit)) {
            if (t == true) {
                return false;
            }
            t = true;
        }
    }
    return true;
}

int len(std::string s) {
    if (s == "_") {
        return 0;
    }
    return s.length();
}

bool NTonlyone(std::string s) {
    return (len(s) == 1) && isupper(s[0]);
}

bool Shas(std::string s) {
    for (auto cit = s.cbegin(); cit != s.cend(); ++cit) {
        if (*cit == 'S') {
            return true;
        }
    }
    return false;
}

bool isauto(std::map<char, std::vector<std::string>> &g) {
    bool S__ = false;
    std::set<char> S_NT;
    for (auto git = g.cbegin(); git != g.cend(); ++git) {
        for (auto vit = git->second.cbegin(); vit != git->second.cend(); ++vit) {
            if (!len(*vit)) {
                if (git->first != 'S') {
                    return false;
                }
                S__ = true;
            } else {
                if (!Tonlyone(*vit)) {
                    return false;
                }
            }
            if (NTonlyone(*vit)) {
                S_NT.insert(*(vit->cbegin()));
            }
        }
    }
    auto eit = S_NT.end();
    if (S__ || !S_NT.empty()) {
        for (auto git = g.cbegin(); git != g.cend(); ++git) {
            for (auto vit = git->second.cbegin(); vit != git->second.cend(); ++vit) {
                if (Shas(*vit)) {
                    return false;
                }
                if (S_NT.find(git->first) != eit) {
                    if (*vit == "_" || NTonlyone(*vit)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int type(std::map<char, std::vector<std::string>> &g) {
    if (isreg(g)) {
        bool right = isrightlinear(g);
        bool left = isleftlinear(g);
        if (right || left) {
            if (isauto(g)) {
                if (left) {
                    return 311;
                } else {
                    return 321;
                }
            } else {
                if (left) {
                    return 31;
                } else {
                    return 32;
                }
            }
        }
    }
    for (auto git = g.cbegin(); git != g.cend(); ++git) {
        for (auto vit = git->second.cbegin(); vit != git->second.cend(); ++vit) {
            if (!len(*vit)) {
                return 2;
            }
        }
    }
    return 21;
}

int main() {
    char l;
    std::string r;
    std::map<char, std::vector<std::string>> grammar;
    while (std::cin >> l >> r) {
        grammar[l].push_back(r);
    }
    std::cout << type(grammar) << std::endl;
}