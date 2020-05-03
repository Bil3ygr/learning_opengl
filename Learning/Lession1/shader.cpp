#include "shader.h"
#include "texture.h"

unsigned int createShader(GLenum shaderType, const char* shaderSource)
{
	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Shader compile failed:\n" << infoLog << std::endl;
		glDeleteShader(shader);
		shader = NULL;
	}
	return shader;
}

unsigned int createProgram(int vs, int fs, int gs)
{
	unsigned int program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	if (gs != NULL)
		glAttachShader(program, gs);
	glLinkProgram(program);
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Program link failed:\n" << infoLog << std::endl;
		glDeleteProgram(program);
		program = NULL;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
	if (gs != NULL)
		glDeleteShader(gs);
	return program;
}

unsigned int createProgram(const char* vsfile, const char* fsfile, const char* gsfile)
{
	unsigned int vs = createShader(GL_VERTEX_SHADER, readFile(vsfile));
	if (vs == NULL)
		return NULL;
	unsigned int fs = createShader(GL_FRAGMENT_SHADER, readFile(fsfile));
	if (fs == NULL)
		return NULL;
	unsigned int gs = NULL;
	if (gsfile != nullptr)
	{
		gs = createShader(GL_GEOMETRY_SHADER, readFile(gsfile));
		if (gs == NULL)
			return NULL;
	}
	return createProgram(vs, fs, gs);
}

unsigned int createVertexInfo(
	float* vertices, int vertices_size, 
	int* pointers, int pointer_count,
	int* indices, int indices_size
	)
{
	unsigned int VAO, VBO, EBO = NULL;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// 绑定顶点数组
	glBindVertexArray(VAO);
	// 绑定顶点缓存
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
	// 绑定索引信息
	if (indices)
	{
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);
	}
	// 设置顶点读取信息
	int total = 0;
	for (int i = 0; i < pointer_count; i++)
		total += pointers[i];
	int offset = 0;
	for (int i = 0; i < pointer_count; i++)
	{
		glVertexAttribPointer(
			i, pointers[i], GL_FLOAT, GL_FALSE, total * sizeof(float), 
			(void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(i);
		offset += pointers[i];
	}
	// 清空
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// 删除
	glDeleteBuffers(1, &VBO);
	if (indices)
		glDeleteBuffers(1, &EBO);
	return VAO;
}
