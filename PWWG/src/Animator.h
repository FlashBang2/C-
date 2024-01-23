#ifndef ANIMATOR_H
#define ANIMATOR_H

#include"Animation.h"

class Animator
{
	public:
		std::vector<glm::mat4> finalBoneMatrices;
		
		Animator() {};
		Animator(Animation Animation);
		void UpdateAnimation(float deltaTime);
		void CalculateFinalBoneMatrices(const AssimpNodeData* node, glm::mat4 parentMatrice);
		void PlayAnimation(Animation Animation);
	private:
		Animation animation;
		float currentTime;
};

#endif
