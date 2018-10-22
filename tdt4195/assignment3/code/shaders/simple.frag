#version 430 core

layout(location = 0) in vec4 vert_Color;

void main()
{
    gl_FragColor = vert_Color;
}
