#include "utils.h"


const char* readFile(const char* filename, int filesize)
{
	std::ifstream file(filename);
	char* content = (char*)malloc(sizeof(char) * filesize);
	if (content)
	{
		char buffer[1024];
		int pt = 0;
		while (file.getline(buffer, 1024))
		{
			for (int i = 0; i < 1024; i++)
			{
				char temp = buffer[i];
				if (temp == '\0')
				{
					content[pt] = '\n';
					pt++;
					break;
				}
				content[pt] = temp;
				pt++;
			}
		}
		content[pt] = '\0';
		char* result = (char*)malloc(sizeof(char) * (++pt));
		if (!result)
			return NULL;
		for (int i = 0; i < pt; i++)
			result[i] = content[i];
		return result;
	}
	return NULL;
}
