#ifndef BUTTON_H
#define BUTTON_H

#include<glm/gtc/type_ptr.hpp>
#include "Model.h"

#include<GLFW/glfw3.h>

enum State
{
	UNHOVER = 0,
	HOVER = 1
};

class Button
{
	public:
		glm::vec3 position;
		State state;
		Model buttonModel;

		Button(glm::vec3 Position);

		void UpdateState(glm::vec2 normalizeMousePosition);
		void Render(Shader shader);
	private:
		glm::vec3 color;
		float maxX, minX, maxY, minY;
		void (*function)(GLFWwindow*);
};

#endif

