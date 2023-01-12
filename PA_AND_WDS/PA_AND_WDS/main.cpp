#include"Model.h"
#include <random>

const unsigned int width = 1920;
const unsigned int height = 1080;

int main()
{

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);

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

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(1.0f, 1.5f, 1.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	glEnable(GL_DEPTH_TEST);

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

	std::vector<glm::vec3> flowersPositions;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(-30, 30);

	for (int i = 0; i < ammountOfFlowers; i++) {
		flowersPositions.push_back(glm::vec3((float)distr(gen),30.0f,(float)distr(gen)));
	}

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
			greenSaturation -= 0.00005f * multiplier;
			blueSaturation  -= 0.00001f * multiplier;
		}
		else if (timeOfDay >= 31000.0f / multiplier && timeOfDay < 62000.0f / multiplier) {
			timeOfDay++;
			redSaturation   += 0.00008f * multiplier;
			greenSaturation += 0.00005f * multiplier;
			blueSaturation  += 0.00001f * multiplier;
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
		
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	shaderProgram.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}