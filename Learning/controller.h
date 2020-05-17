#pragma once
#include "main.h"
#include "Lession1/shader.h"
#include "Lession1/texture.h"

#ifndef _CONTROLLER_H

class Controller
{
public:
	Shader* shader = nullptr;

	Controller(const char* vsfile, const char* fsfile, const char* gsfile = nullptr);
	~Controller();

	void setVertexInfo(
		float* vertices, int vertices_size,
		int* pointers, int pointer_count, bool* pointer_enable,
		int* indices = nullptr, int indices_size = NULL);
	void setTexture(const char* filepath);
	void setDepthEnable();
	void setDepthEnable(bool enable);
	void setClearColor(float r, float g, float b, float a = 1.0f);
	void clear();
	void use();
	void activeTexture(GLenum index);
	void setDraw(void(*func)());
	void draw();

private:
	unsigned int VAO = NULL;
	unsigned int texture = NULL;
	float clear_r, clear_g, clear_b, clear_a;
	void(*_draw)();
	bool depthEnable = false;
};

#endif // !_CONTROLLER_H
