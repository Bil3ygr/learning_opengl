#version 330 core
in layout(location = 0) vec3 pos;
in layout(location = 1) vec3 normal;

out vec3 fragNormal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	fragPos = vec3(model * vec4(pos, 1.0));
	fragNormal = normal;
}