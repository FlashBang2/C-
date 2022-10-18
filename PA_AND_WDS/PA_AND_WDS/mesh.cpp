#include "mesh.h"

mesh::mesh(std::vector<vertex>& verticles, std::vector<GLuint>& indices, std::vector<texture>& textures)
{
	mesh::vertices = vertices;
	mesh::indices = indices;
	mesh::textures = textures;

	VAO.Bind();

	VBO VBO(vertices);
	EABO EABO(indices);

	VAO.LinkAttribute(VBO, 0, 3, GL_FLOAT, 11 * sizeof(vertex), (void*)0);
	VAO.LinkAttribute(VBO, 1, 3, GL_FLOAT, 11 * sizeof(vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttribute(VBO, 2, 3, GL_FLOAT, 11 * sizeof(vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttribute(VBO, 3, 2, GL_FLOAT, 11 * sizeof(vertex), (void*)(9 * sizeof(float)));

	VAO.Unbind();
	VBO.UnBind();
	EABO.Unbind();
}

void mesh::Draw
(
	shader& shader,
	camera& camera,
	glm::mat4 matrix,
	glm::vec3 translation,
	glm::quat rotation,
	glm::vec3 scale
)
{
	shader.Activate();
	VAO.Bind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size();i++)
	{
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse")
			num = std::to_string(numDiffuse++);
		else if (type == "specular")
			num = std::to_string(numSpecular++);
		textures[i].texUnit(shader, (type + num).c_str(),i);
		textures[i].Bind();
	}
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.z, camera.Position.y, camera.Position.x);
	camera.Matrix(shader, "camMatrix");

	glm::mat4 transform = glm::mat4(1.0f);
	glm::mat4 rotate = glm::mat4(1.0f);
	glm::mat4 Scale = glm::mat4(1.0f);

	transform = glm::translate(transform, translation);
	rotate = glm::mat4_cast(rotation);
	Scale = glm::scale(Scale, scale);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(transform));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rotate));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(Scale));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
