#include <stdio.h>
#include <GLFW/glfw3.h>
#include "game.h"
#include "gfx.h"
#include "platform.h"

void gameplay(void)
{
    GLFWwindow *glfw;

    glfw = glfwinit();
    gfxinit();
    while (!glfwWindowShouldClose(glfw)) {
        gfxrender(glfw);
        glfwSwapBuffers(glfw);
        glfwPollEvents();
    }
}