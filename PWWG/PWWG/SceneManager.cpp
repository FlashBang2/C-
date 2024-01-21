#include "SceneManager.h"

void Quit(GLFWwindow* window)
{
	glfwSetWindowShouldClose(window, 1);
}

SceneManager::SceneManager(GLuint currentScene)
{
	ID = currentScene;

	Menu* menu = new Menu();
	Example* example = new Example();
	AdvanceExample* advanceExample = new AdvanceExample();

	scenes.push_back(menu);
	scenes.push_back(example);
	scenes.push_back(advanceExample);
}

void SceneManager::Render(GLFWwindow* window, float deltaTime)
{
	switch (ID) 
	{
		case 0:
			scenes[0]->Render(window, deltaTime);
			break;
		case 1:
			scenes[1]->Render(window, deltaTime);
			break;
		case 2:
			scenes[2]->Render(window, deltaTime);
			break;
	}
}