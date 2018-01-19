#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct digital_tree {
    struct digital_tree *next[ALP_LEN]/*, *parent*/;
    char litera, end;
};

void add_string (struct digital_tree *root, char *text, int length) {
    int i;
    struct digital_tree *current = malloc(sizeof(struct digital_tree));
    current = root;
    for (i = 0; i < length; ++i) {
        if (current->next[text[i] - ALP] == NULL) {
            current->next[text[i] - ALP] = malloc(sizeof(struct digital_tree));
            current->next[text[i] - ALP]->end = CONT;
            for (int j = 0; j < ALP_LEN; ++j) {
                current->next[text[0] - ALP]->next[j] = NULL;
            }
        }
        current = current->next[text[i] - ALP];
        current->litera = text[i];
    }
    current->end = END;




}

struct digital_tree *initializer_tree (struct digital_tree *root) {
    root = malloc(sizeof(struct digital_tree));
    root->end = END;
    root->litera = PRE;
    for (int j = 0; j < ALP_LEN; ++j) {
        root->next[j] = NULL;
    }
    return root;
}//;

int ALP_LEN = 26;
char CONT = '0', PRE = '%', ALP = 'a', END = '$';

static long long computator (struct digital_tree *root) {
    int j;
    static long long count = 0;
    if (root->end == '$') {
        ++count;
    }
    for (j = 0; j < ALP_LEN; ++j) {
        if (root->next[j] != NULL) {
            count = computator(root->next[j]);
        }
    }
    return count;
}

long long compiler(char *text, int length) {
    char *slice = malloc(2002);
    int i, j, k;
    long long sum;
    struct digital_tree *root = initializer_tree(root);
    for (i = 1; i < length + 1; ++i) {
        for (j = 0; j < length - i + 1; ++j) {
            for (k = j; k < j + i; ++k) {
                slice[k] = text[k];
            }
            add_string(root, slice, length);
        }
    }
    sum = computator(root);
    return sum;
}

int main(void)
{



    char *str = malloc(2002);
    fgets(str, 2002, stdin);
    str[strlen(str) - 1] = '\0';
    int str_len = strlen(str);
    printf("%lld\n", compiler(str, str_len));
    return 0;
}
