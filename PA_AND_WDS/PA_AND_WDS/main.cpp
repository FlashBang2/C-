#include"Model.h"

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
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	std::string modelPath = "models/Bee/head/head.gltf";
	std::string modelPath2 = "models/Bee/abdomen/abdomen.gltf";
	std::string modelPath3 = "models/Bee/legLB/legLB.gltf";
	std::string modelPath4 = "models/Bee/legLF/LegLF.gltf";
	std::string modelPath5 = "models/Bee/legLM/legLM.gltf";
	std::string modelPath6 = "models/Bee/legRB/legRB.gltf";
	std::string modelPath7 = "models/Bee/legRF/legRF.gltf";
	std::string modelPath8 = "models/Bee/legRM/legRM.gltf";
	std::string modelPath9 = "models/Bee/thorax/thorax.gltf";
	std::string modelPath10 = "models/Bee/wingL/wingL.gltf";
	std::string modelPath11 = "models/Bee/wingR/wingR.gltf";
	std::string modelPath12 = "models/Bee/sting/sting.gltf";
	
	Model model(modelPath.c_str());
	Model model2(modelPath2.c_str());
	Model model3(modelPath3.c_str());
	Model model4(modelPath4.c_str());
	Model model5(modelPath5.c_str());
	Model model6(modelPath6.c_str());
	Model model7(modelPath7.c_str());
	Model model8(modelPath8.c_str());
	Model model9(modelPath9.c_str());
	Model model10(modelPath10.c_str());
	Model model11(modelPath11.c_str());
	Model model12(modelPath12.c_str());

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);

		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		model.Draw(shaderProgram, camera);
		model2.Draw(shaderProgram, camera);
		model3.Draw(shaderProgram, camera);
		model4.Draw(shaderProgram, camera);
		model5.Draw(shaderProgram, camera);
		model6.Draw(shaderProgram, camera);
		model7.Draw(shaderProgram, camera);
		model8.Draw(shaderProgram, camera);
		model9.Draw(shaderProgram, camera);
		model10.Draw(shaderProgram, camera);
		model11.Draw(shaderProgram, camera);
		model12.Draw(shaderProgram, camera);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	shaderProgram.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}