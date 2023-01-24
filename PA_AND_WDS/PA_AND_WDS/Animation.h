#ifndef ANIMATION_CLASS_H
#define ANIMATION_CLASS_H

#include "model.h"
#include "Bone.h"

struct AssimpNodeData {
	glm::mat4 transformation;
	std::string name;
	int childrenCount;
	std::vector<AssimpNodeData> children;
};

class Animation {
public:
	Animation() = default;
	Animation(const std::string& animationPath, Model* model);
	Bone* FindBone(const std::string& name);
	inline float GetTicksPerSecond() { return TicksPerSecond; }
	inline float GetDuration() { return Duration; }
	inline const AssimpNodeData& GetRootNode() { return RootNode; }
	inline const std::map<std::string, BoneInfo>& GetBoneIDMap() { return BoneInfoMap; }
protected:
private:
	float Duration;
	int TicksPerSecond;
	std::vector<Bone> Bones;
	AssimpNodeData RootNode;
	std::map<std::string, BoneInfo> BoneInfoMap;

	void ReadMissingBones(const aiAnimation* animation, Model& model);
	void ReadHierarchyData(AssimpNodeData& destination, const aiNode* src);
};
#endif

