#include "AdvanceExample.h"

AdvanceExample::AdvanceExample()
	:FlowersModel{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}}
{
	Shader animatedMesh("Shaders/AnimatedMesh.vert", "Shaders/AnimatedMesh.frag");
	Shader mesh("Shaders/Mesh.vert", "Shaders/Mesh.frag");
	Shader light("Shaders/Light.vert", "Shaders/Light.frag");
	Shader postProcessing("Shaders/PostProcessing.vert", "Shaders/PostProcessing.frag");
	Shader blur("Shaders/Blur.vert", "Shaders/Blur.frag");

	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));

	Model bee("Models/Bee/bee.fbx");
	Model tree("Models/Tree/tree.fbx");
	Model ground("Models/Ground/ground.fbx");
	Model hive("Models/Hive/hive.fbx");
	Model flower("Models/Flower/flower.fbx");

	Animation animation("Models/Bee/bee.fbx", &bee);

	Animator animator(animation);

	PointLight pointLight
	{
		glm::vec3 (0.0f, 5.0f, 0.0f),
		glm::vec3 (0.0f, 0.0f, 0.0f),
		glm::vec3 (2.0f, 2.0f, 2.0f),
		glm::vec3 (1.0f, 1.0f, 1.0f),
		1.0f,
		0.09f,
		0.032f
	};

	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	SetupPostProcessing();

	blur.Activate();

	blur.SetInt("image", 0);

	postProcessing.Activate();

	postProcessing.SetInt("hdrBuffer", 0);
	postProcessing.SetInt("bloomBlur", 1);

	light.Activate();

	light.SetVec3("lightColor", pointLight.diffuse);

	animators.push_back(animator);

	shaders.push_back(animatedMesh);
	shaders.push_back(mesh);
	shaders.push_back(light);
	shaders.push_back(postProcessing);
	shaders.push_back(blur);

	cameras.push_back(camera);

	models.push_back(bee);
	models.push_back(tree);
	models.push_back(ground);
	models.push_back(hive);
	models.push_back(flower);

	pointLights.push_back(pointLight);
}

void AdvanceExample::Render(GLFWwindow* window, float deltaTime)
{
	glBindFramebuffer(GL_FRAMEBUFFER, HDR);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cameras[0].HandleEvents(window, deltaTime);
		cameras[0].Update();

		shaders[0].Activate();

		animators[0].UpdateAnimation(deltaTime);

		for (int i = 0; i < animators[0].finalBoneMatrices.size(); ++i)
		{
			shaders[0].SetMat4("finalBonesMatrices[" + std::to_string(i) + "]", animators[0].finalBoneMatrices[i]);
		}

		glm::mat4 mvp = projection * cameras[0].view * glm::mat4(1.0f);

		shaders[0].SetMat4("mvp", mvp);

		models[0].Draw(shaders[0], false);

		shaders[1].Activate();

		shaders[1].SetFloat("material.shininess", 64.0f);

		shaders[1].SetVec3("directionalLight.direction", 0.0f, 5.0f, -15.0f);
		shaders[1].SetVec3("directionalLight.ambient", 0.1f, 0.1f, 0.1f);
		shaders[1].SetVec3("directionalLight.diffuse", 0.3f, 0.3f, 0.3f);
		shaders[1].SetVec3("directionalLight.specular", 1.0f, 1.0f, 1.0f);

		shaders[1].SetVec3("pointLight[0].position", pointLights[0].position);
		shaders[1].SetVec3("pointLight[0].ambient", pointLights[0].ambient);
		shaders[1].SetVec3("pointLight[0].diffuse", pointLights[0].diffuse);
		shaders[1].SetVec3("pointLight[0].specular", pointLights[0].specular);
		shaders[1].SetFloat("pointLight[0].constant", gammaCorrection ? 2 * pointLights[0].constant : pointLights[0].constant);
		shaders[1].SetFloat("pointLight[0].linear", gammaCorrection ? 2 * pointLights[0].linear : pointLights[0].linear);
		shaders[1].SetFloat("pointLight[0].quadratic", gammaCorrection ? 2 * pointLights[0].quadratic : pointLights[0].quadratic);

		shaders[1].SetInt("spotLight.on", flashlight);
		shaders[1].SetVec3("spotLight.position", cameras[0].position);
		shaders[1].SetVec3("spotLight.direction", cameras[0].front);
		shaders[1].SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		shaders[1].SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
		shaders[1].SetVec3("spotLight.ambient", flashlightObject.ambient);
		shaders[1].SetVec3("spotLight.diffuse", flashlightObject.diffuse);
		shaders[1].SetVec3("spotLight.specular", flashlightObject.specular);
		shaders[1].SetFloat("spotLight.constant", gammaCorrection ? 2 * flashlightObject.constant : flashlightObject.constant);
		shaders[1].SetFloat("spotLight.linear", gammaCorrection ? 2 * flashlightObject.linear : flashlightObject.linear);
		shaders[1].SetFloat("spotLight.quadratic", gammaCorrection ? 2 * flashlightObject.quadratic : flashlightObject.quadratic);
	
		shaders[1].SetVec3("viewPosition", cameras[0].position);

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));

		shaders[1].SetMat4("model", model);
		shaders[1].SetMat4("view", cameras[0].view);
		shaders[1].SetMat4("projection", projection);

		models[1].Draw(shaders[1], false);

		shaders[1].SetFloat("material.shininess", 12.0f);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f));

		shaders[1].SetMat4("model", model);
		shaders[1].SetMat4("view", cameras[0].view);
		shaders[1].SetMat4("projection", projection);

		models[2].Draw(shaders[1], false);

		shaders[1].SetFloat("material.shininess", 8.0f);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

		shaders[1].SetMat4("model", model);
		shaders[1].SetMat4("view", cameras[0].view);
		shaders[1].SetMat4("projection", projection);

		models[3].Draw(shaders[1], false);

		shaders[1].SetFloat("material.shininess", 60.0f);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 3.0f));
	
		shaders[1].SetMat4("model", model);
		shaders[1].SetMat4("view", cameras[0].view);
		shaders[1].SetMat4("projection", projection);

		models[4].Draw(shaders[1], false);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	bool horizontal = true, firstIteration = true;
	unsigned int amount = 10;

	shaders[4].Activate();

	glActiveTexture(GL_TEXTURE0);
	for (GLuint i = 0; i < amount; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
		shaders[4].SetInt("horizontal", horizontal);
		glBindTexture(GL_TEXTURE_2D, firstIteration ? colorBuffers[1] : pingpongColorBuffers[!horizontal]);
		RenderQuadFullScreen();
		horizontal = !horizontal;
		if (firstIteration) firstIteration = false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaders[3].Activate();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, pingpongColorBuffers[!horizontal]);
	shaders[3].SetInt("hdr", hdr);
	shaders[3].SetInt("gammaCorrection", gammaCorrection);
	shaders[3].SetInt("bloom", bloom);
	RenderQuadFullScreen();
}
