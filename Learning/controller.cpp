#include "controller.h"

Controller::Controller(const char* vsfile, const char* fsfile, const char* gsfile)
{
	program = createProgram(vsfile, fsfile, gsfile);
}

Controller::~Controller()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(program);
}

void Controller::setVertexInfo(
	float* vertices, int vertices_size,
	int* pointers, int pointer_count,
	int* indices, int indices_size
)
{
	VAO = createVertexInfo(vertices, vertices_size, pointers, pointer_count, indices, indices_size);
}

void Controller::setTexture(const char* filepath)
{
	texture = create2DTextureFromFile(filepath);
}

void Controller::setDepthEnable()
{
	if (depthEnable)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void Controller::setDepthEnable(bool enable)
{
	depthEnable = enable;
}

void Controller::use()
{
	glUseProgram(program);
	glBindVertexArray(VAO);
}

void Controller::setClearColor(float r, float g, float b, float a)
{
	clear_r = r;
	clear_g = g;
	clear_b = b;
	clear_a = a;
}

void Controller::clear()
{
	glClearColor(clear_r, clear_g, clear_b, clear_a);
	if (depthEnable)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	else
		glClear(GL_COLOR_BUFFER_BIT);
}

void Controller::activeTexture(GLenum index)
{
	if (texture)
	{
		glActiveTexture(index);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
}

void Controller::setDraw(void(*func)())
{
	_draw = func;
}

void Controller::draw()
{
	_draw();
}

void Controller::setInt(const char* name, GLint value)
{
	glUniform1i(glGetUniformLocation(program, name), value);
}

void Controller::setMatrix(const char* name, GLsizei count, GLboolean transpos, const GLfloat* value)
{
	glUniformMatrix4fv(glGetUniformLocation(program, name), count, transpos, value);
}

unsigned int Controller::getProgram()
{
	return program;
}
