#version 330 core
in layout(location = 0) vec3 pos;
in layout(location = 1) vec3 color;

out vec3 pColor;

void main()
{
   gl_Position = vec4(pos, 1.0);
   pColor = color;
}