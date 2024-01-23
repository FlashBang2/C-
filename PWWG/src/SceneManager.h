#ifndef SCENE_H
#define SCENE_H

#include"Scenes/AdvanceExample.h"
#include"Scenes/Example.h"
#include"Scenes/Menu.h"

#include <sstream>

class SceneManager
{
	public:
		std::vector<GenericScene*> scenes;
		GLuint ID;
		int width = 1920, height = 1080;

		SceneManager() 
		{
			std::stringstream ss;
			ss << "PATH=" << getenv("PATH");
			ss << ";" << "C:\\Users\\Macon\\Documents\\Github\\Cpp\\PWWG\\src\\DLL";

			_putenv_s("PATH", ss.str().c_str());
		};
		SceneManager(GLuint currentScene);

		void Render(GLFWwindow* window, float deltaTime);
	private:
};

#endif 
