#include <GL/glew.h>
#include "errors.h"
#include "shader.h"
#include "gfx.h"

void gfxinit(void)
{
    GLenum err;
    GLuint vs, fs;
    GLuint prog;

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
}

void gfxrender(void)
{
    GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };

    glClearBufferfv(GL_COLOR, 0, red);
}