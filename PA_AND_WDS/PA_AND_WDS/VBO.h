#ifndef VBO_CLASS_H 
#define VBO_CLASS_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

struct vertex {

	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VBO
{
	public:
		GLuint ID;
		VBO(std::vector<vertex>& vertices);

		void Bind();
		void UnBind();
		void Delete();
};

#endif