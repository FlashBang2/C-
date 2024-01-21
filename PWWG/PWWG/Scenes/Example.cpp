#include "Example.h"

Example::Example()
	:objectsPositions{glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 2.0f, 0.0f)}
{
	Shader shader("Shaders/Mesh.vert", "Shaders/Mesh.frag");
	Shader light("Shaders/Light.vert", "Shaders/Light.frag");

	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));

	Model box("Models/Box/box.obj");

	glm::vec3 pointLightPosition = glm::vec3(0.0f, 3.0f, -3.0f);

	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	shaders.push_back(shader);
	shaders.push_back(light);

	cameras.push_back(camera);

	models.push_back(box);

	lightPositions.push_back(pointLightPosition);
}

void Example::Render(GLFWwindow* window, float deltaTime)
{
	cameras[0].HandleEvents(window, deltaTime);
	cameras[0].Update();

	shaders[0].Activate();

	shaders[0].SetFloat("material.shininess", 64.0f);

	shaders[0].SetVec3("pointLight.position", lightPositions[0]);
	shaders[0].SetVec3("pointLight.ambient", 0.2f, 0.2f, 0.2f);
	shaders[0].SetVec3("pointLight.diffuse", 0.7f, 0.7f, 0.7f);
	shaders[0].SetVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);
	shaders[0].SetFloat("pointLight.constant", gammaCorrection ? 2.0f : 1.0f);
	shaders[0].SetFloat("pointLight.linear", gammaCorrection ? 0.08f : 0.04f);
	shaders[0].SetFloat("pointLight.quadratic", gammaCorrection ? 0.032f : 0.016f);

	shaders[0].SetInt("spotLight.on", flashlight);
	shaders[0].SetVec3("spotLight.position", cameras[0].position);
	shaders[0].SetVec3("spotLight.direction", cameras[0].front);
	shaders[0].SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	shaders[0].SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
	shaders[0].SetVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	shaders[0].SetVec3("spotLight.diffuse", 0.8f, 0.8f, 0.8f);
	shaders[0].SetVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	shaders[0].SetFloat("spotLight.constant", gammaCorrection ? 2.0f : 1.0f);
	shaders[0].SetFloat("spotLight.linear", gammaCorrection ? 0.18f : 0.09f);
	shaders[0].SetFloat("spotLight.quadratic", gammaCorrection ? 0.064f : 0.032f);

	shaders[0].SetVec3("viewPosition", cameras[0].position);
	shaders[0].SetInt("gammaCorrection", gammaCorrection);

	for (int i = 0; i < objectsPositions.size(); i++)
	{
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, objectsPositions[i]);
		model = glm::rotate(model, glm::radians(0.5f), glm::vec3(0.0f, 1.0f, 0.0f));

		shaders[0].SetMat4("model", model);
		shaders[0].SetMat4("view", cameras[0].view);
		shaders[0].SetMat4("projection", projection);

		models[0].Draw(shaders[0], gammaCorrection);
	}

	shaders[1].Activate();
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, lightPositions[0]);

	glm::mat4 mvp = projection * cameras[0].view * model;

	shaders[1].SetMat4("mvp", mvp);

	models[0].Draw(shaders[1], gammaCorrection);
}
