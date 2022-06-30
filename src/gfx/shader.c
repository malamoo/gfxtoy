#include <stdio.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <stdlib.h>
#include "platform.h"
#include "shader.h"

enum {
    SRCINIT = 1,
    SRCGROW = 2
};

static GLuint createshader(char *path, GLenum type);
static void pshaderlog(GLuint shader);
static void pproglog(GLuint prog);

// buildprog: builds a shader program
GLuint buildprog(void)
{
    GLuint vs, fs, prog; // names of shaders and program
    GLint ok;            // if compilation or linking successful

    vs = createshader("src/gfx/shader.vert", GL_VERTEX_SHADER);
    if (vs == 0) {
        weprintf("can't compile vertex shader");
        return 0;
    }

    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        pshaderlog(vs);
        glDeleteShader(vs);
        return 0;
    }

    fs = createshader("src/gfx/shader.frag", GL_FRAGMENT_SHADER);
    if (fs == 0) {
        weprintf("can't compile fragment shader");
        return 0;
    }

    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        pshaderlog(fs);
        glDeleteShader(vs);
        glDeleteShader(fs);
        return 0;
    }

    prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) {
        pproglog(prog);
        glDeleteShader(vs);
        glDeleteShader(fs);
        glDeleteProgram(prog);
        return 0;
    }

    // can delete now program has a copy
    glDeleteShader(vs);
    glDeleteShader(fs);

    return prog;
}

// createshader: creates a shader from its source file
static GLuint createshader(char *path, GLenum type)
{
    FILE *fin;
    char *src;
    size_t n, max, len;
    GLuint shader;

    fin = fopen(path, "rb");
    if (fin == NULL) {
        weprintf("can't open %s:", path);
        return 0;
    }

    // read source file into string
    max = SRCINIT;
    src = emalloc(max * sizeof(char));
    len = 0;
    do {
        n = fread(src + len, sizeof(char), max - len, fin);
        if (ferror(fin)) {
            weprintf("can't read %s:", path);
            fclose(fin);
            free(src);
            return 0;
        }
        len += n;
        if (len >= max) { // grow
            src = erealloc(src, (SRCGROW * max) * sizeof(char));
            max *= SRCGROW;
        }
    } while (!feof(fin));
    src[len] = '\0';
    fclose(fin);

    shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar *const *) &src, NULL);
    free(src);

    return shader;
}

// pshaderlog: prints a shader's info log
static void pshaderlog(GLuint shader)
{
    GLchar *log; // shader info log
    GLint len;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    log = emalloc(len);
    glGetShaderInfoLog(shader, len, NULL, log);
    weprintf("%s", log);
    free(log);
}

// pshaderlog: prints a program's info log
static void pproglog(GLuint prog)
{
    GLchar *log; // program info log
    GLint len;

    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    log = emalloc(len);
    glGetProgramInfoLog(prog, len, NULL, log);
    weprintf("%s", log);
    free(log);
}