#version 330

layout (location = 0) in vec4 pos;

uniform mat4 model;
uniform mat4 tmp = mat4(0.707, 0.707, 0.000, 0.000,
                   -0.707, 0.707, 0.000, 0.000,
                   0.000, 0.000, 1.000, 0.000,
                   0.000, 0.000, 0.000, 1.000);
uniform mat4 tmp2 = mat4(0.0, 1.0, 0.000, 0.000,
                    -1.0, 0.0, 0.000, 0.000,
                    0.000, 0.000, 1.000, 0.000,
                    0.000, 0.000, 0.000, 1.000);

void main() {
    gl_Position = model * pos;
}