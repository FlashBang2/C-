#ifndef GENERIC_SCENE_H
#define GENERIC_SCENE_H

#include"../Button.h"
#include"../Camera.h"
#include"../Animator.h"

class GenericScene
{
	public:
		std::vector<Camera> cameras;
		std::vector<Button> buttons;
		bool flashlight, gammaCorrection;
		int width = 800, height = 800;
		double mouseX, mouseY;

		GenericScene() {};
		
		virtual void Render(GLFWwindow* window, float deltaTime) {};
	protected:
		std::vector<Animator> animators;
		std::vector<Shader> shaders;
		std::vector<Model> models;
		std::vector<glm::vec3> lightPositions;
		glm::mat4 projection;
	private:
};

#endif

