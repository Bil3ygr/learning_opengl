#version 330 core

in vec3 outColor;
in vec2 outTexcoord;

uniform sampler2D texture1;

void main()
{
	gl_FragColor = texture(texture1, outTexcoord);
}
