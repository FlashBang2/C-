#include"Model.h"
#include <random>

const unsigned int width = 1920;
const unsigned int height = 1080;

float gamma = 2.2f;
float exposure = 0.2f;

float framebufferVertices[] = {
	 1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	-1.0f,  1.0f,  0.0f, 1.0f,

	 1.0f,  1.0f,  1.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f,  1.0f,  0.0f, 1.0f
};

int main()
{

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Bee Simulator", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");
	Shader framebufferProgram("framebuffer.vert", "framebuffer.frag");

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(1.0f, 1.5f, 1.5f);
	/*glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);*/

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	framebufferProgram.Activate();
	glUniform1i(glGetUniformLocation(framebufferProgram.ID, "screenTexture"), 0);
	glUniform1f(glGetUniformLocation(framebufferProgram.ID, "gamma"), gamma);
	glUniform1f(glGetUniformLocation(framebufferProgram.ID, "exposure"), exposure);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_FRAMEBUFFER_SRGB);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	std::string modelBeePath = "models/Bee/bee.gltf";
	std::string modelFlowerPath = "models/Flower/flower.gltf";
	std::string modelHivePath = "models/Hive/hive.gltf";
	std::string modelTreePath = "models/Tree/tree.gltf";
	std::string modelSunAndMoonPath = "models/SunAndMoon/SunAndMoon.gltf";
	std::string modelFloorPath = "models/Floor/floor.gltf";
	
	Model modelBee(modelBeePath.c_str());
	Model modelFlower(modelFlowerPath.c_str());
	Model modelHive(modelHivePath.c_str());
	Model modelTree(modelTreePath.c_str());
	Model modelSunAndMoon(modelSunAndMoonPath.c_str());
	Model modelFloor(modelFloorPath.c_str());

	glm::vec3 beeTrajectory = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat beeRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::quat sunAndMoonRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	
	float XDegrees = -0.10f, YDegrees = 0.10f, ZDegrees = -20.0f;

	beeRotation = glm::rotate(beeRotation, XDegrees, glm::vec3(1.0f, 0.0f, 0.0f));		//X
	beeRotation = glm::rotate(beeRotation, YDegrees, glm::vec3(0.0f, 1.0f, 0.0f));		//Y
	beeRotation = glm::rotate(beeRotation, ZDegrees, glm::vec3(0.0f, 0.0f, 1.0f));		//Z

	sunAndMoonRotation = glm::rotate(sunAndMoonRotation, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));		//X
	sunAndMoonRotation = glm::rotate(sunAndMoonRotation, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));		//Y
	sunAndMoonRotation = glm::rotate(sunAndMoonRotation, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));		//Z

	float counter = 0.0f;
	float timeOfDay = 0.0f;
	float multiplier = 10.0f;
	float ammountOfFlowers = 9;

	float redSaturation   = 2.0f;
	float greenSaturation = 2.0f;
	float blueSaturation  = 2.0f;

	bool isDay = true;

	bool lookAtSky = false;

	std::vector<glm::vec3> flowersPositions;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(-30, 30);

	for (int i = 0; i < ammountOfFlowers; i++) {
		flowersPositions.push_back(glm::vec3((float)distr(gen),30.0f,(float)distr(gen)));
	}

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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

	unsigned int RBO;
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	auto FBOError = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (FBOError != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer error: " << FBOError << std::endl;

	while (!glfwWindowShouldClose(window)){

		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glClearColor(pow(0.07f, gamma), pow(0.13f, gamma), pow(0.17f, gamma), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 500.0f);

		modelBee.Draw(shaderProgram, camera, beeTrajectory, beeRotation, glm::vec3(0.25f,0.25f,0.25f));
		modelFlower.Draw(shaderProgram, camera, glm::vec3(30.0f, 30.0f, 0.0f));
		for (int i = 0; i < flowersPositions.size(); i++) {
			modelFlower.Draw(shaderProgram, camera, flowersPositions[i]);
		}
		modelHive.Draw(shaderProgram, camera, glm::vec3(-1.7f, 0.0f, 0.0f));
		modelTree.Draw(shaderProgram, camera, glm::vec3(-5.0f, 31.0f, 18.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(7.0f, 7.0f, 7.0f));
		modelSunAndMoon.Draw(shaderProgram, camera, glm::vec3(0.0f, 0.0f, 0.0f), sunAndMoonRotation, glm::vec3(10.0f, 20.0f, 10.0f));
		modelFloor.Draw(shaderProgram, camera, glm::vec3(0.0f, 0.3f, 0.0f));

		//Day Night cycle
		if (timeOfDay < 31000.0f / multiplier) {
			timeOfDay++;
			redSaturation   -= 0.00008f * multiplier;
			greenSaturation -= 0.00006f * multiplier;
			blueSaturation  -= 0.00002f * multiplier;
		}
		else if (timeOfDay >= 31000.0f / multiplier && timeOfDay < 62000.0f / multiplier) {
			timeOfDay++;
			redSaturation   += 0.00008f * multiplier;
			greenSaturation += 0.00006f * multiplier;
			blueSaturation  += 0.00002f * multiplier;
		}
		else {
			timeOfDay = 0.0f;
		}
		XDegrees = 0.0000f * multiplier;
		YDegrees = 0.0000f * multiplier;
		ZDegrees = 0.0001f * multiplier;
		sunAndMoonRotation = glm::rotate(sunAndMoonRotation, XDegrees, glm::vec3(1.0f, 0.0f, 0.0f));		//X
		sunAndMoonRotation = glm::rotate(sunAndMoonRotation, YDegrees, glm::vec3(0.0f, 1.0f, 0.0f));		//Y
		sunAndMoonRotation = glm::rotate(sunAndMoonRotation, ZDegrees, glm::vec3(0.0f, 0.0f, 1.0f));		//Z
		lightColor = glm::vec4(redSaturation, greenSaturation, blueSaturation, 1.0f);
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		
		if (counter < 3000.0f / multiplier) {
			if (counter >= 2900.0f / multiplier && counter < 3000.0f / multiplier) {
				XDegrees = 0.00025f * multiplier;
				YDegrees = 0.00255f * multiplier;
				ZDegrees = 0.02200f * multiplier;
				beeRotation = glm::rotate(beeRotation, XDegrees, glm::vec3(1.0f, 0.0f, 0.0f));		//X
				beeRotation = glm::rotate(beeRotation, YDegrees, glm::vec3(0.0f, 1.0f, 0.0f));		//Y
				beeRotation = glm::rotate(beeRotation, ZDegrees, glm::vec3(0.0f, 0.0f, 1.0f));		//Z
			}
			counter += 1.0f;
			beeTrajectory[0] += 0.0123f * multiplier;
			beeTrajectory[1] -= 0.0046f * multiplier;
			beeTrajectory[2] += 0.0004f * multiplier;
		}
		else if (counter >= 3000.0f / multiplier && counter <= 3500.0f / multiplier) {
			counter += 1.0f;
		}
		else if (counter >= 3500.0f / multiplier && counter <= 6500.0f / multiplier) {
			if (counter >= 3500.0f / multiplier && counter < 3600.0f / multiplier) {
				XDegrees = -0.00125f * multiplier;
				YDegrees = -0.01250f * multiplier;
				ZDegrees =  0.01500f * multiplier;
				beeRotation = glm::rotate(beeRotation, XDegrees, glm::vec3(1.0f, 0.0f, 0.0f));		//X
				beeRotation = glm::rotate(beeRotation, YDegrees, glm::vec3(0.0f, 1.0f, 0.0f));		//Y
				beeRotation = glm::rotate(beeRotation, ZDegrees, glm::vec3(0.0f, 0.0f, 1.0f));		//Z
			}
			counter += 1.0f;
			beeTrajectory[0] -= 0.0123f * multiplier;
			beeTrajectory[1] += 0.0046f * multiplier;
			beeTrajectory[2] -= 0.0004f * multiplier;
		}
		else if (counter > 6500.0f / multiplier && counter <= 7000.0f / multiplier) {
			counter += 1.0f;
			beeTrajectory[0] -= 0.0123f * multiplier;
			beeTrajectory[1] -= 0.0046f * multiplier;
			beeTrajectory[2] += 0.0104f * multiplier;
		}
		else if (counter >= 7000.0f / multiplier && counter < 7500.0f / multiplier) {
			if (counter >= 7000.0f / multiplier && counter < 7100.0f / multiplier) {
				XDegrees =  0.00100f * multiplier;
				YDegrees =  0.00995f * multiplier;
				ZDegrees = -0.03700f * multiplier;
				beeRotation = glm::rotate(beeRotation, XDegrees, glm::vec3(1.0f, 0.0f, 0.0f));		//X
				beeRotation = glm::rotate(beeRotation, YDegrees, glm::vec3(0.0f, 1.0f, 0.0f));		//Y
				beeRotation = glm::rotate(beeRotation, ZDegrees, glm::vec3(0.0f, 0.0f, 1.0f));		//Z
			}
			counter += 1.0f;
		}
		else if (counter >= 7500.0f / multiplier && counter < 8000.0f / multiplier) {
			counter += 1.0f;
			beeTrajectory[0] += 0.0123f * multiplier;
			beeTrajectory[1] += 0.0046f * multiplier;
			beeTrajectory[2] -= 0.0104f * multiplier;
		}
		else {
			beeRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
			XDegrees = -0.10f, YDegrees = 0.10f, ZDegrees = -20.0f;
			beeRotation = glm::rotate(beeRotation, XDegrees, glm::vec3(1.0f, 0.0f, 0.0f));		//X
			beeRotation = glm::rotate(beeRotation, YDegrees, glm::vec3(0.0f, 1.0f, 0.0f));		//Y
			beeRotation = glm::rotate(beeRotation, ZDegrees, glm::vec3(0.0f, 0.0f, 1.0f));		//Z
			counter = 0.0f;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		framebufferProgram.Activate();
		glBindVertexArray(rectVAO);
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, framebufferTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}