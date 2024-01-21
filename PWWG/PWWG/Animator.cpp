#include "Animator.h"

Animator::Animator(Animation* Animation)
	:currentTime(0.0f), animation(Animation)
{
	for (int i = 0; i < 100; i++) 
	{
		finalBoneMatrices.push_back(glm::mat4(1.0f));
	}
}

void Animator::UpdateAnimation(float deltaTime)
{
	if (animation) 
	{
		currentTime += animation->ticksPerSecond * deltaTime;
		currentTime = fmod(currentTime, animation->duration);
		CalculateFinalBoneMatrices(&animation->rootNode, glm::mat4(1.0f));
	}
}

void Animator::CalculateFinalBoneMatrices(const AssimpNodeData* node, glm::mat4 parentMatrice)
{
	std::string nodeName = node->name;
	glm::mat4 nodeTransform = node->transformation;

	Bone* Bone = animation->FindBone(nodeName);

	if (Bone) 
	{
		Bone->Update(currentTime);
		nodeTransform = Bone->localTransformation;
	}

	glm::mat4 globalTransformation = parentMatrice * nodeTransform;

	std::map<std::string, BoneInfo> boneInfoMap = animation->boneInfo;

	if (boneInfoMap.find(nodeName) != boneInfoMap.end()) 
	{
		int ID = boneInfoMap[nodeName].ID;
		glm::mat4 offset = boneInfoMap[nodeName].offset;
		finalBoneMatrices[ID] = globalTransformation * offset;
	}

	for (int i = 0; i < node->childrenCount; i++)
		CalculateFinalBoneMatrices(&node->children[i], globalTransformation);
}

void Animator::PlayAnimation(Animation* Animation)
{
	animation = Animation;
	currentTime = 0.0f;
}
