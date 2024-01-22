#include "Bone.h"

Bone::Bone(std::string Name, int id, const aiNodeAnim* channel)
	: name(Name), ID(id), localTransformation(1.0f)
{
	numberOfPositions = channel->mNumPositionKeys;

	for (int i = 0; i < numberOfPositions; ++i)
	{
		aiVector3D aiPosition = channel->mPositionKeys[i].mValue;
		float timeStamp = channel->mPositionKeys[i].mTime;
		KeyPosition data;
		data.position.x = aiPosition.x;
		data.position.y = aiPosition.y;
		data.position.z = aiPosition.z;
		data.timeStamp = timeStamp;
		positions.push_back(data);
	}

	numberOfRotations = channel->mNumRotationKeys;

	for (int i = 0; i < numberOfRotations; ++i)
	{
		aiQuaternion aiOrientation = channel->mRotationKeys[i].mValue;
		float timeStamp = channel->mRotationKeys[i].mTime;
		KeyRotation data;
		data.orientation.w = aiOrientation.w;
		data.orientation.x = aiOrientation.x;
		data.orientation.y = aiOrientation.y;
		data.orientation.z = aiOrientation.z;
		data.timeStamp = timeStamp;
		rotations.push_back(data);
	}

	numberOfScales = channel->mNumScalingKeys;

	for (int i = 0; i < numberOfScales; ++i) 
	{
		aiVector3D aiPosition = channel->mScalingKeys[i].mValue;
		float timeStamp = channel->mScalingKeys[i].mTime;
		KeyScale data;
		data.scale.x = aiPosition.x;
		data.scale.y = aiPosition.y;
		data.scale.z = aiPosition.z;
		data.timeStamp = timeStamp;
		scales.push_back(data);
	}
}

void Bone::Update(float animationTime)
{
	glm::mat4 translation = InterpolatePosition(animationTime);
	glm::mat4 rotation = InterpolateRotation(animationTime);
	glm::mat4 scale = InterpolateScale(animationTime);
	localTransformation = translation * rotation * scale;
}

float Bone::getScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime)
{
	float scaleFactor = 0.0f;
	float midWayLength = animationTime - lastTimeStamp;
	float frameDiffrence = nextTimeStamp - lastTimeStamp;
	scaleFactor = midWayLength / frameDiffrence;
	return scaleFactor;
}

unsigned int Bone::getPositionIndex(float animationTime)
{
	for (int i = 0; i < numberOfPositions - 1; ++i)
	{
		if (animationTime < positions[i + 1].timeStamp) return i;
	}
}

unsigned int Bone::getRotationIndex(float animationTime)
{
	for (int i = 0; i < numberOfRotations - 1; ++i) 
	{
		if (animationTime < rotations[i + 1].timeStamp) return i;
	}
	
}

unsigned int Bone::getScaleIndex(float animationTime)
{
	for (int i = 0; i < numberOfScales - 1; ++i) 
	{
		if (animationTime < scales[i + 1].timeStamp) return i;
	}
}

glm::mat4 Bone::InterpolatePosition(float animationTime)
{
	if (numberOfPositions == 1) return glm::translate(glm::mat4(1.0f), positions[0].position);
	int startingPositionIndex = getPositionIndex(animationTime);
	int endingPositionIndex = startingPositionIndex + 1;
	float scaleFactor = getScaleFactor(positions[startingPositionIndex].timeStamp, positions[endingPositionIndex].timeStamp, animationTime);
	glm::vec3 finalPosition = glm::mix(positions[startingPositionIndex].position, positions[endingPositionIndex].position, scaleFactor);
	return glm::translate(glm::mat4(1.0f), finalPosition);
}

glm::mat4 Bone::InterpolateRotation(float animationTime)
{
	if (numberOfRotations == 1) 
	{
		glm::quat rotation = glm::normalize(rotations[0].orientation);
		return glm::toMat4(rotation);
	}
	int startingRotationIndex = getRotationIndex(animationTime);
	int endingRotationIndex = startingRotationIndex + 1;
	float scaleFactor = getScaleFactor(rotations[startingRotationIndex].timeStamp, rotations[endingRotationIndex].timeStamp, animationTime);
	glm::quat finalRotation = glm::normalize(glm::slerp(rotations[startingRotationIndex].orientation, rotations[endingRotationIndex].orientation, scaleFactor));
	return glm::toMat4(finalRotation);
}

glm::mat4 Bone::InterpolateScale(float animationTime)
{
	if (numberOfScales == 1) return glm::scale(glm::mat4(1.0f), scales[0].scale);
	int startingScaleIndex = getScaleIndex(animationTime);
	int endingScaleIndex = startingScaleIndex + 1;
	float scaleFactor = getScaleFactor(scales[startingScaleIndex].timeStamp, scales[endingScaleIndex].timeStamp, animationTime);
	glm::vec3 finalScale = glm::mix(scales[startingScaleIndex].scale, scales[endingScaleIndex].scale, scaleFactor);
	return glm::scale(glm::mat4(1.0f), finalScale);
}
