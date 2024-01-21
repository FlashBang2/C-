#include "AdvanceExample.h"

AdvanceExample::AdvanceExample()
{
	Shader AnimatedMesh("Shaders/AnimatedMesh.vert", "Shaders/AnimatedMesh.frag");
	Shader Light("Shaders/Light.vert", "Shaders/Light.frag");

	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));

	Model bee("Models/Bee/bee.fbx");
	Model tree("Models/Tree/tree.fbx");
	Model ground("Models/Ground/ground.fbx");
	Model hive("Models/Hive/hive.fbx");
	Model flower("Models/Flower/flower.fbx");

	Animation animation("Models/Bee/bee.fbx", &bee);

	Animator animator(animation);

	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	animators.push_back(animator);

	shaders.push_back(AnimatedMesh);
	shaders.push_back(Light);

	cameras.push_back(camera);

	models.push_back(bee);
	models.push_back(tree);
	models.push_back(ground);
	models.push_back(hive);
	models.push_back(flower);
}

void AdvanceExample::Render(GLFWwindow* window, float deltaTime)
{
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

	models[0].Draw(shaders[0]);

	shaders[1].Activate();

	mvp = projection * cameras[0].view * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));

	shaders[1].SetMat4("mvp", mvp);

	models[1].Draw(shaders[1]);

	mvp = projection * cameras[0].view * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f));

	shaders[1].SetMat4("mvp", mvp);

	models[2].Draw(shaders[1]);

	mvp = projection * cameras[0].view * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 30.0f, 0.0f));

	shaders[1].SetMat4("mvp", mvp);

	models[3].Draw(shaders[1]);

	mvp = projection * cameras[0].view * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 3.0f));

	shaders[1].SetMat4("mvp", mvp);

	models[4].Draw(shaders[1]);
}
