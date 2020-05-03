#include "main.h"
#include "Lession1/shader.h"
#include "Lession1/texture.h"
#include "Lession1/creator.h"

Controller* colorRectController = nullptr;
Controller* textureRectController = nullptr;
Controller* cubeController = nullptr;
Controller* currentController = nullptr;

void drawColorRect()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void createColorRect()
{
	if (!colorRectController)
	{
		colorRectController = new Controller("Lession1/vs.glsl", "Lession1/fs.glsl");
		createColorRectInfo(colorRectController);
		colorRectController->setDraw(drawColorRect);
		colorRectController->setClearColor(0.2f, 0.3f, 0.3f);
	}
	currentController = colorRectController;
}

void drawTextureRect()
{
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
	currentController->setMatrix("transform", 1, GL_FALSE, glm::value_ptr(trans));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void createTextureRect()
{
	if (!textureRectController)
	{
		textureRectController = new Controller("Lession1/texvs.glsl", "Lession1/texfs.glsl");
		createTextureRectInfo(textureRectController);
		textureRectController->setTexture("Lession1/container.jpg");
		textureRectController->setDraw(drawTextureRect);
		textureRectController->setClearColor(0.3f, 0.2f, 0.3f);
	}
	currentController = textureRectController;
}

void drawCube()
{
	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	currentController->setMatrix("model", 1, GL_FALSE, glm::value_ptr(model));
	currentController->setMatrix("view", 1, GL_FALSE, glm::value_ptr(view));
	currentController->setMatrix("projection", 1, GL_FALSE, glm::value_ptr(projection));
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void createCube()
{
	if (!cubeController)
	{
		cubeController = new Controller("Lession1/cubevs.glsl", "Lession1/texfs.glsl");
		createCubeInfo(cubeController);
		cubeController->setTexture("Lession1/container.jpg");
		cubeController->setDraw(drawCube);
		cubeController->setDepthEnable(true);
		cubeController->setClearColor(0.3f, 0.3f, 0.2f);
	}
	currentController = cubeController;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow* initGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Create window failed" << std::endl;
		return NULL;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Init GLAD fialed" << std::endl;
		return NULL;
	}

	return window;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		createColorRect();
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		createTextureRect();
	else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		createCube();
}

int start()
{
	GLFWwindow* window = initGLFW();
	if (window == NULL)
	{
		glfwTerminate();
		system("pause");
		return -1;
	}

	createColorRect();

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		if (currentController->getProgram() == NULL)
		{
			glfwTerminate();
			system("pause");
			return -1;
		}

		currentController->setDepthEnable();
		currentController->clear();
		currentController->use();
		currentController->activeTexture(GL_TEXTURE0);
		currentController->draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	currentController = nullptr;
	delete colorRectController;
	colorRectController = nullptr;
	delete textureRectController;
	textureRectController = nullptr;
	delete cubeController;
	cubeController = nullptr;

	glfwTerminate();
	return 0;
}

int main()
{
	return start();
}