#include <GLFW/glfw3.h>
#include <stdio.h>
#include "gfx.h"
#include "platform.h"
#include "game.h"

int main(void)
{
    setprogname("GeoSmith");

    gameplay();

    return 0;
}