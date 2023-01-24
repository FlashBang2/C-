#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

	Model model;
	model.loadModel("models/boblampclean.md5mesh");
	
	Animation animation("models/boblampclean.md5anim", &model);

	Animator animator(&animation);

	glEnable(GL_DEPTH_TEST);

	Camera camera(userWidth, userHeight, glm::vec3(0.0f, 0.0f, 2.0f));

	shader.activate();

	glm::vec3 LightPosition = glm::vec3(1.0f, 1.5f, 1.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, LightPosition);

	shader.setVec3("lightPosition", LightPosition);
	shader.setVec4("lightColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	while (!glfwWindowShouldClose(window))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		animator.UpdateAnimation(deltaTime);

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);

		camera.updateMatrix(45.0f, 0.1f, 500.0f);

		auto transforms = animator.GetCalculatedBoneMatrix();
		for (unsigned int i = 0; i < transforms.size(); i++) {
			shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
		}

		model.rotation = glm::vec3(0.0f, 1.0f, 0.0f);
		model.radians = 0.05f;

		model.Render(shader);

		shader.setVec3("cameraPosition", glm::vec3(camera.Position.x, camera.Position.y, camera.Position.z));

		shader.setMat4("camMatrix", camera.cameraMatrix);

		processInput(window);
		
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	model.Cleanup();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}