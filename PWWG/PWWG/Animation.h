#ifndef ANIMATION_H
#define ANIMATION_H

#include"Model.h"
#include"Bone.h"

struct AssimpNodeData 
{
	glm::mat4 transformation;
	std::string name;
	int childrenCount;
	std::vector<AssimpNodeData> children;
};

class Animation
{
	public:
		std::map<std::string, BoneInfo> boneInfo;
		AssimpNodeData rootNode;
		float duration;
		float ticksPerSecond;

		Animation() {};
		Animation(std::string animationPath, Model* model);
		Bone* FindBone(std::string name);
	private:
		std::vector<Bone> bones;

		void ReadHierarchy(AssimpNodeData& destination, const aiNode* source);
		void ReadMissingBones(aiAnimation* animation, Model& model);
};

#endif

