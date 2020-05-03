#pragma once
#include "../main.h"

struct ImageData
{
	int width, height;
	unsigned char* data;
	GLenum colorType;

	ImageData(int _width, int _height, unsigned char* _data, GLenum _colorType = GL_RGB)
	{
		width = _width;
		height = _height;
		data = _data;
		colorType = _colorType;
	}
};

unsigned int create2DTextureFromData(
	ImageData data,
	GLenum swrap = GL_REPEAT,
	GLenum twrap = GL_REPEAT,
	GLenum minfilter = GL_LINEAR,
	GLenum maxfilter = GL_LINEAR,
	GLenum colorType = GL_RGB,
	float* borderColor = new float[4] {1.0f, 1.0f, 1.0f, 1.0f},
	bool useMipmap = false);
unsigned int create2DTextureFromFile(const char* filepath);
