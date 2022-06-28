#version 330

void main() {
    vec4 vertices[3];
    vertices[0] = vec4(0.25, -0.25, 0.5, 1.0);
    vertices[1] = vec4(-0.25, -0.25, 0.5, 1.0);
    vertices[2] = vec4(0.25, 0.25, 0.5, 1.0);
    gl_Position = vertices[gl_VertexID];
}