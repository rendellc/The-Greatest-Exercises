#version 430 core

out vec4 color;
layout(location = 1) in vec4 vert_Color;

void main()
{
    color = vert_Color;
}
