#include "Animation.h"

Animation::Animation(std::string animationPath, Model* model)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);
	aiAnimation* animation = scene->mAnimations[0];
	duration = animation->mDuration;
	ticksPerSecond = animation->mTicksPerSecond;
	aiMatrix4x4 globalTransformation = scene->mRootNode->mTransformation;
	globalTransformation = globalTransformation.Inverse();
	ReadHierarchy(rootNode, scene->mRootNode);
	ReadMissingBones(animation, *model);
}

Bone* Animation::FindBone(std::string name)
{
	std::vector<Bone>::iterator iterator = std::find_if(bones.begin(), bones.end(), [&](const Bone& Bone)
		{
			return Bone.name == name;
		}
	);
	if (iterator == bones.end()) return nullptr;
	else return &(*iterator);
}

void Animation::ReadHierarchy(AssimpNodeData& destination, const aiNode* source)
{
	destination.name = source->mName.data;
	destination.transformation = glm::mat4(source->mTransformation.a1, source->mTransformation.b1, source->mTransformation.c1, source->mTransformation.d1,
										   source->mTransformation.a2, source->mTransformation.b2, source->mTransformation.c2, source->mTransformation.d2,
										   source->mTransformation.a3, source->mTransformation.b3, source->mTransformation.c3, source->mTransformation.d3,
										   source->mTransformation.a4, source->mTransformation.b4, source->mTransformation.c4, source->mTransformation.d4);
	destination.childrenCount = source->mNumChildren;
	for (int i = 0; i < source->mNumChildren; i++) 
	{
		AssimpNodeData data;
		ReadHierarchy(data, source->mChildren[i]);
		destination.children.push_back(data);
	}
}
void Animation::ReadMissingBones(aiAnimation* animation, Model& model)
{
	int size = animation->mNumChannels;

	for (int i = 0; i < size; i++) 
	{
		aiNodeAnim* channel = animation->mChannels[i];
		std::string boneName = channel->mNodeName.data;

		if (model.bonesInfo.find(boneName) == model.bonesInfo.end())
		{
			model.bonesInfo[boneName].ID = model.currentBone;
			model.currentBone++;
		}
		bones.push_back(Bone(channel->mNodeName.data, model.bonesInfo[channel->mNodeName.data].ID, channel));
	}
	boneInfo = model.bonesInfo;
}

