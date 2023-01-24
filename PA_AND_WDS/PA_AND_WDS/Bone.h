#ifndef  BONE_CLASS_H
#define  BONE_CLASS_H

#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <glm/gtx/quaternion.hpp>
#include <vector>

struct KeyPosition {
	glm::vec3 position;
	float timeStamp;
};

struct KeyRotation {
	glm::quat orientation;
	float timeStamp;
};

struct KeyScale {
	glm::vec3 scale;
	float timeStamp;
};

class Bone {
public:
	Bone(const std::string& name, int ID, const aiNodeAnim* channel);
	void Update(float animationTime);
	int GetPositionIndex(float animationTime);
	int GetRotationIndex(float animationTime);
	int GetScaleIndex(float animationTime);
	glm::mat4 GetLocalTransform() { return LocalSpace; }
	std::string GetBoneName() const { return name; }
	int GetBoneID() { return ID; }
protected:
private:
	std::vector<KeyPosition> Positions;
	std::vector<KeyRotation> Rotations;
	std::vector<KeyScale> Scales;
	glm::mat4 LocalSpace = glm::mat4(1.0f);
	std::string name;
	int ID;

	float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);
	glm::mat4 InterpolatePosition(float animationTime);
	glm::mat4 InterpolateRotation(float animationTime);
	glm::mat4 InterpolateScale(float animationTime);
};
#endif
