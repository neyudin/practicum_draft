#include <iostream>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <utility>
#include <cstdio>
#include <cerrno>
#include <ctype.h>
#include <limits>
#include <map>
#include <vector>
#include <set>

class Grammar {
public:
    enum GrammarType {
        NONE = 0,
        SCF = 2,
        CF = 21,
        LR = 31,
        RR = 32,
        LA = 311,
        RA = 321
    };

    Grammar() {
        char left;
        std::string right;
        while (std::cin >> left >> right) {
            rules[left].push_back(right);
        }
    }

    GrammarType get_type() {
        if (type != NONE) {
            return type;
        }
        if (isRegular()) {
            bool left = isLeft(), right = isRight();
            if (left || right) {
                if (isAutomatic()) {
                    if (left) {
                        return type = LA;
                    } else {
                        return type = RA;
                    }
                } else {
                    if (left) {
                        return type = LR;
                    } else {
                        return type = RR;
                    }
                }
            }
        }
        if (isShortening()) {
            return type = SCF;
        }
        return type = CF;
    }

private:
    typedef
        std::map<
            char,
            std::vector<
                std::string > > G;
    G rules;
    GrammarType type = NONE;

    static inline int len(const std::string& s) {
        if (s == "_") {
            return 0;
        }
        return s.length();
    }

    static inline bool hasNonTerm(const std::string& s) {
        for (const auto& c : s) {
            if (isNonTerm(c)) {
                return true;
            }
        }
        return false;
    }

    static inline bool isNonTerm(char c) {
        return 'A' <= c && c <= 'Z';
    }

    static inline bool isTerm(char c) {
        return !isNonTerm(c);
    }

    static inline bool containsSingleNonTerminal(const std::string& s) {
        return len(s) == 1 && isNonTerm(s[0]);
    }

    static inline bool containsSingleTerminal(const std::string& s) {
        bool f = false;
        for (const auto& c : s) {
            if (isTerm(c)) {
                if (f) {
                    return false;
                }
                f = true;
            }
        }
        return true;
    }

    static inline bool containsS(const std::string& s) {
        for (const auto& c : s) {
            if (c == 'S') {
                return true;
            }
        }
        return false;
    }

    bool isRegular() {
        for (auto& rule : rules) {
            for (auto& right : rule.second) {
                int nonterms = 0;
                for (auto& c : right) {
                    nonterms += isNonTerm(c);
                }
                if (nonterms > 1) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isShortening() {
        for (auto& rule : rules) {
            for (auto& right : rule.second) {
                if (!len(right)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isLeft() {
        for (auto& rule : rules) {
            for (auto& right : rule.second) {
                if (hasNonTerm(right) && isTerm(right[0])) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isRight() {
        for (auto& rule : rules) {
            for (auto& right : rule.second) {
                if (hasNonTerm(right) && isTerm(right.back())) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isAutomatic() {
        bool S_to_empty_exists = false;
        std::set<char> nonTermsFromS;
        for (auto& rule : rules) {
            for (auto& right : rule.second) {
                if (!len(right)) {
                    if (rule.first != 'S') {
                        return false;
                    }
                    S_to_empty_exists = true;
                } else if (!containsSingleTerminal(right)) {
                    return false;
                }
                if (containsSingleNonTerminal(right)) {
                    nonTermsFromS.insert(right[0]);
                }
            }
        }
        auto end_it = nonTermsFromS.end();
        if (S_to_empty_exists || !nonTermsFromS.empty()) {
            for (auto& rule : rules) {
                for (auto& right : rule.second) {
                    if (containsS(right)) {
                        return false;
                    }
                    if (nonTermsFromS.find(rule.first) != end_it) {
                        if (right == "_" || containsSingleNonTerminal(right)) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
};

int main() {
    std::cout << Grammar().get_type() << std::endl;
}