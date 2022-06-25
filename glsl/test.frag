#version 450 core

uniform sampler2D s;

out vec4 color;

in VSout {
    vec4 position;
    vec2 tc;
} fsin;

void main(void)
{
    color = texture(s, fsin.tc);
}

