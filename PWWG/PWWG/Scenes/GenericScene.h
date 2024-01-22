#ifndef GENERIC_SCENE_H
#define GENERIC_SCENE_H

#include"../Button.h"
#include"../Camera.h"
#include"../Animator.h"

struct Flashlight 
{
	glm::vec3 ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);
	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;
};

struct PointLight 
{
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float constant = 1.0f;
	float linear;
	float quadratic;
};

struct Object
{
	glm::mat4 model;

	float strengthOfRotation;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

class GenericScene
{
	public:
		std::vector<Camera> cameras;
		std::vector<Button> buttons;
		std::vector<PointLight> pointLights;
		Flashlight flashlightObject;
		bool flashlight, gammaCorrection, hdr, bloom;
		int width = 800, height = 800;
		double mouseX, mouseY;

		GenericScene() {};
		
		virtual void Render(GLFWwindow* window, float deltaTime) {};
	protected:
		std::vector<Animator> animators;
		std::vector<Shader> shaders;
		std::vector<Model> models;
		glm::mat4 projection;
	private:
};

#endif

