#version 450 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tc;

out VSout {
    vec4 position;
    vec2 tc;
} vsout;

uniform mat4 mv;
uniform mat4 proj;

void main(void)
{
    gl_Position = proj * mv * position;
    vsout.tc = tc;
    vsout.position = position;
}
