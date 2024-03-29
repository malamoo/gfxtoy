#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <GLFW/glfw3.h>
#include "platform.h"

static char *name = NULL; // program name for messages

void eprintf(char *fmt, ...)
{
    va_list args;

    fflush(stdout);
    if (progname() != NULL)
        fprintf(stderr, "%s: ", progname());

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    if (fmt[0] != '\0' && fmt[strlen(fmt) - 1] == ':')
        fprintf(stderr, " %s", strerror(errno));
    fprintf(stderr, "\n");
    exit(2);
}

char *estrdup(char *s)
{
    char *t;

    t = (char *) malloc(strlen(s) + 1);
    if (t == NULL)
        eprintf("estrdup(\"%.20s\") failed:", s);
    strcpy(t, s);
    return t;
}

void setprogname(char *str)
{
    name = estrdup(str);
}

char *progname(void)
{
    return name;
}

void weprintf(char *fmt, ...)
{
    va_list args;

    if (progname() != NULL)
        fprintf(stderr, "%s: ", progname());

    fprintf(stderr, "warning: ");
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    if (fmt[0] != '\0' && fmt[strlen(fmt) - 1] == ':')
        fprintf(stderr, " %s", strerror(errno));
    fprintf(stderr, "\n");
}

void *emalloc(size_t n)
{
    void *p;

    p = malloc(n);
    if (p == NULL)
        eprintf("malloc of %u bytes failed:", n);
    return p;
}

void *erealloc(void *p, size_t n)
{
    p = realloc(p, n);
    if (p == NULL)
        eprintf("realloc of %u bytes failed:", n);
    return p;
}