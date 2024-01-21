#include"Model.h"

Model::Model(std::string path)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_FlipUVs | aiProcess_Triangulate);

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

void Model::SetVertexBoneWeightToDefault(Vertex& vertex)
{
	for (int i = 0; i < MAX_BONE_INFLUENCE; i++) 
	{
		vertex.boneIds[i] = -1;
		vertex.weights[i] = 0.0f;
	}
}

void Model::ExtractBoneWeights(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene)
{
	for (int i = 0; i < mesh->mNumBones; i++) 
	{
		int boneID = -1;
		std::string boneName = mesh->mBones[i]->mName.C_Str();
		if (bonesInfo.find(boneName) == bonesInfo.end())
		{
			BoneInfo boneInfo;
			boneInfo.ID = currentBone;
			boneInfo.offset = glm::mat4(mesh->mBones[i]->mOffsetMatrix.a1, mesh->mBones[i]->mOffsetMatrix.b1, mesh->mBones[i]->mOffsetMatrix.c1, mesh->mBones[i]->mOffsetMatrix.d1,
				mesh->mBones[i]->mOffsetMatrix.a2, mesh->mBones[i]->mOffsetMatrix.b2, mesh->mBones[i]->mOffsetMatrix.c2, mesh->mBones[i]->mOffsetMatrix.d2,
				mesh->mBones[i]->mOffsetMatrix.a3, mesh->mBones[i]->mOffsetMatrix.b3, mesh->mBones[i]->mOffsetMatrix.c3, mesh->mBones[i]->mOffsetMatrix.d3,
				mesh->mBones[i]->mOffsetMatrix.a4, mesh->mBones[i]->mOffsetMatrix.b4, mesh->mBones[i]->mOffsetMatrix.c4, mesh->mBones[i]->mOffsetMatrix.d4);
			bonesInfo[boneName] = boneInfo;
			boneID = currentBone;
			currentBone++;
		}
		else 
		{
			boneID = bonesInfo[boneName].ID;
		}
		if (boneID == -1) 
		{
			std::cout << "Error::Bone: Extracton of data failed!";
			std::abort();
		}
		aiVertexWeight* weights = mesh->mBones[i]->mWeights;
		GLuint numberOfWeights = mesh->mBones[i]->mNumWeights;

		for (int j = 0; j < numberOfWeights; j++) 
		{
			unsigned int vertexID = weights[j].mVertexId;
			float weight = weights[j].mWeight;

			for (int k = 0; k < MAX_BONE_INFLUENCE; k++) 
			{
				if (vertices[vertexID].boneIds[k] < 0) 
				{
					vertices[vertexID].boneIds[k] = boneID;
					vertices[vertexID].weights[k] = weight;
					break;
				}
			}
		}
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
	std::vector<GLuint> indicies;
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;

	for (int i = 0; i < mesh->mNumVertices; i++) 
	{
		Vertex vertex;

		SetVertexBoneWeightToDefault(vertex);
	
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

	for (GLuint i = 0; i < mesh->mNumFaces; i++) 
	{
		aiFace face = mesh->mFaces[i];
		indicies.push_back(face.mIndices[0]);
		indicies.push_back(face.mIndices[1]);
		indicies.push_back(face.mIndices[2]);
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	setupTextures(aiTextureType_DIFFUSE, material, scene);
	setupTextures(aiTextureType_SPECULAR, material, scene);

	ExtractBoneWeights(vertices, mesh, scene);

	meshes.push_back(Mesh(vertices, indicies, textures));
}

void Model::setupTextures(aiTextureType type, aiMaterial* material, const aiScene* scene)
{
	for (int i = 0; i < material->GetTextureCount(type); i++)
	{
		Texture texture;
		GLuint id;

		aiString path;
		material->GetTexture(type, i, &path);

		int width, height, numberOfChannels;

		unsigned char* imageData = stbi_load((diretory + "/" + path.C_Str()).c_str(), &width, &height, &numberOfChannels, 0);

		const aiTexture* embendedTexture = scene->GetEmbeddedTexture(path.C_Str());
		if (embendedTexture) 
		{
			imageData = stbi_load_from_memory((const stbi_uc*)embendedTexture->pcData, embendedTexture->mWidth, &width, &height, &numberOfChannels, 0);
		}

		GLenum internalFormat;
		switch (numberOfChannels)
		{
		case 1:
			internalFormat = GL_RED;
			break;
		case 3:
			internalFormat = GL_RGB;
			break;
		case 4:
			internalFormat = GL_RGBA;
			break;
		}

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, imageData);

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
