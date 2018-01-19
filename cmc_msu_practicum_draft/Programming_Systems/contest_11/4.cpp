#include <iostream>
#include <map>
#include <cctype>
std::map<char, int> priority = {{'*', 5}, {'/', 5}, {'+', 4}, {'-', 4}, {'&', 3}, {'^', 2}, {'|', 1}};//variable = 6
/*
S -> A or A|A
A -> B or B^B
B -> C or C&C
C -> D or D+D or D-D
D -> E or E*E or E/E
E -> a......z or (S)
*/
struct TREE {
    char c = '_';
    TREE *left = nullptr;
    TREE *right = nullptr;
};
TREE *S(TREE *curtree);
TREE *A(TREE *curtree);
TREE *B(TREE *curtree);
TREE *C(TREE *curtree);
TREE *D(TREE *curtree);
TREE *E(TREE *curtree);
TREE *S(TREE *curtree) {
    if (curtree == nullptr) {
        curtree = new TREE;
    }
    char c;
    if (curtree->left == nullptr) {
        c = std::cin.peek();
        if (islower(c)) {
            curtree->left = E(curtree->left);
        }
        if (c == '(') {
            std::cin >> c;
            curtree->left = S(curtree->left);
            if (std::cin.peek() == ')') {
                std::cin >> c;
            }
        }
    }
    if (std::cin.peek() == '|') {
        std::cin >> c;
        curtree->c = c;
        c = std::cin.peek();
        if (islower(c)) {
            curtree->right = E(curtree->right);
        }
        if (c == '(') {
            std::cin >> c;
            curtree->right = S(curtree->right);
            if (std::cin.peek() == ')') {
                std::cin >> c;
            }
        }
    } else {
        curtree = A(curtree);
    }
    return curtree;
}
TREE *A(TREE *curtree) {
    if (curtree == nullptr) {
        curtree = new TREE;
    }
    char c;
    if (curtree->left == nullptr) {
        c = std::cin.peek();
        if (islower(c)) {
            curtree->left = E(curtree->left);
        }
        if (c == '(') {
            std::cin >> c;
            curtree->left = S(curtree->left);
            if (std::cin.peek() == ')') {
                std::cin >> c;
            }
        }
    }
    if (std::cin.peek() == '^') {
        std::cin >> c;
        curtree->c = c;
        c = std::cin.peek();
        if (islower(c)) {
            curtree->right = E(curtree->right);
        }
        if (c == '(') {
            std::cin >> c;
            curtree->right = S(curtree->right);
            if (std::cin.peek() == ')') {
                std::cin >> c;
            }
        }
    } else {
        curtree = B(curtree);
    }
    return curtree;
}
TREE *B(TREE *curtree) {
    if (curtree == nullptr) {
        curtree = new TREE;
    }
    char c;
    if (curtree->left == nullptr) {
        c = std::cin.peek();
        if (islower(c)) {
            curtree->left = E(curtree->left);
        }
        if (c == '(') {
            std::cin >> c;
            curtree->left = S(curtree->left);
            if (std::cin.peek() == ')') {
                std::cin >> c;
            }
        }
    }
    if (std::cin.peek() == '&') {
        std::cin >> c;
        curtree->c = c;
        c = std::cin.peek();
        if (islower(c)) {
            curtree->right = E(curtree->right);
        }
        if (c == '(') {
            std::cin >> c;
            curtree->right = S(curtree->right);
            if (std::cin.peek() == ')') {
                std::cin >> c;
            }
        }
    } else {
        curtree = C(curtree);
    }
    return curtree;
}
TREE *C(TREE *curtree) {
    if (curtree == nullptr) {
        curtree = new TREE;
    }
    char c;
    if (curtree->left == nullptr) {
        c = std::cin.peek();
        if (islower(c)) {
            curtree->left = E(curtree->left);
        }
        if (c == '(') {
            std::cin >> c;
            curtree->left = S(curtree->left);
            if (std::cin.peek() == ')') {
                std::cin >> c;
            }
        }
    }
    if ((std::cin.peek() == '+') || (std::cin.peek() == '-')) {
        std::cin >> c;
        curtree->c = c;
        c = std::cin.peek();
        if (islower(c)) {
            curtree->right = E(curtree->right);
        }
        if (c == '(') {
            std::cin >> c;
            curtree->right = S(curtree->right);
            if (std::cin.peek() == ')') {
                std::cin >> c;
            }
        }
    } else {
        curtree = D(curtree);
    }
    return curtree;
}
TREE *D(TREE *curtree) {
    if (curtree == nullptr) {
        curtree = new TREE;
    }
    char c;
    if (curtree->left == nullptr) {
        c = std::cin.peek();
        if (islower(c)) {
            curtree->left = E(curtree->left);
        }
        if (c == '(') {
            std::cin >> c;
            curtree->left = S(curtree->left);
            if (std::cin.peek() == ')') {
                std::cin >> c;
            }
        }
    }
    if ((std::cin.peek() == '*') || (std::cin.peek() == '/')) {
        std::cin >> c;
        curtree->c = c;
        c = std::cin.peek();
        if (islower(c)) {
            curtree->right = E(curtree->right);
        }
        if (c == '(') {
            std::cin >> c;
            curtree->right = S(curtree->right);
            if (std::cin.peek() == ')') {
                std::cin >> c;
            }
        }
    } else {
        curtree = S(curtree);
    }
    return curtree;
}
TREE *E(TREE *curtree) {
    if (curtree == nullptr) {
        curtree = new TREE;
    }
    char c;
    std::cin >> c;
    curtree->c = c;
    return curtree;
}
void printer(TREE *expr) {
    if (expr == nullptr) {
        return;
    }
    if (expr->left != nullptr) {
        if ((priority.find(expr->c) != priority.end()) && (priority.find(expr->left->c) != priority.end())) {
            if (*(priority.find(expr->left->c)) < *(priority.find(expr->c))) {
                std::cout << '(';
                printer(expr->left);
                std::cout << ')';
            } else {
                printer(expr->left);
            }
        } else {
            printer(expr->left);
        }
    }
    if (expr->c != '_') {
        std::cout << expr->c;
    }
    if (expr->right != nullptr) {
        if ((priority.find(expr->c) != priority.end()) && (priority.find(expr->right->c) != priority.end())) {
            if (*(priority.find(expr->right->c)) <= *(priority.find(expr->c))) {
                std::cout << '(';
                printer(expr->right);
                std::cout << ')';
            } else {
                printer(expr->right);
            }
        } else {
            printer(expr->right);
        }
    }
}
void deleter(TREE *curtree) {
    if (curtree != nullptr) {
        if (curtree->left != nullptr) {
            deleter(curtree->left);
        }
        if (curtree->right != nullptr) {
            deleter(curtree->right);
        }
        delete curtree;
    }
}
int main() {
    TREE *tree = S(nullptr);
    printer(tree);
    std::cout << std::endl;
    deleter(tree);
}
//
//
//
//
//
//
//
//
//
//
//
//