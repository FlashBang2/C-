#include "Animation.h"

Animation::Animation(const std::string& animationPath, Model* model) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);
	assert(scene && scene->mRootNode);
	auto animation = scene->mAnimations[0];
	Duration = animation->mDuration;
	TicksPerSecond = animation->mTicksPerSecond;
	ReadHierarchyData(RootNode, scene->mRootNode);
	ReadMissingBones(animation, *model);
}

Bone* Animation::FindBone(const std::string& name) {
	auto Iterates = std::find_if(Bones.begin(), Bones.end(), [&](const Bone& Bone) {
		return Bone.GetBoneName() == name;
		}
	);
	if (Iterates == Bones.end()) return nullptr;
	else return &(*Iterates);
}

void Animation::ReadMissingBones(const aiAnimation* animation, Model& model) {

	auto& boneInfoMap = model.GetBoneInfoMap();
	int& boneCount = model.GetBoneCount();

	for (unsigned int i = 0; i < animation->mNumChannels;i++) {
		auto channel = animation->mChannels[i];
		std::string boneName = channel->mNodeName.data;
		if (boneInfoMap.find(boneName) == boneInfoMap.end()) {
			boneInfoMap[boneName].ID = boneCount;
			boneCount++;
		}
		Bones.push_back(Bone(channel->mNodeName.data, boneInfoMap[channel->mNodeName.data].ID, channel));
	}

	BoneInfoMap = boneInfoMap;
}

void Animation::ReadHierarchyData(AssimpNodeData& destination, const aiNode* src) {
	assert(src);
	destination.name = src->mName.data;
	destination.transformation = glm::mat4(src->mTransformation.a1, src->mTransformation.b1, src->mTransformation.c1, src->mTransformation.d1,
										   src->mTransformation.a2, src->mTransformation.b2, src->mTransformation.c2, src->mTransformation.d2,
										   src->mTransformation.a3, src->mTransformation.b3, src->mTransformation.c3, src->mTransformation.d3,
										   src->mTransformation.a4, src->mTransformation.b4, src->mTransformation.c4, src->mTransformation.d4);
	destination.childrenCount = src->mNumChildren;

	for (unsigned int i = 0; i < src->mNumChildren;i++) {
		AssimpNodeData Data;
		ReadHierarchyData(Data, src->mChildren[i]);
		destination.children.push_back(Data);
	}
}
