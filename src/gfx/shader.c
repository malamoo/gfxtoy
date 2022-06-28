#include <stdio.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <stdlib.h>
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
    GLchar *s;
    size_t slen;
    GLint ok;
    GLchar *log;
    GLint loglen;

    // get shader source code
    fin = fopen(path, "rb");
    if (fin == NULL) {
        weprintf("can't open %s:", path);
        return 1;
    }
    s = emalloc(MAXSRC);
    slen = freads(fin, s, MAXSRC);
    fclose(fin);
    if (slen < 0) {
        weprintf("can't compile %s", path);
        free(s);
        return 1;
    }
    glShaderSource(shader, 1, (const GLchar *const *) &s, NULL);
    free(s);

    // compile and check for errors
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &loglen);
        log = emalloc(loglen);
        glGetShaderInfoLog(shader, loglen, NULL, log);
        weprintf("%s", log);
        free(log);
        return 1;
    }

    return 0;
}

int islinkerr(GLuint prog)
{
    GLint ok;
    GLchar *log;
    GLint loglen;

    // link and check for errors
    glLinkProgram(prog);
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) {
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &loglen);
        log = emalloc(loglen);
        glGetProgramInfoLog(prog, loglen, NULL, log);
        weprintf("%s", log);
        free(log);
        return 1;
    }

    return 0;
}