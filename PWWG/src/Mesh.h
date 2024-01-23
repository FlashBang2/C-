#ifndef MESH_H
#define MESH_H

#include<glm/glm.hpp>
#include<string>
#include<vector>

#include"Shader.h"

#define MAX_BONE_INFLUENCE 4

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
	int boneIds[MAX_BONE_INFLUENCE];
	float weights[MAX_BONE_INFLUENCE];
};

struct Texture {
	GLuint ID;
	std::string type;
};

class Mesh
{
	public:
		Mesh(std::vector<Vertex> Vertices, std::vector<GLuint> Indices, std::vector<Texture> Textures, std::vector<Texture> GammaCorrectedTextures);

		void Draw(Shader& shader, bool gammaCorrected);
		float CalculateCursorOffsetY();
		float GetMaxPositionX();
		float GetMinPositionX();
		float GetMaxPositionY();
		float GetMinPositionY();
	private:
		std::vector<Vertex> vertices;
		std::vector<Texture> textures;
		std::vector<Texture> gammaCorrectedTextures;
		std::vector<GLuint> indices;
		GLuint VAO;
};

#endif

