#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include "platform.h"
#include "shader.h"
#include "gfx.h"
#include "gmath.h"

static GLint unisetmat4fv(GLuint prog, char *name, tform m);

static GLuint mainprog;
static GLuint vao;
static vec3 pos[36] = {
    { -1.0f, -1.0f, -1.0f },
    { -1.0f, -1.0f, 1.0f },
    { -1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, -1.0f },
    { -1.0f, -1.0f, -1.0f },
    { -1.0f, 1.0f, -1.0f },
    { 1.0f, -1.0f, 1.0f },
    { -1.0f, -1.0f, -1.0f },
    { 1.0f, -1.0f, -1.0f },
    { 1.0f, 1.0f, -1.0f },
    { 1.0f, -1.0f, -1.0f },
    { -1.0f, -1.0f, -1.0f },
    { -1.0f, -1.0f, -1.0f },
    { -1.0f, 1.0f, 1.0f },
    { -1.0f, 1.0f, -1.0f },
    { 1.0f, -1.0f, 1.0f },
    { -1.0f, -1.0f, 1.0f },
    { -1.0f, -1.0f, -1.0f },
    { -1.0f, 1.0f, 1.0f },
    { -1.0f, -1.0f, 1.0f },
    { 1.0f, -1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, -1.0f, -1.0f },
    { 1.0f, 1.0f, -1.0f },
    { 1.0f, -1.0f, -1.0f },
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, -1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, -1.0f },
    { -1.0f, 1.0f, -1.0f },
    { 1.0f, 1.0f, 1.0f },
    { -1.0f, 1.0f, -1.0f },
    { -1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f },
    { -1.0f, 1.0f, 1.0f },
    { 1.0f, -1.0f, 1.0f }
};

typedef struct Cursor {
    float x, y;
} Cursor;

static Cursor cursor = {
    .x = 0.0f,
    .y = 0.0f
};

static float pitch, yaw;
static vec3 g = { 0.0f, 0.0f, -1.0f };
static float dt;
static float tlast;
static tform model;

static float PI = 3.14159265358979323846f;
static float degtorad(float deg)
{
    return (deg * PI) / 180.0f;
}

void gfxinit(void)
{
    GLuint buf;

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        eprintf("failed to initialize OpenGL context");

    glViewport(0, 0, 720, 720);

    mainprog = buildprog();
    if (mainprog == 0)
        eprintf("can't create shader program");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &buf);
    glBindBuffer(GL_ARRAY_BUFFER, buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
    glEnableVertexAttribArray(0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    tfid(model);
}

// TODO: gfxDelete

void gfxrender(GLFWwindow *glfw)
{
    tform camera, proj;
    float t;
    double x, y, dx, dy;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(mainprog);

    t = (float) glfwGetTime();
    dt = t - tlast;
    tlast = t;
    glfwGetCursorPos(glfw, &x, &y);
    dx = cursor.x - x, dy = cursor.y - y;
    cursor.x = x, cursor.y = y;
    pitch += degtorad(0.1f * dy);
    yaw += degtorad(0.1f * dx);

    tfroty(model, dt * 180, model);
    unisetmat4fv(mainprog, "model", model);

    g[0] = -sinf(yaw);
    g[1] = sinf(pitch);
    g[2] = -cosf(pitch) - cosf(yaw);

    tfcam((vec3){ 0.0f, 5.0f, 10.0f },
          g,
          (vec3){ 0.0f, 1.0f, 0.0f },
          camera);
    unisetmat4fv(mainprog, "camera", camera);

    tfpersp(45, 720 / 720, 0.1f, 100.0f, proj);
    unisetmat4fv(mainprog, "proj", proj);

    glDrawArrays(GL_TRIANGLES, 0, sizeof(pos));
}

static GLint unisetmat4fv(GLuint prog, char *name, tform m)
{
    GLint loc;

    loc = glGetUniformLocation(prog, name);
    if (loc == -1) {
        eprintf("can't find uniform \"%s\"", name);
        return loc;
    }
    glUniformMatrix4fv(loc, 1, GL_FALSE, (const GLfloat *) m);
    return loc;
}