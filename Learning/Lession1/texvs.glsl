#version 330 core
in layout(location = 0) vec3 pos;
in layout(location = 1) vec3 color;
in layout(location = 2) vec2 texcoord;

out vec3 outColor;
out vec2 outTexcoord;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(pos, 1.0);
	outColor = color;
	outTexcoord = texcoord;
}