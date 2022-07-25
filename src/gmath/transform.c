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

void tfid(tform out)
{
    out[0][0] = 1;
    out[0][1] = 0;
    out[0][2] = 0;
    out[0][3] = 0;

    out[1][0] = 0;
    out[1][1] = 1;
    out[1][2] = 0;
    out[1][3] = 0;

    out[2][0] = 0;
    out[2][1] = 0;
    out[2][2] = 1;
    out[2][3] = 0;

    out[3][0] = 0;
    out[3][1] = 0;
    out[3][2] = 0;
    out[3][3] = 1;
}

void tfrotz(float deg, tform out)
{
    float rad;

    rad = degtorad(deg);

    out[0][0] = cosf(rad);
    out[0][1] = sinf(rad);
    out[0][2] = 0;
    out[0][3] = 0;

    out[1][0] = -sinf(rad);
    out[1][1] = cosf(rad);
    out[1][2] = 0;
    out[1][3] = 0;

    out[2][0] = 0;
    out[2][1] = 0;
    out[2][2] = 1;
    out[2][3] = 0;

    out[3][0] = 0;
    out[3][1] = 0;
    out[3][2] = 0;
    out[3][3] = 1;
}

void tfroty(float deg, tform out)
{
    float rad;

    rad = degtorad(deg);

    out[0][0] = cosf(rad);
    out[0][1] = 0;
    out[0][2] = -sinf(rad);
    out[0][3] = 0;

    out[1][0] = 0;
    out[1][1] = 1;
    out[1][2] = 0;
    out[1][3] = 0;

    out[2][0] = sinf(rad);
    out[2][1] = 0;
    out[2][2] = cosf(rad);
    out[2][3] = 0;

    out[3][0] = 0;
    out[3][1] = 0;
    out[3][2] = 0;
    out[3][3] = 1;
}

void tfcam(vec3 e, vec3 g, vec3 t, tform out)
{
    hvec u, v, w;

    vec3neg(g, w);
    vec3unit(w, w);

    vec3cross(t, w, u);
    vec3unit(u, u);

    vec3cross(w, u, v);

    tfframe(u, v, w, e, out);
    tfframeinv(out, out);
}

void tfframe(vec3 u, vec3 v, vec3 w, vec3 e, tform out)
{
    out[0][0] = u[0];
    out[0][1] = u[1];
    out[0][2] = u[2];
    out[0][3] = 0;

    out[1][0] = v[0];
    out[1][1] = v[1];
    out[1][2] = v[2];
    out[1][3] = 0;

    out[2][0] = w[0];
    out[2][1] = w[1];
    out[2][2] = w[2];
    out[2][3] = 0;

    out[3][0] = e[0];
    out[3][1] = e[1];
    out[3][2] = e[2];
    out[3][3] = 1;
}

void tfframeinv(tform frame, tform out)
{
    tform a, b;
    vec3 u = { frame[0][0], frame[0][1], frame[0][2] },
         v = { frame[1][0], frame[1][1], frame[1][2] },
         w = { frame[2][0], frame[2][1], frame[2][2] },
         e = { frame[3][0], frame[3][1], frame[3][2] };

    a[0][0] = u[0];
    a[0][1] = v[0];
    a[0][2] = w[0];
    a[0][3] = 0;

    a[1][0] = u[1];
    a[1][1] = v[1];
    a[1][2] = w[1];
    a[1][3] = 0;

    a[2][0] = u[2];
    a[2][1] = v[2];
    a[2][2] = w[2];
    a[2][3] = 0;

    a[3][0] = 0;
    a[3][1] = 0;
    a[3][2] = 0;
    a[3][3] = 1;

    b[0][0] = 1;
    b[0][1] = 0;
    b[0][2] = 0;
    b[0][3] = 0;

    b[1][0] = 0;
    b[1][1] = 1;
    b[1][2] = 0;
    b[1][3] = 0;

    b[2][0] = 0;
    b[2][1] = 0;
    b[2][2] = 1;
    b[2][3] = 0;

    b[3][0] = -e[0];
    b[3][1] = -e[1];
    b[3][2] = -e[2];
    b[3][3] = 1;

    tfmul(a, b, out);
}

void tfmul(tform a, tform b, tform out)
{
    hvec r0 = { a[0][0], a[1][0], a[2][0], a[3][0] },
         r1 = { a[0][1], a[1][1], a[2][1], a[3][1] },
         r2 = { a[0][2], a[1][2], a[2][2], a[3][2] },
         r3 = { a[0][3], a[1][3], a[2][3], a[3][3] };
    hvec c0 = { b[0][0], b[0][1], b[0][2], b[0][3] },
         c1 = { b[1][0], b[1][1], b[1][2], b[1][3] },
         c2 = { b[2][0], b[2][1], b[2][2], b[2][3] },
         c3 = { b[3][0], b[3][1], b[3][2], b[3][3] };

    out[0][0] = r0[0] * c0[0] + r0[1] * c0[1] + r0[2] * c0[2] + r0[3] * c0[3];
    out[0][1] = r1[0] * c0[0] + r1[1] * c0[1] + r1[2] * c0[2] + r1[3] * c0[3];
    out[0][2] = r2[0] * c0[0] + r2[1] * c0[1] + r2[2] * c0[2] + r2[3] * c0[3];
    out[0][3] = r3[0] * c0[0] + r3[1] * c0[1] + r3[2] * c0[2] + r3[3] * c0[3];

    out[1][0] = r0[0] * c1[0] + r0[1] * c1[1] + r0[2] * c1[2] + r0[3] * c1[3];
    out[1][1] = r1[0] * c1[0] + r1[1] * c1[1] + r1[2] * c1[2] + r1[3] * c1[3];
    out[1][2] = r2[0] * c1[0] + r2[1] * c1[1] + r2[2] * c1[2] + r2[3] * c1[3];
    out[1][3] = r3[0] * c1[0] + r3[1] * c1[1] + r3[2] * c1[2] + r3[3] * c1[3];

    out[2][0] = r0[0] * c2[0] + r0[1] * c2[1] + r0[2] * c2[2] + r0[3] * c2[3];
    out[2][1] = r1[0] * c2[0] + r1[1] * c2[1] + r1[2] * c2[2] + r1[3] * c2[3];
    out[2][2] = r2[0] * c2[0] + r2[1] * c2[1] + r2[2] * c2[2] + r2[3] * c2[3];
    out[2][3] = r3[0] * c2[0] + r3[1] * c2[1] + r3[2] * c2[2] + r3[3] * c2[3];

    out[3][0] = r0[0] * c3[0] + r0[1] * c3[1] + r0[2] * c3[2] + r0[3] * c3[3];
    out[3][1] = r1[0] * c3[0] + r1[1] * c3[1] + r1[2] * c3[2] + r1[3] * c3[3];
    out[3][2] = r2[0] * c3[0] + r2[1] * c3[1] + r2[2] * c3[2] + r2[3] * c3[3];
    out[3][3] = r3[0] * c3[0] + r3[1] * c3[1] + r3[2] * c3[2] + r3[3] * c3[3];
}

void vec3cross(vec3 a, vec3 b, vec3 out)
{
    float xa, ya, za, xb, yb, zb;

    xa = a[0];
    ya = a[1];
    za = a[2];
    xb = b[0];
    yb = b[1];
    zb = b[2];

    out[0] = ya * zb - za * yb;
    out[1] = za * xb - xa * zb;
    out[2] = xa * yb - ya * xb;
}

void vec3neg(vec3 v, vec3 out)
{
    out[0] = -v[0];
    out[1] = -v[1];
    out[2] = -v[2];
}

void vec3unit(vec3 v, vec3 out)
{
    float mag;

    mag = vec3norm(v);
    out[0] = v[0] / mag;
    out[1] = v[1] / mag;
    out[2] = v[2] / mag;
}

float vec3norm(vec3 v)
{
    return sqrtf(v[0] * v[0] +
                 v[1] * v[1] +
                 v[2] * v[2]);
}

void tfpersp(float fov, float aspect, float near, float far, tform out)
{
    float n, f, r, l, t, b;

    n = fabsf(near);
    f = fabsf(far);
    t = tanf(degtorad(fov) / 2.0f) * n;
    b = -t;
    r = aspect * t;
    l = -r;

    out[0][0] = (2.0f * n) / (r - l);
    out[0][1] = 0;
    out[0][2] = 0;
    out[0][3] = 0;

    out[1][0] = 0;
    out[1][1] = (2.0f * n) / (t - b);
    out[1][2] = 0;
    out[1][3] = 0;

    out[2][0] = (r + l) / (r - l);
    out[2][1] = (t + b) / (t - b);
    out[2][2] = (n + f) / (n - f);
    out[2][3] = -1;

    out[3][0] = 0;
    out[3][1] = 0;
    out[3][2] = (2.0f * n * f) / (n - f);
    out[3][3] = 0;
}

void tftranz(float z, tform out)
{
    out[3][2] += z;
}

void tfprint(tform m)
{
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("% 12.3f", m[j][i]);
        }
        printf("\n");
    }
    printf("\n");
}