#pragma once
#include "main.h"
#include "Lession1/shader.h"
#include "Lession1/texture.h"

class Controller
{
public:
	Controller(const char* vsfile, const char* fsfile, const char* gsfile = nullptr);
	~Controller();

	void setVertexInfo(
		float* vertices, int vertices_size,
		int* pointers, int pointer_count,
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

	void setInt(const char* name, GLint value);
	void setMatrix(const char* name, GLsizei count, GLboolean transpos, const GLfloat* value);

	unsigned int getProgram();

private:
	unsigned int program = NULL;
	unsigned int VAO = NULL;
	unsigned int texture = NULL;
	float clear_r, clear_g, clear_b, clear_a;
	void(*_draw)();
	bool depthEnable = false;
};
