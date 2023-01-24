#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"

#define MAX_BONE_INFLUENCE 4

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
	int BoneIds[MAX_BONE_INFLUENCE];
	float Weights[MAX_BONE_INFLUENCE];

	static std::vector<struct Vertex> genList(float* vertices, int noVertices);
};
typedef struct Vertex Vertex;

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indcies;
	unsigned int VAO;
	std::vector<Texture> textures;

	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures = {});
	void Render(Shader shaderProgram);
	void Cleanup();
protected:
private:
	unsigned int VBO, EABO;
	void setup();
};
#endif