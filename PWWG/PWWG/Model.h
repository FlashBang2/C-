#ifndef MODEL_H
#define MODEL_H

#include<iostream>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include<stb/stb_image.h>
#include<map>

#include"Mesh.h"

struct BoneInfo
{
	int ID;
	glm::mat4 offset;
};

class Model
{
	public:
		std::map<std::string, BoneInfo> bonesInfo;
		std::vector<Mesh> meshes;
		GLuint currentBone = 0;

		Model() {};
		Model(std::string path);

		void Draw(Shader& shader);
	private:
		std::string diretory;
		std::vector<Texture> textures;

		void traverseNodes(aiNode* node, const aiScene* scene);
		void processMesh(aiMesh* mesh, const aiScene* scene);
		void setupTextures(aiTextureType type, aiMaterial* material, const aiScene* scene);
		void SetVertexBoneWeightToDefault(Vertex& vertex);
		void ExtractBoneWeights(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);
};

#endif

