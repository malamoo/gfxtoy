#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "platform.h"
#include "shader.h"
#include "gfx.h"

static GLuint prog;
static GLuint vao;

void gfxinit(void)
{
    GLenum err;
    GLuint vs, fs;

    err = glewInit();
    if (GLEW_OK != err)
        eprintf("GLEW init failed: %s", glewGetErrorString(err));

    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    if (iscomperr(vs, "src/gfx/shader.vert") ||
        iscomperr(fs, "src/gfx/shader.frag"))
        eprintf("can't create shader program");

    prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    if (islinkerr(prog))
        eprintf("can't create shader program");
    glDeleteShader(vs);
    glDeleteShader(fs);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

// TODO: gfxDelete

void gfxrender(void)
{
    GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };

    glClearBufferfv(GL_COLOR, 0, red);

    glUseProgram(prog);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}