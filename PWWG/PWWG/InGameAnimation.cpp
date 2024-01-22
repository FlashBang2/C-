#include "InGameAnimation.h"

InGameAnimation::InGameAnimation(float Duration, unsigned int TicksPerSecond, std::vector<KeyPositionInGame> Positions, std::vector<KeyRotationInGame> Rotations, std::vector<KeyScaleInGame> Scales)
	:ticksPerSecond(TicksPerSecond), duration(Duration), positions{ Positions }, rotations{ Rotations }, scales{Scales}, currentTime(0.0f) {}

glm::mat4 InGameAnimation::UpdateAnimation(float deltaTime)
{
	currentTime += ticksPerSecond * deltaTime;
	animationTimePlaying += ticksPerSecond * deltaTime;
	if (animationTimePlaying > duration) endAnimation = true;
	currentTime = fmod(currentTime, duration);
	glm::mat4 translate = InterpolatePosition(currentTime);
	glm::mat4 rotation = InterpolateRotation(currentTime);
	glm::mat4 scale = InterpolateScale(currentTime);
	return translate * rotation * scale;
}

float InGameAnimation::getScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime)
{
	float scaleFactor = 0.0f;
	float midWayLength = animationTime - lastTimeStamp;
	float frameDiffrence = nextTimeStamp - lastTimeStamp;
	scaleFactor = midWayLength / frameDiffrence;
	return scaleFactor;
}

unsigned int InGameAnimation::getPositionIndex(float animationTime)
{
	for (int i = 0; i < positions.size() - 1; ++i)
	{
		if (animationTime < positions[i + 1].timeStamp) return i;
	}
}

unsigned int InGameAnimation::getRotationIndex(float animationTime)
{
	for (int i = 0; i < rotations.size() - 1; ++i)
	{
		if (animationTime < rotations[i + 1].timeStamp) return i;
	}
}

unsigned int InGameAnimation::getScaleIndex(float animationTime)
{
	for (int i = 0; i < scales.size() - 1; ++i)
	{
		if (animationTime < scales[i + 1].timeStamp) return i;
	}
}

glm::mat4 InGameAnimation::InterpolatePosition(float animationTime)
{
	if (positions.size() == 1) return glm::translate(glm::mat4(1.0f), positions[0].position);
	int startingPositionIndex = getPositionIndex(animationTime);
	int endingPositionIndex = startingPositionIndex + 1;
	float scaleFactor = getScaleFactor(positions[startingPositionIndex].timeStamp, positions[endingPositionIndex].timeStamp, animationTime);
	glm::vec3 finalPosition = glm::mix(positions[startingPositionIndex].position, positions[endingPositionIndex].position, scaleFactor);
	return glm::translate(glm::mat4(1.0f), finalPosition);
}

glm::mat4 InGameAnimation::InterpolateRotation(float animationTime)
{
	if (rotations.size() == 1)
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

glm::mat4 InGameAnimation::InterpolateScale(float animationTime)
{
	if (scales.size() == 1) return glm::scale(glm::mat4(1.0f), scales[0].scale);
	int startingScaleIndex = getScaleIndex(animationTime);
	int endingScaleIndex = startingScaleIndex + 1;
	float scaleFactor = getScaleFactor(scales[startingScaleIndex].timeStamp, scales[endingScaleIndex].timeStamp, animationTime);
	glm::vec3 finalScale = glm::mix(scales[startingScaleIndex].scale, scales[endingScaleIndex].scale, scaleFactor);
	return glm::scale(glm::mat4(1.0f), finalScale);
}
