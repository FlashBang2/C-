#ifndef BONE_H
#define BONE_H

#include<assimp/scene.h>
#include<string>
#include<vector>
#include<glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

struct KeyPosition 
{
	glm::vec3 position;
	float timeStamp;
};

struct KeyRotation 
{
	glm::quat orientation;
	float timeStamp;
};

struct KeyScale 
{
	glm::vec3 scale;
	float timeStamp;
};

class Bone
{
public:
	glm::mat4 localTransformation;
	std::string name;
	unsigned int ID;

	Bone(std::string name, int ID, const aiNodeAnim* channel);
	void Update(float animationTime);
private:
	std::vector<KeyPosition> positions;
	std::vector<KeyRotation> rotations;
	std::vector<KeyScale> scales;
	unsigned int numberOfPositions, numberOfRotations, numberOfScales;

	float getScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);
	unsigned int getPositionIndex(float animationTime);
	unsigned int getRotationIndex(float animationTime);
	unsigned int getScaleIndex(float animationTime);
	glm::mat4 InterpolatePosition(float animationTime);
	glm::mat4 InterpolateRotation(float animationTime);
	glm::mat4 InterpolateScale(float animationTime);
};

#endif