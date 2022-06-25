#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "err.h"

void errcb(int err, const char *desc)
{
    weprintf("%s", desc);
}

void gfxinit(void)
{
    GLFWwindow *glfw;
    GLenum err;

    glfwSetErrorCallback(errcb);
    if (!glfwInit())
        eprintf("GLFW init failed");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfw = glfwCreateWindow(1920, 1080, progname(), NULL, NULL);
    if (glfw == NULL)
        eprintf("window creation failed");

    glfwMakeContextCurrent(glfw);

    err = glewInit();
    if (GLEW_OK != err)
        eprintf("GLEW init failed: %s", glewGetErrorString(err));
}

void gfxrender(void)
{
}
