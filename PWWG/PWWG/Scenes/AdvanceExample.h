#ifndef ADVANCE_EXAMPLE_H
#define ADVANCE_EXAMPLE_H

#include"GenericScene.h"

class AdvanceExample:public GenericScene
{
	public:
		AdvanceExample() {};

		void Render(GLFWwindow* window, float deltaTime);
	private:
};

#endif

