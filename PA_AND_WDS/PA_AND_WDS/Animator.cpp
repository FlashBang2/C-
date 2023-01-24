#include "Animator.h"

Animator::Animator(Animation* animation)
	:animation(animation), DeltaTime(0.0f) {
	CurrentTime = 0.0f;

	for (unsigned int i = 0; i < 100;i++) {
		CalculatedBoneMatrix.push_back(glm::mat4(1.0f));
	}
}

void Animator::UpdateAnimation(float deltaTime) {
	DeltaTime = deltaTime;
	if (animation) {
		CurrentTime += animation->GetTicksPerSecond() * DeltaTime;
		CurrentTime = std::fmod(CurrentTime, animation->GetDuration());
		CalculateBoneMatrix(&animation->GetRootNode(), glm::mat4(1.0f));
	}
}

void Animator::CalculateBoneMatrix(const AssimpNodeData* node, glm::mat4 parentTransform) {
	glm::mat4 currentTransformation = node->transformation;

	Bone* Bone = animation->FindBone(node->name);

	if (Bone) {
		Bone->Update(CurrentTime);
		currentTransformation = Bone->GetLocalTransform();
	}

	glm::mat4 globalTransformation = parentTransform * currentTransformation;

	auto boneInfoMap = animation->GetBoneIDMap();
	if (boneInfoMap.find(node->name) != boneInfoMap.end()) {
		int index = boneInfoMap[node->name].ID;
		glm::mat4 offset = boneInfoMap[node->name].offset;
		CalculatedBoneMatrix[index] = globalTransformation * offset;
	}

	for (unsigned int i = 0; i < node->childrenCount ;i++) {
		CalculateBoneMatrix(&node->children[i], globalTransformation);
	}
}

void Animator::PlayAnimation(Animation* Animation) {
	animation = Animation;
	CurrentTime = 0.0f;
}
