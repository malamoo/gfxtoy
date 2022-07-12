#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include "platform.h"
#include "shader.h"
#include "gfx.h"
#include "gmath.h"

static GLuint prog;
static GLuint vao;
static vec3 pos[36] = {
    { -0.25f, -0.25f, -0.25f },
    { -0.25f, -0.25f, 0.25f },
    { -0.25f, 0.25f, 0.25f },
    { 0.25f, 0.25f, -0.25f },
    { -0.25f, -0.25f, -0.25f },
    { -0.25f, 0.25f, -0.25f },
    { 0.25f, -0.25f, 0.25f },
    { -0.25f, -0.25f, -0.25f },
    { 0.25f, -0.25f, -0.25f },
    { 0.25f, 0.25f, -0.25f },
    { 0.25f, -0.25f, -0.25f },
    { -0.25f, -0.25f, -0.25f },
    { -0.25f, -0.25f, -0.25f },
    { -0.25f, 0.25f, 0.25f },
    { -0.25f, 0.25f, -0.25f },
    { 0.25f, -0.25f, 0.25f },
    { -0.25f, -0.25f, 0.25f },
    { -0.25f, -0.25f, -0.25f },
    { -0.25f, 0.25f, 0.25f },
    { -0.25f, -0.25f, 0.25f },
    { 0.25f, -0.25f, 0.25f },
    { 0.25f, 0.25f, 0.25f },
    { 0.25f, -0.25f, -0.25f },
    { 0.25f, 0.25f, -0.25f },
    { 0.25f, -0.25f, -0.25f },
    { 0.25f, 0.25f, 0.25f },
    { 0.25f, -0.25f, 0.25f },
    { 0.25f, 0.25f, 0.25f },
    { 0.25f, 0.25f, -0.25f },
    { -0.25f, 0.25f, -0.25f },
    { 0.25f, 0.25f, 0.25f },
    { -0.25f, 0.25f, -0.25f },
    { -0.25f, 0.25f, 0.25f },
    { 0.25f, 0.25f, 0.25f },
    { -0.25f, 0.25f, 0.25f },
    { 0.25f, -0.25f, 0.25f }
};

void gfxinit(void)
{
    GLuint buf;

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        eprintf("failed to initialize OpenGL context");

    glViewport(0, 0, 720, 720);

    prog = buildprog();
    if (prog == 0)
        eprintf("can't create shader program");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &buf);
    glBindBuffer(GL_ARRAY_BUFFER, buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
    glEnableVertexAttribArray(0);

    //    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

// TODO: gfxDelete

void gfxrender(void)
{
    GLint loc;
    tform model;
    tform model2;
    float t;

    t = (float)glfwGetTime();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(prog);

    loc = glGetUniformLocation(prog, "model");
    if (loc == -1)
        eprintf("can't find uniform");
    tformroty(45 * (float) glfwGetTime(), model);
    glUniformMatrix4fv(loc, 1, GL_FALSE, (const GLfloat *) model);

    loc = glGetUniformLocation(prog, "model2");
    if (loc == -1)
        eprintf("can't find uniform");
    tformrotz(45 * (float) glfwGetTime(), model2);
    glUniformMatrix4fv(loc, 1, GL_FALSE, (const GLfloat *) model2);

    loc = glGetUniformLocation(prog, "t");
    if (loc == -1)
        eprintf("can't find uniform");
    glUniform1f(loc, cosf(t) + 1.5);

    glDrawArrays(GL_TRIANGLES, 0, sizeof(pos));
}