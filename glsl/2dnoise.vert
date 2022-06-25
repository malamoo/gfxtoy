#version 450 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tc;

uniform sampler2D s;

out VSout {
    vec4 position;
    vec2 tc;
} vsout;

uniform mat4 mv;
uniform mat4 proj;

vec2 grad(vec2 p) {
	const float texture_width = 256.0;
	vec4 v = texture(s, vec2(p.x / texture_width, p.y / texture_width));
    return normalize(v.xy*2.0 - vec2(1.0));
}

/* S-shaped curve for 0 <= t <= 1 */
float fade(float t) {
  return t*t*t*(t*(t*6.0 - 15.0) + 10.0);
}


/* 2D noise */
float noise(vec2 p) {
  /* Calculate lattice points. */
  vec2 p0 = floor(p);
  vec2 p1 = p0 + vec2(1.0, 0.0);
  vec2 p2 = p0 + vec2(0.0, 1.0);
  vec2 p3 = p0 + vec2(1.0, 1.0);

  /* Look up gradients at lattice points. */
  vec2 g0 = grad(p0);
  vec2 g1 = grad(p1);
  vec2 g2 = grad(p2);
  vec2 g3 = grad(p3);

  float t0 = p.x - p0.x;
  float fade_t0 = fade(t0); /* Used for interpolation in horizontal direction */

  float t1 = p.y - p0.y;
  float fade_t1 = fade(t1); /* Used for interpolation in vertical direction. */

  /* Calculate dot products and interpolate.*/
  float p0p1 = (1.0 - fade_t0) * dot(g0, (p - p0)) + fade_t0 * dot(g1, (p - p1)); /* between upper two lattice points */
  float p2p3 = (1.0 - fade_t0) * dot(g2, (p - p2)) + fade_t0 * dot(g3, (p - p3)); /* between lower two lattice points */

  /* Calculate final result */
  return (1.0 - fade_t1) * p0p1 + fade_t1 * p2p3;
}

void main(void)
{
    vec2 pos = position.xz;
    float y = noise(pos/64.0) * 1.0 +
        	  noise(pos/32.0) * 0.5 +
        	  noise(pos/16.0) * 0.25 +
        	  noise(pos/8.0) * 0.125;
    gl_Position = proj * mv * (position + vec4(0.0, y * 30, 0.0, 0.0));
    vsout.tc = tc;
    vsout.position = position;
}
