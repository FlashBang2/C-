#ifndef ADVANCE_EXAMPLE_H
#define ADVANCE_EXAMPLE_H

#include<random>

#include"../InGameAnimation.h"
#include"GenericScene.h"

class AdvanceExample:public GenericScene
{
	public:
		AdvanceExample();

		void Render(GLFWwindow* window, float deltaTime);
	private:
		Object flowersModel[50], beesModel[1];
		int selectedFlowersModel[10];
		InGameAnimation* pathToFlowers[50];
		InGameAnimation* SunAndMoon;
};

#endif

