#include <stdio.h>
#include <stdlib.h>

struct node {
    char sym;
    struct node *left_op, *right_op;
};

struct node *build_tree(struct node *root) {
    int st_lp = 0, op = 0, st_rp = 0;
    char c;
    if (root) {
        scanf("%c", &c);
    } else {
        free(root);
        return NULL;
    }
    if (c == '(') {
        st_lp = 1;
        root->left_op = malloc(sizeof(struct node));
        root->left_op = build_tree(root->left_op);
    } else {
        if (((c >= '0') && (c <= '9')) || (c == 'x')) {
        st_lp = 1;
        root->left_op = malloc(sizeof(struct node));
        root->left_op->left_op = NULL;
        root->left_op->right_op = NULL;
        root->left_op->sym = c;
        } else {
            free(root);
                return NULL;
        }
    }
    if (root->left_op) {
        scanf("%c", &c);
    } else {
        free(root);
        return NULL;
    }
    if ((c == '*') || (c == '-') || (c == '+')) {
        root->sym = c;
        op = 1;
    } else {
        free(root);
            return NULL;
    }
    scanf("%c", &c);
    if (c == '(') {
        st_rp = 1;
        root->right_op = malloc(sizeof(struct node));
        root->right_op = build_tree(root->right_op);
    } else {
        if (((c >= '0') && (c <= '9')) || (c == 'x')) {
            st_rp = 1;
            root->right_op = malloc(sizeof(struct node));
            root->right_op->left_op = NULL;
            root->right_op->right_op = NULL;
            root->right_op->sym = c;
        } else {
            free(root);
                return NULL;
        }
    }
    if (root->right_op) {
        scanf("%c", &c);
    } else {
        free(root);
        return NULL;
    }
    if (c == ')') {
        if (st_lp && op && st_rp) {
            if ((!(root->left_op)) || (!(root->right_op))) {
                free(root);
                return NULL;
            }
            return root;
        }
    }
    free(root);
    return NULL;
}

int computation(struct node *root, int number) {
    if (root->sym == '-') {
        return computation(root->left_op, number) - computation(root->right_op, number);
    }
    if (root->sym == '+') {
        return computation(root->left_op, number) + computation(root->right_op, number);
    }
    if (root->sym == '*') {
        return computation(root->left_op, number) * computation(root->right_op, number);
    }
    return root->sym == 'x' ? number : root->sym - '0';
}

int main(void)
{
    int x = 0;
    printf("please, enter expression you want to computate\n");
    struct node *root = malloc(sizeof(struct node));
    char c;
    scanf("%c", &c);
    if (c == '(') {
        root = build_tree(root);
        if (!root) {
            printf("expression is incorrect\n");
            return 0;
        }
    } else {
        root->left_op = NULL;
        root->right_op = NULL;
        root->sym = c;
        scanf("%c", &c);
        if (((root->sym != 'x') && ((root->sym < '0') || (root->sym > '9'))) || (c != '\n')) {
            printf("expression is incorrect\n");
            free(root);
            root = NULL;
            return 0;
        }
    }
    printf("please, enter value of x\n");
    if (scanf("%d", &x)) {
        printf("expresion equals %d\n", computation(root, x));
    } else {
        printf("illegal value of x\n");
    }
    free(root);
    return 0;
}
