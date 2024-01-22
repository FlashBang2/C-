#ifndef SCENE_DATA_H
#define SCENE_DATA_H

#include"GenericScene.h"

class Example:public GenericScene
{
	public:
		Example();

		void Render(GLFWwindow* window, float deltaTime);
	private:
		Object boxesModel[4];
		GLuint pingpongFBO[2], pingpongColorBuffers[2];
		GLuint HDR, colorBuffers[2], VAO = 0;

		void RenderQuadFullScreen();
};

#endif

