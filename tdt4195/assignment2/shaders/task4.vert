#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

layout(location = 1) out vec4 out_Color;

uniform layout(location = 2) mat4 u_Transform;

void main()
{
    gl_Position = u_Transform * vec4(position, 1.0f);
    gl_Position = gl_Position / gl_Position.w;

    out_Color = color;
}
