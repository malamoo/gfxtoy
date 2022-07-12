#version 330

layout (location = 0) in vec3 pos;

uniform mat4 model;
uniform mat4 model2;
uniform float t;

out vec4 vcolor;

void main() {
    vcolor = vec4(gl_VertexID % 6 * 0.1 * t, gl_VertexID % 6 * 0.2 * sin(t), gl_VertexID % 6 * 0.3 * t, 1.0);
    gl_Position = model2 * model * vec4(pos, 1.0);
}