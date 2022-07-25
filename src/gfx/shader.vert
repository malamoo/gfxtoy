#version 330

layout (location = 0) in vec3 pos;

uniform mat4 model;
uniform mat4 camera;
uniform mat4 proj;

out vec4 vcolor;

void main() {
    vcolor = vec4(gl_VertexID % 2 * 0.45, gl_VertexID % 2 * 0.30, gl_VertexID % 2 * 0.20, 1.0);
    gl_Position = proj * camera * model * vec4(pos, 1.0);
}