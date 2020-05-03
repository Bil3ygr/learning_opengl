#version 330 core

in vec3 pColor;

void main()
{
    gl_FragColor = vec4(pColor, 1.0);
}
