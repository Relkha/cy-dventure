#include "util.h"
#include <string.h>

void chomp(char *str) {
    size_t p = strlen(str);
    str[p - (str[p-1] == '\n')] = 0;
}

