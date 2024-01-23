#include "AdvanceExample.h"

AdvanceExample::AdvanceExample()
	:flowersModel{{glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(-5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(3.0f, 0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(4.0f, 0.0f, 6.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(17.0f, 0.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(12.0f, 0.0f, 8.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(9.0f, 0.0f, 14.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(-8.0f, 0.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(-10.0f, 0.0f, -7.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(-11.0f, 0.0f, -13.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(-5.0f, 0.0f, 13.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(0.0f, 0.0f, 18.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(2.0f, 0.0f, -19.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(6.0f, 0.0f, -21.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(-9.0f, 0.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(18.0f, 0.0f, 14.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(-10.0f, 0.0f, 11.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(-17.0f, 0.0f, 13.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(-17.0f, 0.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(-13.0f, 0.0f, 20.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(14.0f, 0.0f, -7.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(16.0f, 0.0f, -11.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(12.0f, 0.0f, -19.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(-18.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(-10.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(-2.7f, 0.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(-10.0f, 0.0f, 6.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(-6.0f, 0.0f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(12.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(14.0f, 0.0f, -13.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(7.0f, 0.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(12.0f, 0.0f, -4.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(19.0f, 0.0f, -7.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(-5.0f, 0.0f, -13.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(7.0f, 0.0f, -18.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(15.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(-8.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(-18.0f, 0.0f, -4.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(1.5f, 0.0f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(-8.0f, 0.0f, -21.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(5.0f, 0.0f, -9.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f),  0.0f, glm::vec3(5.5f, 0.0f, -13.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, -13.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(-3.3f, 0.0f, -22.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(6.0f, 0.0f, 18.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(23.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(-22.0f, 0.0f, 1.2f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				  {glm::mat4(1.0f), 0.0f, glm::vec3(-2.4f, 0.0f, -19.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)}},
	beesModel{ {glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(-2.9f, 4.0f, -9.7f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.09f, 0.09f, 0.09f)}},
	pathToFlowersAnimationDistribution(0, std::end(selectedFlowersModel) - std::begin(selectedFlowersModel) - 1),
	generator(std::random_device{}()),
	hives{{glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(-2.5f, 4.15f, -10.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)}},
	diffuse(2.0f, 2.0f, 2.0f)
{
	Shader animatedMesh("../src/Shaders/AnimatedMesh.vert", "../src/Shaders/AnimatedMesh.frag");
	Shader mesh("../src/Shaders/Mesh.vert", "../src/Shaders/Mesh.frag");
	Shader light("../src/Shaders/Light.vert", "../src/Shaders/Light.frag");
	Shader postProcessing("../src/Shaders/PostProcessing.vert", "../src/Shaders/PostProcessing.frag");
	Shader blur("../src/Shaders/Blur.vert", "../src/Shaders/Blur.frag");

	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));

	Model bee("../src/Models/Bee/bee.fbx");
	Model tree("../src/Models/Tree/tree.fbx");
	Model ground("../src/Models/Ground/ground.fbx");
	Model hive("../src/Models/Hive/hive.fbx");
	Model flower("../src/Models/Flower/flower.fbx");
	Model sunAndMoon("../src/Models/SunAndMoon/sunAndMoon.fbx");

	Animation animation("../src/Models/Bee/bee.fbx", &bee);

	Animator animator(animation);

	PointLight pointLight
	{
		glm::vec3 (0.0f, -30.0f, 0.0f),
		glm::vec3 (0.0f, 0.0f, 0.0f),
		glm::vec3 (0.0f, 0.0f, 0.0f),
		glm::vec3 (0.0f, 0.0f, 0.0f),
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
	models.push_back(sunAndMoon);

	pointLights.push_back(pointLight);

	std::uniform_int_distribution<std::size_t> distribution(0, std::end(flowersModel) - std::begin(flowersModel) - 1);

	for (std::size_t i = 0; i < std::end(flowersModel) - std::begin(flowersModel); i++)
	{
		std::size_t value = distribution(generator);
		if (std::find(std::begin(selectedFlowersModel), std::end(selectedFlowersModel), value) != std::end(selectedFlowersModel)) 
		{
			--i;
			continue;
		}
		selectedFlowersModel[i] = value;
		flowersModel[value].model = glm::translate(flowersModel[value].model, flowersModel[value].position);
		flowersModel[value].model = glm::rotate(flowersModel[value].model, flowersModel[value].strengthOfRotation, flowersModel[value].rotation);
		flowersModel[value].model = glm::scale(flowersModel[value].model, flowersModel[value].scale);
	}

	animationIndex = pathToFlowersAnimationDistribution(generator);

	std::vector<KeyPositionInGame> positions;
	std::vector<KeyRotationInGame> rotations;
	std::vector<KeyScaleInGame> scales;

	for (int i = 0; i < std::end(pathToFlowers) - std::begin(pathToFlowers); i++)
	{
		positions = {};
		rotations = {};
		scales = {};

	positions.push_back({ glm::vec3(beesModel[0].position), 0.0f});
	positions.push_back({ glm::vec3(flowersModel[i].position.x, 4.05f, flowersModel[i].position.z), 20.0f});
	positions.push_back({ glm::vec3(flowersModel[i].position.x, 4.05f, flowersModel[i].position.z), 40.0f });
	positions.push_back({ glm::vec3(beesModel[0].position), 60.0f });
	positions.push_back({ glm::vec3(beesModel[0].position), 80.0f });
	rotations.push_back({glm::angleAxis(glm::radians(beesModel[0].strengthOfRotation), glm::vec3(0.0f, 1.0f, 0.0f)), 0.0f});
	rotations.push_back({ glm::angleAxis(glm::radians(beesModel[0].strengthOfRotation), glm::vec3(0.0f, 1.0f, 0.0f)), 20.0f });
	rotations.push_back({ glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)), 40.0f });
	rotations.push_back({ glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)), 60.0f });
	rotations.push_back({ glm::angleAxis(glm::radians(beesModel[0].strengthOfRotation), glm::vec3(0.0f, 1.0f, 0.0f)), 80.0f });
	scales.push_back({ beesModel[0].scale, 0.0f });

	pathToFlowers[i] = new InGameAnimation(80.0f, 5, positions, rotations, scales);
	}

	positions = { {glm::vec3(0.0f, 5.0f, 0.0f), 0.0f}};
	rotations = { {glm::angleAxis(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)), 0.0f},
				  {glm::angleAxis(glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)), 200.0f},
				  {glm::angleAxis(glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f)), 400.0f}};
	scales = { {glm::vec3(1.0f, 1.0f, 1.0f)}};

	SunAndMoon = new InGameAnimation(400.0f, 30, positions, rotations, scales);

	for (int i = 0; i < std::end(beesModel) - std::begin(beesModel); i++) 
	{
		beesModel[i].model = glm::translate(beesModel[i].model, beesModel[i].position);
		beesModel[i].model = glm::rotate(beesModel[i].model, beesModel[i].strengthOfRotation, beesModel[i].rotation);
		beesModel[i].model = glm::scale(beesModel[i].model, beesModel[i].scale);
	}

	for (int i = 0; i < std::end(hives) - std::begin(hives); i++) 
	{
		hives[i].model = glm::translate(hives[i].model, hives[i].position);
		hives[i].model = glm::rotate(hives[i].model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		hives[i].model = glm::rotate(hives[i].model, hives[i].strengthOfRotation, hives[i].rotation);
		hives[i].model = glm::scale(hives[i].model, hives[i].scale);
	}
}

void AdvanceExample::Render(GLFWwindow* window, float deltaTime)
{
	counter++;
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

		if (pathToFlowers[selectedFlowersModel[animationIndex]]->endAnimation)
		{
			pathToFlowers[animationIndex]->endAnimation = false;
			pathToFlowers[animationIndex]->currentTime = 0.0f;
			animationIndex = pathToFlowersAnimationDistribution(generator);
		}

		glm::mat4 model = pathToFlowers[selectedFlowersModel[animationIndex]]->UpdateAnimation(deltaTime);

		glm::mat4 mvp = projection * cameras[0].view * model;

		shaders[0].SetMat4("mvp", mvp);

		models[0].Draw(shaders[0], gammaCorrection);

		shaders[1].Activate();

		shaders[1].SetFloat("material.shininess", 64.0f);

		if (counter < 800) 
		{
			diffuse.x -= 0.01f;
			diffuse.y -= 0.01f;
			diffuse.z -= 0.01f;
		}
		if (counter > 800 && counter < 1600) 
		{
			diffuse.x += 0.01f;
			diffuse.y += 0.01f;
			diffuse.z += 0.01f;
		}
		if (counter > 1600) 
		{
			counter = 0;
		}

		shaders[1].SetVec3("directionalLight.direction", -0.2f, -1.0f, -0.3f);
		shaders[1].SetVec3("directionalLight.ambient", 0.1f, 0.1f, 0.1f);
		shaders[1].SetVec3("directionalLight.diffuse", diffuse);
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

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));

		shaders[1].SetMat4("model", model);
		shaders[1].SetMat4("view", cameras[0].view);
		shaders[1].SetMat4("projection", projection);

		models[1].Draw(shaders[1], gammaCorrection);

		shaders[1].SetFloat("material.shininess", 12.0f);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.001f, 0.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));

		shaders[1].SetMat4("model", model);

		models[2].Draw(shaders[1], gammaCorrection);

		shaders[1].SetFloat("material.shininess", 8.0f);

		shaders[1].SetMat4("model", hives[0].model);

		models[3].Draw(shaders[1], gammaCorrection);

		shaders[1].SetFloat("material.shininess", 60.0f);

		for (int i = 0; i < std::end(selectedFlowersModel) - std::begin(selectedFlowersModel); i++)
		{
			model = flowersModel[selectedFlowersModel[i]].model;

			shaders[1].SetMat4("model", model);

			models[4].Draw(shaders[1], gammaCorrection);
		}

		model = SunAndMoon->UpdateAnimation(deltaTime);

		shaders[1].SetMat4("model", model);

		models[5].Draw(shaders[1], gammaCorrection);

		shaders[2].Activate();

		model = glm::mat4(1.0f);

		model = glm::translate(model, pointLights[0].position);

		mvp = projection * cameras[0].view * model;

		models[4].Draw(shaders[2], gammaCorrection);

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

glm::vec3 AdvanceExample::InterpolateColor(float deltaTime, unsigned int ticksPerSecond, float duration)
{
	currentColorAnimationTime += ticksPerSecond * deltaTime;
	currentColorAnimationTime = fmod(currentColorAnimationTime, duration);

	return glm::vec3();
}