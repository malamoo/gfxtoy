#include <stdio.h>
#include <GLFW/glfw3.h>
#include "errors.h"
#include "types.h"
#include "platform.h"

static void errcb(int err, const char *desc);
static void keycb(GLFWwindow *window, int key, int scancode, int action, int mods);

GLFWwindow *glfwinit()
{
    GLFWwindow *glfw;

    glfwSetErrorCallback(errcb);
    if (!glfwInit())
        eprintf("GLFW init failed");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfw = glfwCreateWindow(1280, 720, progname(), NULL, NULL);
    if (glfw == NULL)
        eprintf("window creation failed");

    glfwMakeContextCurrent(glfw);

    glfwSwapInterval(1); // enable vsync

    glfwSetKeyCallback(glfw, keycb);

    return glfw;
}

static void errcb(int err, const char *desc)
{
    weprintf("%s", desc);
}

static void keycb(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // TODO: fix window closing immediately bug
    //    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    //        glfwSetWindowShouldClose(window, GLFW_TRUE);
}