#include <GLFW/glfw3.h>
#include <stdio.h>
#include "gfx.h"
#include "platform.h"
#include "game.h"

int main(void)
{
    setprogname("eemoo");

    gameplay();

    return 0;
}