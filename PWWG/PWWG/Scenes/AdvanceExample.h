#ifndef ADVANCE_EXAMPLE_H
#define ADVANCE_EXAMPLE_H

#include<random>

#include"GenericScene.h"

class AdvanceExample:public GenericScene
{
	public:
		AdvanceExample();

		void Render(GLFWwindow* window, float deltaTime);
	private:
		Object flowersModel[50];
		int selectedFlowersModel[10];
};

#endif

