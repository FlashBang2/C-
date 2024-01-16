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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

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
	Shader SunAndMoonProgram("default.vert", "SunAndMoon.frag");
	Shader framebufferProgram("framebuffer.vert", "framebuffer.frag");
	Shader blurringProgram("framebuffer.vert", "blur.frag");
	Shader streakingProgram("framebuffer.vert", "streak.frag");

	float lightAngle1 = 0.0f;
	float lightAngle2 = -1.0f;
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	SunAndMoonProgram.Activate();
	glUniform4f(glGetUniformLocation(SunAndMoonProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(SunAndMoonProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	framebufferProgram.Activate();
	glUniform1i(glGetUniformLocation(framebufferProgram.ID, "screenTexture"), 0);
	glUniform1i(glGetUniformLocation(framebufferProgram.ID, "bloomTexture"), 1);
	glUniform1f(glGetUniformLocation(framebufferProgram.ID, "gamma"), gamma);
	glUniform1f(glGetUniformLocation(framebufferProgram.ID, "exposure"), exposure);
	blurringProgram.Activate();
	glUniform1i(glGetUniformLocation(blurringProgram.ID, "screenTexture"), 0);
	streakingProgram.Activate();
	glUniform1i(glGetUniformLocation(streakingProgram.ID, "screenTexture"), 0);

	float redSaturation = 2.0f;
	float greenSaturation = 2.0f;
	float blueSaturation = 1.8f;

	glEnable(GL_FRAMEBUFFER_SRGB);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	std::string modelBeePath = "models/Bee/bee.gltf";
	std::string modelFlowerPath = "models/Flower/flower.gltf";
	std::string modelHivePath = "models/Hive/hive.gltf";
	std::string modelTreePath = "models/Tree/tree.gltf";
	std::string modelSunPath = "models/Sun/sun.gltf";
	std::string modelMoonPath = "models/Moon/moon.gltf";
	std::string modelFloorPath = "models/Floor/floor.gltf";

	Model modelBee(modelBeePath.c_str());
	Model modelFlower(modelFlowerPath.c_str());
	Model modelHive(modelHivePath.c_str());
	Model modelTree(modelTreePath.c_str());
	Model modelSun(modelSunPath.c_str());
	Model modelMoon(modelMoonPath.c_str());
	Model modelFloor(modelFloorPath.c_str());

	glm::vec3 beeTrajectory = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat beeRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	
	float XDegrees = -0.10f, YDegrees = 0.10f, ZDegrees = -20.0f;

	beeRotation = glm::rotate(beeRotation, XDegrees, glm::vec3(1.0f, 0.0f, 0.0f));		//X
	beeRotation = glm::rotate(beeRotation, YDegrees, glm::vec3(0.0f, 1.0f, 0.0f));		//Y
	beeRotation = glm::rotate(beeRotation, ZDegrees, glm::vec3(0.0f, 0.0f, 1.0f));		//Z

	float counter = 0.0f;
	float timeOfDay = 0.0f;
	float multiplier = 5.0f;
	float ammountOfFlowers = 9;
	float sunAndMoonAxis1 = 0;
	float sunAndMoonAxis2 = -200;

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

	unsigned int bloomTexture;
	glGenTextures(1, &bloomTexture);
	glBindTexture(GL_TEXTURE_2D, bloomTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, bloomTexture, 0);

	unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachments);

	auto FBOError = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (FBOError != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer error: " << FBOError << std::endl;

	unsigned int pingpongFBO[2];
	unsigned int pingpongBuffer[2];
	glGenFramebuffers(2, pingpongFBO);
	glGenTextures(2, pingpongBuffer);
	for (unsigned int i = 0; i < 2; i++) {
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, pingpongBuffer[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongBuffer[i], 0);

		FBOError = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (FBOError != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Ping-Pong Framebuffer error: " << FBOError << std::endl;
	}

	while (!glfwWindowShouldClose(window)){
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glClearColor(pow(0.005f, gamma), pow(0.013f, gamma), pow(0.017f, gamma), 1.0f);
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
		modelSun.Draw(SunAndMoonProgram, camera, glm::vec3(sunAndMoonAxis1, sunAndMoonAxis2, 0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f));
		modelMoon.Draw(SunAndMoonProgram, camera, glm::vec3(-sunAndMoonAxis1, -sunAndMoonAxis2, 0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f));
		modelFloor.Draw(shaderProgram, camera, glm::vec3(0.0f, 0.3f, 0.0f));

		glUniform1f(glGetUniformLocation(shaderProgram.ID, "lightAngle1"), lightAngle1);
		glUniform1f(glGetUniformLocation(shaderProgram.ID, "lightAngle2"), lightAngle2);
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

		bool horizontal = true, firstIteration = true;
		int blurAmount = 3;
		//Tylko jeden na raz mo¿e dzia³aæ
		//blurringProgram.Activate();
		streakingProgram.Activate();
		for (int i = 0; i < blurAmount; i++) {
			glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
			glUniform1i(glGetUniformLocation(blurringProgram.ID, "horizontal"), horizontal);

			if (firstIteration) {
				glBindTexture(GL_TEXTURE_2D, bloomTexture);
				firstIteration = false;
			}
			else {
				glBindTexture(GL_TEXTURE_2D, pingpongBuffer[!horizontal]);
			}
			glBindVertexArray(rectVAO);
			glDisable(GL_DEPTH_TEST);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			horizontal = !horizontal;
		}

		//Day Night cycle
		if (timeOfDay < 31000.0f / multiplier) {
			timeOfDay++;
			redSaturation -= 0.000064f * multiplier;
			greenSaturation -= 0.000062f * multiplier;
			blueSaturation  -= 0.000045f * multiplier;
			if (timeOfDay < 15500.0f / multiplier) {
				lightAngle1 += 1.0f / 15500.0f * multiplier;
				sunAndMoonAxis1 += 200.0f / 15500.0f * multiplier;
				lightAngle2 += 1.0f / 15500.0f * multiplier;
				sunAndMoonAxis2 += 200.0f / 15500.0f * multiplier;
			}
			else {
				lightAngle1 -= 1.0f / 15500.0f * multiplier;
				sunAndMoonAxis1 -= 200.0f / 15500.0f * multiplier;
				lightAngle2 += 1.0f / 15500.0f * multiplier;
				sunAndMoonAxis2 += 200.0f / 15500.0f * multiplier;
			}
		}
		else if (timeOfDay >= 31000.0f / multiplier && timeOfDay < 62000.0f / multiplier) {
			timeOfDay++;
			redSaturation += 0.000064f * multiplier;
			greenSaturation += 0.000062f * multiplier;
			blueSaturation  += 0.000045f * multiplier;
			if (timeOfDay < 46500.0f / multiplier) {
				lightAngle1 -= 1.0f / 15500.0f * multiplier;
				sunAndMoonAxis1 -= 200.0f / 15500.0f * multiplier;
				lightAngle2 -= 1.0f / 15500.0f * multiplier;
				sunAndMoonAxis2 -= 200.0f / 15500.0f * multiplier;
			}
			else {
				lightAngle1 += 1.0f / 15500.0f * multiplier;
				sunAndMoonAxis1 += 200.0f / 15500.0f * multiplier;
				lightAngle2 -= 1.0f / 15500.0f * multiplier;
				sunAndMoonAxis2 -= 200.0f / 15500.0f * multiplier;
			}
		}
		else {
			timeOfDay = 0.0f;
		}
		lightColor = glm::vec4(redSaturation, greenSaturation, blueSaturation, 1.0f);
		
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
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, framebufferTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, pingpongBuffer[!horizontal]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}