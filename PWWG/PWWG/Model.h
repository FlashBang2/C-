#ifndef MODEL_H
#define MODEL_H

#include<iostream>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include<stb/stb_image.h>

#include"Mesh.h"

class Model
{
	public:
		std::vector<Mesh> meshes;

		Model() {};
		Model(std::string path);

		void Draw(Shader& shader);
	private:
		std::string diretory;
		std::vector<Texture> textures;

		void traverseNodes(aiNode* node, const aiScene* scene);
		void processMesh(aiMesh* mesh, const aiScene* scene);
		void setupTextures(aiTextureType type, aiMaterial* material);
};

#endif

