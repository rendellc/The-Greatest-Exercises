#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

uniform layout(location = 0) mat4 u_Transform;

layout(location = 0) out vec4 vertexColor;

void main()
{
    gl_Position = u_Transform * position;
    vertexColor = color;
}
