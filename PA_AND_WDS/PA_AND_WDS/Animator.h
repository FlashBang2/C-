#ifndef ANIMATOR_CLASS_H
#define ANIMATOR_CLASS_H

#include "Animation.h"

class Animator {
public:
	Animator(Animation* animation);
	void UpdateAnimation(float deltaTime);
	void CalculateBoneMatrix(const AssimpNodeData* animation, glm::mat4 parentTransform);
	void PlayAnimation(Animation* Animation);
	std::vector<glm::mat4> GetCalculatedBoneMatrix() { return CalculatedBoneMatrix; }
protected:
private:
	std::vector<glm::mat4> CalculatedBoneMatrix;
	Animation* animation;
	float CurrentTime, DeltaTime;
};
#endif
