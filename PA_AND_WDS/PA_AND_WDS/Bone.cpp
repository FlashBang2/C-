#include "Bone.h"

Bone::Bone(const std::string& name, int ID, const aiNodeAnim* channel) 
	:name(name), ID(ID) {
	for (unsigned int i = 0; i < channel->mNumPositionKeys;++i) {
		KeyPosition data;
		data.position = glm::vec3(channel->mPositionKeys[i].mValue.x, channel->mPositionKeys[i].mValue.y, channel->mPositionKeys[i].mValue.z);
		data.timeStamp = channel->mPositionKeys[i].mTime;
		Positions.push_back(data);
	}
	for (unsigned int i = 0; i < channel->mNumRotationKeys;++i) {
		KeyRotation data;
		data.orientation = glm::quat(channel->mRotationKeys[i].mValue.w, channel->mRotationKeys[i].mValue.x, channel->mRotationKeys[i].mValue.y, channel->mRotationKeys[i].mValue.z);
		data.timeStamp = channel->mPositionKeys[i].mTime;
		Rotations.push_back(data);
	}
	for (unsigned int i = 0; i < channel->mNumScalingKeys;++i) {
		KeyScale data;
		data.scale = glm::vec3(channel->mScalingKeys[i].mValue.x, channel->mScalingKeys[i].mValue.y, channel->mScalingKeys[i].mValue.z);
		data.timeStamp = channel->mScalingKeys[i].mTime;
		Scales.push_back(data);
	}


}

void Bone::Update(float animationTime) {
	glm::mat4 translation = InterpolatePosition(animationTime);
	glm::mat4 rotation = InterpolateRotation(animationTime);
	glm::mat4 scale = InterpolateScale(animationTime);
	LocalSpace = translation * rotation * scale;
}

int Bone::GetPositionIndex(float animationTime) {
	for (unsigned int i = 0; i < Positions.size() - 1;++i) {
		if (animationTime < Positions[i + 1].timeStamp) return i;
	}
	assert(0);
}

int Bone::GetRotationIndex(float animationTime) {
	for (unsigned int i = 0; i < Rotations.size() - 1;++i) {
		if (animationTime < Rotations[i + 1].timeStamp) return i;
	}
	assert(0);
}

int Bone::GetScaleIndex(float animationTime) {
	for (unsigned int i = 0; i < Scales.size() - 1;++i) {
		if (animationTime < Scales[i + 1].timeStamp) return i;
	}
	assert(0);
}

float Bone::GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime) {
	float scaleFactor = 0.0f;
	float midPoint = animationTime - lastTimeStamp;
	float timeDiffrence = nextTimeStamp - lastTimeStamp;
	scaleFactor = midPoint / timeDiffrence;
	return scaleFactor;
}

glm::mat4 Bone::InterpolatePosition(float animationTime) {
	if (1 == Positions.size()) {
		return glm::translate(glm::mat4(1.0f), Positions[0].position);
	}
	int index = GetPositionIndex(animationTime);
	float scaleFactor = GetScaleFactor(Positions[index].timeStamp,
		Positions[index + 1].timeStamp, animationTime);
	glm::vec3 calculatedPosition = glm::mix(Positions[index].position, Positions[index + 1].position, scaleFactor);;
	return glm::translate(glm::mat4(1.0f), calculatedPosition);
}

glm::mat4 Bone::InterpolateRotation(float animationTime)
{
	if (1 == Rotations.size()) {
		auto rotation = glm::normalize(Rotations[0].orientation);
		return glm::toMat4(rotation);
	}
	int index = GetRotationIndex(animationTime);
	float scaleFactor = GetScaleFactor(Rotations[index].timeStamp, Rotations[index + 1].timeStamp, animationTime);
	glm::quat calculatedRotation = glm::slerp(Rotations[index].orientation, Rotations[index + 1].orientation, scaleFactor);
	return glm::toMat4(calculatedRotation);
}

glm::mat4 Bone::InterpolateScale(float animationTime)
{
	if (1 == Scales.size()) {
		return glm::scale(glm::mat4(1.0f), Scales[0].scale);
	}
	int index = GetScaleIndex(animationTime);
	float scaleFactor = GetScaleFactor(Scales[index].timeStamp, Scales[index + 1].timeStamp, animationTime);
	glm::vec3 calculatedSize = glm::mix(Scales[index].scale, Scales[index + 1].scale, scaleFactor);
	return glm::scale(glm::mat4(1.0f), calculatedSize);
}
