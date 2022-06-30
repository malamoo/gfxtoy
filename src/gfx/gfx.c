#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "platform.h"
#include "shader.h"
#include "gfx.h"
#include "math.h"

static GLuint prog;
static GLuint vao;

void gfxinit(void)
{
    GLenum err;
    GLuint buf;
    hvec pos[3] = {
        { 0.25f, -0.25f, 0.5f, 1.0f },
        { -0.25f, -0.25f, 0.5f, 1.0f },
        { 0.25f, 0.25f, 0.5f, 1.0f }
    };

    err = glewInit();
    if (GLEW_OK != err)
        eprintf("GLEW init failed: %s", glewGetErrorString(err));

    prog = buildprog();
    if (prog == 0)
        eprintf("can't create shader program");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &buf);
    glBindBuffer(GL_ARRAY_BUFFER, buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(hvec), 0);
    glEnableVertexAttribArray(0);
}

// TODO: gfxDelete

void gfxrender(void)
{
    GLfloat red[] = { 1.0f, 0.0f, 0.0f };

    glClearBufferfv(GL_COLOR, 0, red);

    glUseProgram(prog);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}