#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_inverse.hpp>
#include <random>

#include "model.h"
#include "Shader.h"
#include "Camera.h"
#include "Animation.h"
#include "Animator.h"

const unsigned int userWidth = 1920;
const unsigned int userHeight = 1080;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {

	float radians = 0.0f, deltaTime = 0.0f, lastTime = 0.0f;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(userWidth, userHeight, "BeeSimulator", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, userWidth, userHeight);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader shader("VertexShader.glsl", "FragmentShader.glsl");

	std::vector<Model> flowers;
	Model modelBee,modelFlower,modelHive,modelTree,modelSunAndMoon,modelFloor;
	modelBee.loadModel("models/Bee.fbx");
	modelFlower.flip = true;
	modelFlower.loadModel("models/flower.fbx");
	modelHive.flip = true;
	modelHive.loadModel("models/hive/hive.gltf");
	modelTree.flip = true;
	modelTree.loadModel("models/Tree.fbx");
	modelSunAndMoon.flip = true;
	modelSunAndMoon.loadModel("models/SunAndMoon.fbx");
	modelFloor.flip = true;
	modelFloor.loadModel("models/Floor/floor.gltf");

	modelFloor.position = glm::vec3(0.0f, -9.5f, 0.0f);
	modelFloor.size = glm::vec3(70.0f, 70.0f, 70.0f);

	modelSunAndMoon.radians = 10.0f;
	modelSunAndMoon.size = glm::vec3(5.0f, 5.0f, 5.0f);
	modelSunAndMoon.position = glm::vec3(0.0f, -14.5f, 0.0f);
	modelSunAndMoon.rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	//modelTree.rotation = glm::vec3(0.0f, 0.0f, 90.0f);
	modelTree.position = glm::vec3(5.0f, -9.5f, 0.0f);
	modelTree.size = glm::vec3(2.0f, 2.0f, 2.0f);

	modelHive.radians = 180.0f;
	modelHive.rotation = glm::vec3(0.0f, 0.0f, 1.0f);
	modelHive.position = glm::vec3(0.0f, 0.2f, 0.0f);
	modelHive.size = glm::vec3(1.0f, 1.0f, 1.0f);

	//modelBee.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	modelBee.size = glm::vec3(0.2f, 0.2f, 0.2f);

	Animation animation("models/Bee.fbx", &modelBee);

	Animator animator(&animation);

	glEnable(GL_DEPTH_TEST);

	Camera camera(userWidth, userHeight, glm::vec3(0.0f, 0.0f, 3.0f));

	shader.activate();

	glm::vec3 LightPosition = glm::vec3(1.0f, 1.5f, 1.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, LightPosition);

	float counter = 0.0f;
	float timeOfDay = 0.0f;
	float multiplier = 10.0f;
	float ammountOfFlowers = 9;

	float redSaturation = 2.0f;
	float greenSaturation = 2.0f;
	float blueSaturation = 2.0f;

	bool beeForward = true;

	shader.setVec3("lightPosition", LightPosition);
	shader.setVec4("lightColor", glm::vec4(redSaturation, greenSaturation, blueSaturation, 1.0f));

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(-30, 30);

	for (unsigned int i = 0; i < 9;i++) {
		if(i==1)
			modelFlower.position = glm::vec3(0.0f, -9.5f, 15.0f);
		else
			modelFlower.position = glm::vec3((float)distr(gen), -9.5f, (float)distr(gen));
		flowers.push_back(modelFlower);
	}

	while (!glfwWindowShouldClose(window))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		animator.UpdateAnimation(deltaTime);

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);

		camera.updateMatrix();
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)camera.width / camera.height, 0.1f, 500.0f);
		shader.setMat4("projection", projection);

		auto transforms = animator.GetCalculatedBoneMatrix();
		for (unsigned int i = 0; i < transforms.size(); i++) {
			shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
			shader.setMat4("finalBonesNormal[" + std::to_string(i) + "]", glm::inverseTranspose(transforms[i]));
		}

		//Day Night cycle
		if (timeOfDay < 36000.0f / multiplier) {
			timeOfDay++;
			redSaturation -= 0.00007f * multiplier;
			greenSaturation -= 0.00005f * multiplier;
			blueSaturation -= 0.00001f * multiplier;
		}
		else if (timeOfDay >= 36000.0f / multiplier && timeOfDay < 72000.0f / multiplier) {
			timeOfDay++;
			redSaturation += 0.00007f * multiplier;
			greenSaturation += 0.00005f * multiplier;
			blueSaturation += 0.00001f * multiplier;
		}
		else {
			timeOfDay = 0.0f;
			float redSaturation = 2.0f;
			float greenSaturation = 2.0f;
			float blueSaturation = 2.0f;
		}

		shader.setVec4("lightColor", glm::vec4(redSaturation, greenSaturation, blueSaturation, 1.0f));

		modelBee.Render(shader);
		modelHive.Render(shader);
		modelTree.Render(shader);
		modelSunAndMoon.Render(shader);
		modelFloor.Render(shader);
		for (unsigned int i = 0; i < flowers.size(); i++) {
			flowers[i].Render(shader);
		}

		if (counter < 1000.0f / multiplier) {
			counter += 1.0f;
			modelBee.position = glm::vec3(0.0f, 0.0f, 0.025f * multiplier);
		}
		else if (counter >= 1000.0f / multiplier && counter < 3000.0f / multiplier) {
			counter += 1.0f;
			modelBee.position = glm::vec3(0.0f, -0.0135f * multiplier, 0.025f * multiplier);
		}
		else if (counter >= 3000.0f / multiplier && counter < 4000.0f / multiplier) {
			counter += 1.0f;
		}
		else if (counter >= 4000.0f / multiplier && counter < 6000.0f / multiplier) {
			if (beeForward) {
				modelBee.size = glm::vec3(1.0f, 1.0f, -1.0f);
				beeForward = false;
			}
			counter += 1.0f;
			modelBee.position = glm::vec3(0.0f, 0.0135f * multiplier, 0.025f * multiplier);
		}
		else if (counter >= 6000.0f / multiplier && counter < 7000.0f / multiplier) {
			counter += 1.0f;
			modelBee.position = glm::vec3(0.0f, 0.0f, 0.02525f * multiplier);
		}
		else if (counter >= 7000.0f / multiplier && counter < 8000.0f / multiplier) {
			counter += 1.0f;
		}
		else {
			counter = 1.0f;
			modelBee.size = glm::vec3(1.0f, 1.0f, -1.0f);
			beeForward = true;
		}

		shader.setVec3("cameraPosition", glm::vec3(camera.Position.x, camera.Position.y, camera.Position.z));

		shader.setMat4("camMatrix", camera.cameraMatrix);

		processInput(window);
		
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	modelBee.Cleanup();
	modelFlower.Cleanup();
	modelHive.Cleanup();
	modelTree.Cleanup();
	modelSunAndMoon.Cleanup();
	modelFloor.Cleanup();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}