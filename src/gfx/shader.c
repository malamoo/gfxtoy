#include <stdio.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include "errors.h"
#include "types.h"
#include "platform.h"
#include "shader.h"

enum {
    MAXSRC = 16384
};

int iscomperr(GLuint shader, char *path)
{
    FILE *fin;
    GLchar s[MAXSRC], *sp;
    size_t slen;

    fin = fopen(path, "rb");
    if (fin == NULL) {
        weprintf("can't open %s:", path);
        return 1;
    }

    slen = freads(fin, s, MAXSRC);
    fclose(fin);
    if (slen < 0) {
        weprintf("can't compile %s", path);
        return 1;
    }

    sp = s; // need address of pointer variable, not array
    glShaderSource(shader, 1, (const GLchar *const *) &sp, NULL);
    glCompileShader(shader); // TODO: check compilation errors

    return 0;
}

int islinkerr(GLuint prog)
{
    glLinkProgram(prog); // TODO: check linking errors

    return 0;
}