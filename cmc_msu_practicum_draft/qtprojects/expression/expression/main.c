#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_expression(char **expr, int lp) {
    int st_lp = 0, op = 0, st_rp = 0;
    if (**expr == '(') {
        ++(*expr);
        st_lp ^= check_expression(expr, 1);
    } else {
        if (((**expr >= '0') && (**expr <= '9')) || (**expr == 'x')) {
            st_lp ^= 1;
            ++(*expr);
            if (((**expr >= '0') && (**expr <= '9')) || (**expr == 'x')) {
                return 0;
            }
        }
    }
    if ((**expr == '*') || (**expr == '-') || (**expr == '+')) {
        op = 1;
        ++(*expr);
    }
    if (**expr == '(') {
        ++(*expr);
        st_rp ^= check_expression(expr, 1);
    } else {
        if (((**expr >= '0') && (**expr <= '9')) || (**expr == 'x')) {
            st_rp ^= 1;
            ++(*expr);
            if (((**expr >= '0') && (**expr <= '9')) || (**expr == 'x')) {
                return 0;
            }
        }
    }
    if (**expr == ')') {
        ++(*expr);
        if (lp && st_lp && op && st_rp) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
    return 1;
}

struct node {
    char sym;
    struct node *left_op, *right_op;
};

struct node *build_tree(struct node *root, char **expr) {
    if (**expr == '(') {
        root->left_op = malloc(sizeof(struct node));
        ++(*expr);
        root->left_op = build_tree(root->left_op, expr);
    }
    if (((**expr >= '0') && (**expr <= '9')) || (**expr == 'x')) {
        root->left_op = malloc(sizeof(struct node));
        root->left_op->left_op = NULL;
        root->left_op->right_op = NULL;
        root->left_op->sym = **expr;
        *expr += 1;
    }
    if ((**expr == '*') || (**expr == '-') || (**expr == '+')) {
        root->sym = **expr;
        ++(*expr);
    }
    if (**expr == '(') {
        root->right_op = malloc(sizeof(struct node));
        ++(*expr);
        root->right_op = build_tree(root->right_op, expr);
    }
    if (((**expr >= '0') && (**expr <= '9')) || (**expr == 'x')) {
        root->right_op = malloc(sizeof(struct node));
        root->right_op->left_op = NULL;
        root->right_op->right_op = NULL;
        root->right_op->sym = **expr;
        *expr += 1;
    }
    if (**expr == ')') {
        ++(*expr);
    }
    return root;
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
    char *expr = malloc(2000002), *check = NULL;
    int x = 0;
    printf("please, enter expression you want to computate\n");
    fgets(expr, 500002, stdin);
    expr[strlen(expr) - 1] = '\0';
    check = expr;
    if (strlen(expr) > 1) {
        if (*check == '(') {
            ++check;
            x = 1;
        }
        if (check_expression(&check, x) && (!strlen(check))) {
            printf("please, enter value of x\n");
            scanf("%d", &x);
            struct node *root = malloc(sizeof(struct node));
            root = build_tree(root, &expr);
            root = root->left_op;
            printf("expresion equals %d\n", computation(root, x));
        } else {
            printf("expression is incorrect\n");
        }
    } else {
        if (((*expr >= '0') && (*expr <= '9')) || (*expr == 'x')) {
            printf("please, enter value of x\n");
            scanf("%d", &x);
            if (*expr == 'x') {
                printf("expresion equals %d\n", x);
            } else {
                printf("expresion equals %d\n", *expr - '0');
            }
        } else {
            printf("expression is incorrect\n");
        }
    }
    return 0;
}
