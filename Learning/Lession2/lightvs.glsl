#version 330 core

in layout(location = 0) vec3 pos;
in layout(location = 1) vec3 normal;
in layout(location = 2) vec2 texCoords;

out vec3 fragNormal;
out vec3 fragPos;
out vec2 fragTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	fragPos = vec3(model * vec4(pos, 1.0));
	fragNormal = normal;
	fragTexCoords = texCoords;
}