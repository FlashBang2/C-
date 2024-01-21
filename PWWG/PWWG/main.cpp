#include"SceneManager.h"

bool firstMousePositionChange = true;
float lastPositionX = 0.0f, lastPositionY = 0.0f;
int offsetX = 0, offsetY = 0;

SceneManager sceneManager;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void cursorPositionCallback(GLFWwindow* window, double posX, double PosY);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(sceneManager.width, sceneManager.height, "Game Engine", NULL, NULL);
	if (window == NULL) 
	{
		std::cout << "Failed To initialize window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);

	gladLoadGL();

	glEnable(GL_DEPTH_TEST);

	float deltaTime = 0, lastTime = 0;

	sceneManager = SceneManager(0);
	
	while (!glfwWindowShouldClose(window)) 
	{
		float currentTime = static_cast<float>(glfwGetTime());
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		glClearColor(0.00f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sceneManager.Render(window, deltaTime);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int Width, int Height)
{
	sceneManager.width = Width;
	sceneManager.height = Height;
	glViewport(0, 0, sceneManager.width, sceneManager.height);
}

void cursorPositionCallback(GLFWwindow* window, double posX, double posY) 
{
	if (sceneManager.ID == 0) 
	{
		sceneManager.scenes[0]->mouseX = posX;
		sceneManager.scenes[0]->mouseY = posY;
	}
	if (sceneManager.ID == 1 || sceneManager.ID == 2) 
	{
		float xPosition = static_cast<float>(posX);
		float yPosition = static_cast<float>(posY);

		if (firstMousePositionChange)
		{
			lastPositionX = xPosition;
			lastPositionY = yPosition;
			firstMousePositionChange = false;
		}

		float xMouseOffset = xPosition - lastPositionX;
		float yMouseOffset = lastPositionY - yPosition;

		lastPositionX = xPosition;
		lastPositionY = yPosition;

		sceneManager.scenes[sceneManager.ID]->cameras[0].HandleMouseMovment(xMouseOffset, yMouseOffset);
		sceneManager.scenes[sceneManager.ID]->cameras[0].Recalculate();
	}
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
	{
		sceneManager.ID = 0;
		glfwSetCursorPos(window, 0, 0);
		cursorPositionCallback(window, 0, 0);
	}

	if (sceneManager.ID == 1 || sceneManager.ID == 2)
	{
		if (key == GLFW_KEY_G && action == GLFW_PRESS) 
		{
			switch (sceneManager.scenes[sceneManager.ID]->gammaCorrection)
			{
				case true:
					sceneManager.scenes[sceneManager.ID]->gammaCorrection = false;
					break;
				case false:
					sceneManager.scenes[sceneManager.ID]->gammaCorrection = true;
					break;
			}
		}	
		if (key == GLFW_KEY_F && action == GLFW_PRESS)
		{
			switch (sceneManager.scenes[sceneManager.ID]->flashlight) 
			{
				case true:
					sceneManager.scenes[sceneManager.ID]->flashlight = false;
					break;
				case false:
					sceneManager.scenes[sceneManager.ID]->flashlight = true;
					break;
			}
		}
	}
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	std::vector<Button> buttons = sceneManager.scenes[sceneManager.ID]->buttons;

	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i].state == HOVER && i == 0 && button == GLFW_MOUSE_BUTTON_LEFT)
		{
			sceneManager.ID = 1;
		}
		if (buttons[i].state == HOVER && i == 1 && button == GLFW_MOUSE_BUTTON_LEFT)
		{
			sceneManager.ID = 2;
		}
		if (buttons[i].state == HOVER && i == 2 && button == GLFW_MOUSE_BUTTON_LEFT)
		{
			glfwSetWindowShouldClose(window, 1);
		}
	}
}