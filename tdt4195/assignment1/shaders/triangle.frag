#version 430 core

out vec4 color;
uniform vec2 u_Screensize;

void main()
{
    float v = float(gl_FragCoord.x * u_Screensize.y / u_Screensize.x  < gl_FragCoord.y);

    color = vec4(v, gl_FragCoord.x / u_Screensize.x, gl_FragCoord.y / u_Screensize.y, 1);
}
