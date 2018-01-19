#include <stdlib.h>
#include <string.h>

int mysubstr(const char sample[], const char text[])
{
    int star_pos = -1, i;
    char my_sample[strlen(sample) + 1];
    for (i = 0; sample[i] != '\0'; ++i) {
        my_sample[i] = sample[i];
    }
    my_sample[i] = '\0';
    char *after = NULL, *position;
    for (i = 0; my_sample[i] != '\0'; ++i) {
        if (my_sample[i] == '*') {
            star_pos = i;
            after = my_sample + i + 1;
            my_sample[i] = '\0';
            break;
        }
    }
    position = strstr(text, my_sample);
    if (position) {
        if (after) {
            return strstr(position + star_pos, after) ? position - text : -1;
        }
        return position - text;
    }
    return -1;
}
