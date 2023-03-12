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

float framebufferVertices[] = {
	 1.0f, -1.0f,	1.0f, 0.0f,
	-1.0f, -1.0f,	0.0f, 0.0f,
	-1.0f,  1.0f,	0.0f, 1.0f,

	 1.0f,  1.0f,	1.0f, 1.0f,
	 1.0f, -1.0f,	1.0f, 0.0f,
	-1.0f,  1.0f,	0.0f, 1.0f
};

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
	Shader framebufferProg("framebuffer.vert", "framebuffer.frag");

	glm::vec3 LightPosition = glm::vec3(1.0f, 1.5f, 1.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, LightPosition);

	shader.activate();
	framebufferProg.activate();
	glUniform1i(glGetUniformLocation(framebufferProg.ID, "screenTexture"), 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	Camera camera(userWidth, userHeight, glm::vec3(0.0f, 0.0f, 3.0f));

	std::vector<Model> flowers;
	Model modelBee,modelFlower,modelHive,modelTree,modelSunAndMoon,modelFloor;
	modelBee.flip = false;
	modelBee.loadModel("models/Bee.fbx");
	modelFlower.loadModel("models/flower.fbx");
	modelHive.loadModel("models/hive/hive.gltf");
	modelTree.loadModel("models/Tree.fbx");
	modelSunAndMoon.loadModel("models/SunAndMoon.fbx");
	modelFloor.loadModel("models/Floor/floor.gltf");

	modelFloor.position = glm::vec3(0.0f, -9.5f, 0.0f);
	modelFloor.size = glm::vec3(70.0f, 70.0f, 70.0f);

	modelSunAndMoon.size = glm::vec3(5.0f, 5.0f, 5.0f);
	modelSunAndMoon.position = glm::vec3(0.0f, -14.5f, 0.0f);
	modelSunAndMoon.rotation = glm::vec3(1.0f, 0.0f, 0.0f);

	modelTree.position = glm::vec3(5.0f, -9.5f, 0.0f);
	modelTree.size = glm::vec3(2.0f, 2.0f, 2.0f);

	modelHive.radians = 180.0f;
	modelHive.rotation = glm::vec3(0.0f, 0.0f, 1.0f);
	modelHive.position = glm::vec3(0.0f, 0.2f, 0.0f);
	modelHive.size = glm::vec3(1.0f, 1.0f, 1.0f);

	modelBee.size = glm::vec3(0.2f, 0.2f, 0.2f);

	Animation animation("models/Bee.fbx", &modelBee);

	Animator animator(&animation);

	float counter = 0.0f;
	float timeOfDay = 0.0f;
	float multiplier = 10.0f;
	float ammountOfFlowers = 9;

	float redSaturation = 2.0f;
	float greenSaturation = 2.0f;
	float blueSaturation = 2.0f;

	bool beeForward = true;

	shader.setVec3("lightPosition", LightPosition);
	shader.setVec4("lightModel", glm::vec4(redSaturation, greenSaturation, blueSaturation, 1.0f));

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

	Texture orangeBee("models/Bee", "BeeOrange.png", aiTextureType_DIFFUSE), redBee("models/Bee", "BeeRed.png", aiTextureType_DIFFUSE);
	orangeBee.load();
	redBee.load();

	Texture lighterTree("models/Tree", "TreeGreenLighter.png", aiTextureType_DIFFUSE), darkerTree("models/Tree", "TreeGreenDarker.png", aiTextureType_DIFFUSE);
	lighterTree.load(true);
	darkerTree.load(true);

	unsigned int rectVAO, rectVBO;
	glGenVertexArrays(1, &rectVAO);
	glGenBuffers(1, &rectVBO);
	glBindVertexArray(rectVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(framebufferVertices), &framebufferVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	unsigned int FBO;
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	unsigned int framebufferTexture;
	glGenTextures(1, &framebufferTexture);
	glBindTexture(GL_TEXTURE_2D, framebufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, userWidth, userHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

	unsigned int RBO;
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, userWidth, userHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	auto FBOError = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (FBOError != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer error:" << FBOError << std::endl;

	while (!glfwWindowShouldClose(window))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		animator.UpdateAnimation(deltaTime);

		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		camera.Inputs(window);
		camera.updateMatrix();
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)camera.width / camera.height, 0.1f, 500.0f);
		shader.setMat4("projection", projection);

		modelSunAndMoon.Render(shader);
		modelFloor.Render(shader);

		for (unsigned int i = 0; i < flowers.size(); i++) {
			flowers[i].Render(shader);
		}

		//Bee Yellow Texture apply
		if (counter < 3000.0f / multiplier)
			modelBee.Render(shader);
		if (counter > 13000.0f / multiplier)
			modelBee.Render(shader);

		modelHive.Render(shader);
		//Tree Texture swaping
		if (counter < 3000.0f / multiplier)
			modelTree.Render(shader);
		else if (counter >= 3000.0f / multiplier && counter < 6000.0f / multiplier)
			modelTree.Render(shader, lighterTree);
		else if (counter >= 6000.0f / multiplier && counter < 9000.0f / multiplier)
			modelTree.Render(shader, darkerTree);
		else if (counter >= 9000.0f / multiplier && counter < 12000.0f / multiplier)
			modelTree.Render(shader);
		else if (counter >= 12000.0f / multiplier && counter < 15000.0f / multiplier)
			modelTree.Render(shader, darkerTree);
		else if (counter >= 15000.0f / multiplier && counter < 17000.0f / multiplier)
			modelTree.Render(shader, lighterTree);

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

		modelSunAndMoon.radians = (360.0f/72000.0f)*multiplier;
		shader.setVec4("lightModel", glm::vec4(redSaturation, greenSaturation, blueSaturation, 1.0f));

		//Bee Flying animation
		if (counter < 1000.0f / multiplier) {
			counter += 1.0f;
			modelBee.position = glm::vec3(0.0f, 0.0f, 0.025f * multiplier);
		}
		else if (counter >= 1000.0f / multiplier && counter < 3000.0f / multiplier) {
			counter += 1.0f;
			modelBee.position = glm::vec3(0.0f, -0.0135f * multiplier, 0.025f * multiplier);
		}
		//Bee Siting on Flower
		else if (counter >= 3000.0f / multiplier && counter < 13000.0f / multiplier) {
			//Swaping between textures
			if (counter >= 3000.0f / multiplier && counter < 5000.0f / multiplier) {
				modelBee.Render(shader, orangeBee);
			}
			else if (counter >= 5000.0f / multiplier && counter < 7000.0f / multiplier) {
				modelBee.Render(shader, redBee);
			}
			else if (counter >= 7000.0f / multiplier && counter < 9000.0f / multiplier) {
				modelBee.Render(shader, orangeBee);
			}
			else if (counter >= 9000.0f / multiplier && counter < 11000.0f / multiplier) {
				modelBee.Render(shader, redBee);
			}
			else {
				modelBee.Render(shader, orangeBee);
			}
			counter += 1.0f;
		}
		else if (counter >= 13000.0f / multiplier && counter < 15000.0f / multiplier) {
			if (beeForward) {
				modelBee.size = glm::vec3(1.0f, 1.0f, -1.0f);
				beeForward = false;
			}
			counter += 1.0f;
			modelBee.position = glm::vec3(0.0f, 0.0135f * multiplier, 0.025f * multiplier);
		}
		else if (counter >= 15000.0f / multiplier && counter < 16000.0f / multiplier) {
			counter += 1.0f;
			modelBee.position = glm::vec3(0.0f, 0.0f, 0.02525f * multiplier);
		}
		else if (counter >= 16000.0f / multiplier && counter < 17000.0f / multiplier) {
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

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		framebufferProg.activate();
		glBindVertexArray(rectVAO);
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, framebufferTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	modelBee.Cleanup();
	modelFlower.Cleanup();
	modelHive.Cleanup();
	modelTree.Cleanup();
	modelSunAndMoon.Cleanup();
	modelFloor.Cleanup();

	glDeleteFramebuffers(1, &FBO);
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}