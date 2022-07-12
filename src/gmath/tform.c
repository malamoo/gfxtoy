#include <math.h>
#include <stdio.h>
#include "gmath.h"

static float PI = 3.14159265358979323846f;

//static float radtodeg(float rad)
//{
//    return rad * (180.0f / PI);
//}

static float degtorad(float deg)
{
    return (deg * PI) / 180.0f;
}

void tformid(tform m)
{
    m[0] = 1;
    m[1] = 0;
    m[2] = 0;
    m[3] = 0;

    m[4] = 0;
    m[5] = 1;
    m[6] = 0;
    m[7] = 0;

    m[8] = 0;
    m[9] = 0;
    m[10] = 1;
    m[11] = 0;

    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}

void tformrotz(float deg, tform m)
{
    float rad;

    rad = degtorad(deg);

    m[0] = cosf(rad);
    m[1] = sinf(rad);
    m[2] = 0;
    m[3] = 0;

    m[4] = -sinf(rad);
    m[5] = cosf(rad);
    m[6] = 0;
    m[7] = 0;

    m[8] = 0;
    m[9] = 0;
    m[10] = 1;
    m[11] = 0;

    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}

void tformroty(float deg, tform m)
{
    float rad;

    rad = degtorad(deg);

    m[0] = cosf(rad);
    m[1] = 0;
    m[2] = -sinf(rad);
    m[3] = 0;

    m[4] = 0;
    m[5] = 1;
    m[6] = 0;
    m[7] = 0;

    m[8] = sinf(rad);
    m[9] = 0;
    m[10] = cosf(rad);
    m[11] = 0;

    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}

void tformprint(tform m)
{
    int i;

    for (i = 0; i < 16; i++) {
        printf("% 5.3f", m[i]);
        if ((i % 4) < 3)
            printf(" ");
        else
            printf("\n");
    }
    printf("\n");
}