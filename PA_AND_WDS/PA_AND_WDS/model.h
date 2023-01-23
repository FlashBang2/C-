#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <vector>

#include "Mesh.h"
#include "Texture.h"

class Model {
public:
	glm::vec3 position;
	glm::vec3 size;
	glm::vec3 rotation;
	float radians;

	Model(glm::vec3 position = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(1.0f), float radians = 0.0f);
	void loadModel(std::string path);
	void Render(Shader shaderProgram);
	void Cleanup();
protected:
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> texturesLoaded;
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadTextures(aiMaterial* mat, aiTextureType type);
private:
};
#endif