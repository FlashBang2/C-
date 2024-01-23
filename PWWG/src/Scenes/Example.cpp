#include "Example.h"

Example::Example()
	: boxesModel{ {glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f)},
				  {glm::mat4(1.0f), 30.0f, glm::vec3(-3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.8f, 0.8f, 0.8f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)}}
{
	Shader shader("../src/Shaders/Mesh.vert", "../src/Shaders/Mesh.frag");
	Shader light("../src/Shaders/Light.vert", "../src/Shaders/Light.frag");
	Shader postProcessing("../src/Shaders/PostProcessing.vert", "../src/Shaders/PostProcessing.frag");
	Shader blur("../src/Shaders/Blur.vert", "../src/Shaders/Blur.frag");

	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));

	Model box("../src/Models/Box/box.obj");

	PointLight pointLight;

	pointLight.position = glm::vec3(0.0f, 5.0f, -3.0f);
	pointLight.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	pointLight.diffuse = glm::vec3(10.0f, 10.0f, 10.0f);
	pointLight.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	pointLight.linear = 0.09f;
	pointLight.quadratic = 0.032f;

	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	
	SetupPostProcessing();

	blur.Activate();

	blur.SetInt("image", 0);

	postProcessing.Activate();

	postProcessing.SetInt("hdrBuffer", 0);
	postProcessing.SetInt("bloomBlur", 1);

	light.Activate();

	light.SetVec3("lightColor", pointLight.diffuse);

	shaders.push_back(shader);
	shaders.push_back(light);
	shaders.push_back(postProcessing);
	shaders.push_back(blur);

	cameras.push_back(camera);

	models.push_back(box);

	pointLights.push_back(pointLight);

	for (int i = 0; i < std::end(boxesModel) - std::begin(boxesModel); i++) 
	{	
		boxesModel[i].model = glm::translate(boxesModel[i].model, boxesModel[i].position);
		boxesModel[i].model = glm::rotate(boxesModel[i].model, glm::radians(boxesModel[i].strengthOfRotation), boxesModel[i].rotation);
		boxesModel[i].model = glm::scale(boxesModel[i].model, boxesModel[i].scale);
	}
}

void Example::Render(GLFWwindow* window, float deltaTime)
{
	glBindFramebuffer(GL_FRAMEBUFFER, HDR);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cameras[0].HandleEvents(window, deltaTime);
		cameras[0].Update();

		shaders[0].Activate();

		shaders[0].SetFloat("material.shininess", 64.0f);

		shaders[0].SetVec3("directionalLight.direction", 0.0f, 0.0f, 0.0f);
		shaders[0].SetVec3("directionalLight.ambient", 0.0f, 0.0f, 0.0f);
		shaders[0].SetVec3("directionalLight.diffuse", 0.0f, 0.0f, 0.0f);
		shaders[0].SetVec3("directionalLight.specular", 0.0f, 0.0f, 0.0f);

		shaders[0].SetVec3("pointLight[0].position", pointLights[0].position);
		shaders[0].SetVec3("pointLight[0].ambient", pointLights[0].ambient);
		shaders[0].SetVec3("pointLight[0].diffuse", pointLights[0].diffuse);
		shaders[0].SetVec3("pointLight[0].specular", pointLights[0].specular);
		shaders[0].SetFloat("pointLight[0].constant", gammaCorrection ? 2 * pointLights[0].constant : pointLights[0].constant);
		shaders[0].SetFloat("pointLight[0].linear", gammaCorrection ? 2 * pointLights[0].linear : pointLights[0].linear);
		shaders[0].SetFloat("pointLight[0].quadratic", gammaCorrection ? 2 * pointLights[0].quadratic : pointLights[0].quadratic);

		shaders[0].SetInt("spotLight.on", flashlight);
		shaders[0].SetVec3("spotLight.position", cameras[0].position);
		shaders[0].SetVec3("spotLight.direction", cameras[0].front);
		shaders[0].SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		shaders[0].SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
		shaders[0].SetVec3("spotLight.ambient", flashlightObject.ambient);
		shaders[0].SetVec3("spotLight.diffuse", flashlightObject.diffuse);
		shaders[0].SetVec3("spotLight.specular", flashlightObject.specular);
		shaders[0].SetFloat("spotLight.constant", gammaCorrection ? 2 * flashlightObject.constant : flashlightObject.constant);
		shaders[0].SetFloat("spotLight.linear", gammaCorrection ? 2 * flashlightObject.linear : flashlightObject.linear);
		shaders[0].SetFloat("spotLight.quadratic", gammaCorrection ? 2 * flashlightObject.quadratic : flashlightObject.quadratic);

		shaders[0].SetVec3("viewPosition", cameras[0].position);

		for (int i = 0; i < std::end(boxesModel) - std::begin(boxesModel); i++)
		{
			boxesModel[i].model = glm::rotate(boxesModel[i].model, glm::radians(0.05f), glm::vec3(0.0f, 1.0f, 0.0f));

			shaders[0].SetMat4("model", boxesModel[i].model);
			shaders[0].SetMat4("view", cameras[0].view);
			shaders[0].SetMat4("projection", projection);

			models[0].Draw(shaders[0], gammaCorrection);
		}

		shaders[1].Activate();
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, pointLights[0].position);

		glm::mat4 mvp = projection * cameras[0].view * model;

		shaders[1].SetMat4("mvp", mvp);

		models[0].Draw(shaders[1], gammaCorrection);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	bool horizontal = true, firstIteration= true;
	unsigned int amount = 10;

	shaders[3].Activate();

	glActiveTexture(GL_TEXTURE0);
	for (GLuint i = 0; i < amount; i++) 
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
		shaders[3].SetInt("horizontal", horizontal);
		glBindTexture(GL_TEXTURE_2D, firstIteration ? colorBuffers[1] : pingpongColorBuffers[!horizontal]);
		RenderQuadFullScreen();
		horizontal = !horizontal;
		if (firstIteration) firstIteration = false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaders[2].Activate();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, pingpongColorBuffers[!horizontal]);
	shaders[2].SetInt("hdr", hdr);
	shaders[2].SetInt("gammaCorrection", gammaCorrection);
	shaders[2].SetInt("bloom", bloom);
	RenderQuadFullScreen();
}
