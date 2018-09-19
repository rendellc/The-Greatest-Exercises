#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

layout(location = 1) out vec4 out_Color;

uniform layout(location = 2) float val;
mat4 transform;

void main()
{
    // Stuff
    float x_scale = 1.f;
    float x_shear = 0.f;
    float x_trans = 0.f;
    float y_scale = 1.f;
    float y_shear = 0.f;
    float y_trans = val;
    
    // Column major matrix!
    transform[0] = vec4(x_scale, y_shear, 0, 0);
    transform[1] = vec4(x_shear, y_scale, 0, 0);
    transform[2] = vec4(0, 0, 1, 0);
    transform[3] = vec4(x_trans, y_trans, 0, 1);

    gl_Position = transform * vec4(position, 1.0f);
    out_Color = color;
}
