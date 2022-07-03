#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "platform.h"
#include "shader.h"
#include "gfx.h"
#include "gmath.h"

static GLuint prog;
static GLuint vao;
static hvec pos[] = {
    { 0.25f, -0.25f, 0.5f, 1.0f },
    { -0.25f, -0.25f, 0.5f, 1.0f },
    { 0.25f, 0.25f, 0.5f, 1.0f },
    { -0.25f, -0.25f, 0.5f, 1.0f },
    { -0.25f, 0.25f, 0.5f, 1.0f },
    { 0.25f, 0.25f, 0.5f, 1.0f },
};

void gfxinit(void)
{
    GLenum err;
    GLuint buf;

    err = glewInit();
    if (GLEW_OK != err)
        eprintf("GLEW init failed: %s", glewGetErrorString(err));

    glViewport(0, 0, 720, 720);

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
    vec3 red = { 0.5f, 0.0f, 0.0f };
    GLint loc;
    tform model;

    glClearBufferfv(GL_COLOR, 0, red);

    glUseProgram(prog);

    loc = glGetUniformLocation(prog, "model");
    if (loc == -1)
        eprintf("can't find uniform");
    tformrotz(45, model);
    tformprint(model);
    glUniformMatrix4fv(loc, 1, GL_FALSE, (const GLfloat *) model);

    glDrawArrays(GL_TRIANGLES, 0, sizeof(pos));

    //    tformid(model);
    //    glUniformMatrix4fv(loc, 1, GL_FALSE, (const GLfloat *) model);
    //
    //    glDrawArrays(GL_TRIANGLES, 0, 3);
}