#include <iostream>
#include <map>
#include <cctype>
std::map<char, int> priority = {{'*', 5}, {'/', 5}, {'+', 4}, {'-', 4}, {'&', 3}, {'^', 2}, {'|', 1}};//variable = 6
/*
S -> A or A|A
A -> B or  B^B
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
TREE *S();
TREE *A();
TREE *B();
TREE *C();
TREE *D();
TREE *E();
TREE *S() {
    TREE *node = new TREE;
    node->left = A();
    char c;
    if (std::cin.peek() == '|') {
        std::cin >> c;
        node->c = c;
        node->right = A();
    }
    return node;
}
TREE *A() {
    TREE *node = new TREE;
    node->left = B();
    char c;
    if (std::cin.peek() == '^') {
        std::cin >> c;
        node->c = c;
        node->right = B();
    }
    return node;
}
TREE *B() {
    TREE *node = new TREE;
    node->left = C();
    char c;
    if (std::cin.peek() == '&') {
        std::cin >> c;
        node->c = c;
        node->right = B();
    }
    return node;
}
TREE *C() {
    TREE *node = new TREE;
    node->left = D();
    char c;
    if ((std::cin.peek() == '+') || (std::cin.peek() == '-')) {
        std::cin >> c;
        node->c = c;
        node->right = D();
    }
    return node;
}
TREE *D() {
    TREE *node = new TREE;
    node->left = E();
    char c;
    if ((std::cin.peek() == '*') || (std::cin.peek() == '/')) {
        std::cin >> c;
        node->c = c;
        node->right = E();
    }
    return node;
}
TREE *E() {
    TREE *node = new TREE;
    char c;
    std::cin >> c;
    if (c == '(') {
        S();
        std::cin >> c;
        return node;
    }
    node->c = c;
    return node;
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
int main() {
    printer(S());
    std::cout << std::endl;
}
