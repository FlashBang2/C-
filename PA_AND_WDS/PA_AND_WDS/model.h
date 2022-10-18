#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <json/json.h>

#include "mesh.h"

using json = nlohmann::json;

#pragma once
class model
{
public:
	model(const char* file);

	void Draw(shader& shader, camera& camera);

private:
	const char* file;
	std::vector<unsigned char> data;
	json JSON;

	std::vector<mesh> meshes;
	std::vector<glm::vec3> translationsMeshes;
	std::vector<glm::quat> rotationsMeshes;
	std::vector<glm::vec3> scalesMeshes;
	std::vector<glm::mat4> matricesMeshses;

	std::vector<std::string> loadedTexName;
	std::vector<texture> loadedTex;

	void loadMesh(unsigned int indMesh);

	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	std::vector<unsigned char> getData();
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);
	std::vector<texture> getTextures();

	std::vector<vertex> assembleVertices
	(
		std::vector<glm::vec3> positions,
		std::vector<glm::vec3> normal,
		std::vector<glm::vec2> texUvs
	);

	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
};

#endif