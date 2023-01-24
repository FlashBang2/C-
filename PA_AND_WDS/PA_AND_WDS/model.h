#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <vector>
#include <map>

#include "Mesh.h"
#include "Texture.h"

struct BoneInfo {
	int ID;
	glm::mat4 offset;
};

class Model {
public:
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 position;
	glm::vec3 size;
	glm::vec3 rotation;
	float radians;

	Model(glm::vec3 position = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(1.0f), float radians = 0.0f);
	void Render(Shader shaderProgram);
	void Cleanup();
	void loadModel(std::string path);
	auto& GetBoneInfoMap() { return BoneInfoMap; }
	int& GetBoneCount() { return BoneCounter; }
protected:
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> texturesLoaded;

	std::vector<Texture> loadTextures(aiMaterial* mat, aiTextureType type);
private:
	std::map<std::string, BoneInfo> BoneInfoMap;
	int BoneCounter = 0;

	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	void processNode(aiNode* node, const aiScene* scene);
	void SetVertexBoneDataToDefault(Vertex& vertex);
	void SetVertexBoneData(Vertex& vertex, int boneID, float weight);
	void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);
};
#endif