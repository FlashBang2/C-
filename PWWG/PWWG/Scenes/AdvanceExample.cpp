#include "AdvanceExample.h"

AdvanceExample::AdvanceExample()
{
	Shader AnimatedMesh("Shaders/AnimatedMesh.vert", "Shaders/AnimatedMesh.frag");

	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));

	Model bee("Models/Bee/bee.fbx");

	Animation animation("Models/Bee/bee.fbx", &bee);

	Animator animator(&animation);

	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	animators.push_back(animator);

	shaders.push_back(AnimatedMesh);

	cameras.push_back(camera);

	models.push_back(bee);
}

void AdvanceExample::Render(GLFWwindow* window, float deltaTime)
{
	cameras[0].HandleEvents(window, deltaTime);
	cameras[0].Update();

	shaders[0].Activate();

	for (int i = 0; animators[0].finalBoneMatrices.size(); ++i)
	{
		shaders[0].SetMat4("finalBonesMatrices[" + std::to_string(i) + "]", animators[0].finalBoneMatrices[i]);
	}

	glm::mat4 mvp = glm::mat4(1.0f) * cameras[0].view * projection;

	shaders[0].SetMat4("mvp", mvp);

	models[0].Draw(shaders[0]);
}
