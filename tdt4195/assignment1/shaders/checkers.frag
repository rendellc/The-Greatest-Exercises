#version 430 core

out vec4 color;

void main()
{
    float b = float((int(gl_FragCoord.x) % 32 < 16 && int(gl_FragCoord.y) % 32 < 16) || (int(gl_FragCoord.x) % 32 >= 16 && int(gl_FragCoord.y) % 32 >= 16));
    

    color = vec4(b, b, b, 1.0);
}
