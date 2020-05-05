#pragma once
#ifndef _SHADER_H

#include "../utils.h"

unsigned int createShader(GLenum shaderType, const char* shaderSource);
unsigned int createProgram(int vs, int fs, int gs = NULL);
unsigned int createProgram(const char* vsfile, const char* fsfile, const char* gsfile = nullptr);
unsigned int createVertexInfo(
	float* vertices, int vertices_size,
	int* pointers, int pointer_count,
	int* indices = nullptr, int indices_size = 0
);

#endif // !_SHADER_H
