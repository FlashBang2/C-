#include"Model.h"

Model::Model(glm::vec3 position, glm::vec3 size, glm::vec3 rotation, float radians)
	: position(position), size(size), rotation(rotation), radians(radians) {}

void Model::loadModel(std::string path) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		printf("Could not load model:\n%s\n Error message:\n%s", path.c_str(), importer.GetErrorString());
		return;
	}

	directory = path.substr(0, path.find_last_of("/"));
	processNode(scene->mRootNode, scene);
}

void Model::Render(Shader shaderProgram) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(0.0f), rotation);
	model = glm::scale(model, size);
	shaderProgram.setMat4("model", model);

	for (Mesh mesh : meshes) {
		mesh.Render(shaderProgram);
	}
}

void Model::Cleanup() {
	for (Mesh mesh : meshes) {
		mesh.Cleanup();
	}
}

void Model::processNode(aiNode* node, const aiScene* scene) {
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;

		vertex.position = glm::vec3(
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		);

		vertex.normal = glm::vec3(
			mesh->mNormals[i].x,
			mesh->mNormals[i].y,
			mesh->mNormals[i].z
		);

		if (mesh->mTextureCoords[0]) {
			vertex.texCoord = glm::vec2(
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y
			);
		}
		else {
			vertex.texCoord = glm::vec2(0.0f);
		}

		vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces;i++) {
		aiFace face = mesh->mFaces[i];
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuseMaps = loadTextures(material, aiTextureType_DIFFUSE);
		std::vector<Texture> specularMaps = loadTextures(material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadTextures(aiMaterial* material, aiTextureType type) {
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < material->GetTextureCount(type);i++) {
		aiString path;
		material->GetTexture(type,i, &path);
		printf("Loaded texture from:\n%s", path.C_Str());

		bool skip = false;

		for (unsigned int j = 0; j < texturesLoaded.size();j++) {
			if (std::strcmp(texturesLoaded[j].path.data(), path.C_Str()) == 0) {
				textures.push_back(texturesLoaded[j]);
				skip = true;
				break;
			}
		}

		if (!skip) {
			Texture texture(directory, path.C_Str(), type);
			texture.load(false);
			textures.push_back(texture);
			texturesLoaded.push_back(texture);
		}
	}

	return textures;
}