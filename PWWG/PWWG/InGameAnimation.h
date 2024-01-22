#ifndef IN_GAME_ANIMATION_H
#define IN_GAME_ANIMATION_H

#include<vector>
#include<glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

struct KeyPositionInGame
{
	glm::vec3 position;
	float timeStamp;
};

struct KeyRotationInGame
{
	glm::quat orientation;
	float timeStamp;
};

struct KeyScaleInGame
{
	glm::vec3 scale;
	float timeStamp;
};


class InGameAnimation
{
	public:
		InGameAnimation() {};
		InGameAnimation(float Duration, unsigned int TicksPerSecond, std::vector<KeyPositionInGame> Positions, std::vector<KeyRotationInGame> Rotations, std::vector<KeyScaleInGame> Scales);

		glm::mat4 UpdateAnimation(float deltaTime);
	protected:
	private:
		std::vector<KeyPositionInGame> positions;
		std::vector<KeyRotationInGame> rotations;
		std::vector<KeyScaleInGame> scales;
		unsigned int ticksPerSecond;
		float duration, currentTime;

		float getScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);
		unsigned int getPositionIndex(float animationTime);
		unsigned int getRotationIndex(float animationTime);
		unsigned int getScaleIndex(float animationTime);
		glm::mat4 InterpolatePosition(float animationTime);
		glm::mat4 InterpolateRotation(float animationTime);
		glm::mat4 InterpolateScale(float animationTime);
};

#endif
