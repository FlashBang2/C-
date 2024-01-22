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
		std::mt19937 generator; 
		std::uniform_int_distribution<std::size_t> pathToFlowersAnimationDistribution;
		glm::vec3 diffuse;
		Object flowersModel[50], beesModel[1], hives[1];
		int selectedFlowersModel[10], animationIndex, currentColorAnimationTime, counter = 0;
		InGameAnimation* pathToFlowers[50];
		InGameAnimation* SunAndMoon;

		glm::vec3 InterpolateColor(float deltaTime, unsigned int ticksPerSecond, float duration);
};

#endif

