#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 1) out vec4 out_Color;

void main()
{
    out_Color = color;
    gl_Position = vec4(position, 1.0f);
}
