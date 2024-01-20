#include"Model.h"

Model::Model(std::string path)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
	{
		std::cout << "Error Assimp: " << importer.GetErrorString() << std::endl;
		return;
	}

	diretory = path.substr(0, path.find_last_of('/'));

	traverseNodes(scene->mRootNode, scene);
}

void Model::Draw(Shader& shader)
{
	for (int i = 0; i < meshes.size(); i++) 
	{
		meshes[i].Draw(shader);
	}
}

void Model::traverseNodes(aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; i++) 
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		processMesh(mesh, scene);
	}

	for (int i = 0; i < node->mNumChildren; i++) 
	{
		traverseNodes(node->mChildren[i], scene);
	}
}

void Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;

	for (int i = 0; i < mesh->mNumVertices; i++) 
	{
		Vertex vertex;
	
		position.x = mesh->mVertices[i].x;
		position.y = mesh->mVertices[i].y;
		position.z = mesh->mVertices[i].z;
		
		if (mesh->HasVertexColors(i)) 
		{
			color.x = mesh->mColors[i]->r;
			color.y = mesh->mColors[i]->g;
			color.z = mesh->mColors[i]->b;
			vertex.color = color;
		}

		if (mesh->HasNormals()) 
		{
			normal.x = mesh->mNormals[i].x;
			normal.y = mesh->mNormals[i].y;
			normal.z = mesh->mNormals[i].z;
			vertex.normal = normal;
		}

		if (mesh->HasTextureCoords(0)) 
		{
			textureCoordinates.x = mesh->mTextureCoords[0][i].x;
			textureCoordinates.y = mesh->mTextureCoords[0][i].y;
			vertex.textureCoordinates = textureCoordinates;
		}

		vertex.position = position;

		vertices.push_back(vertex);
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	setupTextures(aiTextureType_DIFFUSE, material);
	setupTextures(aiTextureType_SPECULAR, material);

	meshes.push_back(Mesh(vertices, textures));
}

void Model::setupTextures(aiTextureType type, aiMaterial* material)
{
	for (int i = 0; i < material->GetTextureCount(type); i++)
	{
		Texture texture;
		GLuint id;

		aiString path;
		material->GetTexture(type, i, &path);

		int width, height, numberOfChannels;

		unsigned char* imageData = stbi_load((diretory + "/" + path.C_Str()).c_str(), &width, &height, &numberOfChannels, 0);

		GLenum format;
		switch (numberOfChannels)
		{
		case 1:
			format = GL_RED;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		}

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		texture.ID = id;
		texture.type = std::string(path.C_Str()).find_last_of('.');

		textures.push_back(texture);

		stbi_image_free(imageData);
	}
}
