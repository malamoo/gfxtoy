#include <stddef.h>
#include <stdio.h>
#include "types.h"
#include "errors.h"

size_t freads(FILE *fin, char *s, size_t max)
{
    size_t n;

    n = fread(s, sizeof(char), max - 1, fin);
    s[n] = '\0';
    if (!feof(fin)) {
        weprintf("can't read file: too large");
        return -1;
    }
    if (ferror(fin)) {
        weprintf("can't read file:");
        return -1;
    }

    return n;
}