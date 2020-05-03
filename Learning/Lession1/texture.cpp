#include "texture.h"
#include "../stb_image.h"

unsigned int create2DTextureFromData(
	ImageData data, 
	GLenum swrap, 
	GLenum twrap, 
	GLenum minfilter, 
	GLenum maxfilter, 
	GLenum colorType, 
	float* borderColor,
	bool useMipmap)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// ���Ʒ�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, swrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, twrap);
	//for GL_CLAMP_TO_BORDER
	if (swrap == GL_CLAMP_TO_BORDER || twrap == GL_CLAMP_TO_BORDER)
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// �������, Mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minfilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxfilter);
	// ����
	glTexImage2D(GL_TEXTURE_2D, 0, colorType, data.width, data.height, 0, data.colorType, GL_UNSIGNED_BYTE, data.data);
	// ���filter������mipmap��Ҫ���ɣ����򿴲���
	if (useMipmap)
		glGenerateMipmap(GL_TEXTURE_2D);
	return texture;
}

unsigned int create2DTextureFromFile(const char* filepath)
{
	unsigned int texture = NULL;
	// ���ز�����
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
	if (data)
	{
		ImageData image = ImageData(width, height, data);
		texture = create2DTextureFromData(image);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Load texture failed." << std::endl;
	}

	return texture;
}
