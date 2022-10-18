#ifndef MESH_CLASS_H
#define	MESH_CLASS_H

#include <string>

#include "VAO.h"
#include "EABO.h"
#include "camera.h"
#include "texture.h"

class mesh
{
public:
	std::vector <vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <texture> textures;

	VAO VAO;

	mesh(std::vector <vertex>& verticles, std::vector <GLuint>& indices, std::vector <texture>& textures);

	void Draw
	(
		shader& shader,
		camera& camera,
		glm::mat4 matrix = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);

};

#endif

