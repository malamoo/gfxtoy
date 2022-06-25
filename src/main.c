#include "gfx.h"
#include "err.h"

int main(void)
{
    setprogname("eemoo");

    gfxinit();
    gameplay();

    return 0;
}
