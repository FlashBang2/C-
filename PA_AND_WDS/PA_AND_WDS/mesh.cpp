#include "Mesh.h"

std::vector<struct Vertex> Vertex::genList(float* vertices, int noVertices) {
	std::vector<Vertex> RET(noVertices);

	int stride = sizeof(Vertex) / sizeof(float);

	for (int i = 0; i < noVertices;i++) {
		RET[i].position = glm::vec3(
			vertices[i * stride + 0],
			vertices[i * stride + 1],
			vertices[i * stride + 2]
		);

		RET[i].normal = glm::vec3(
			vertices[i * stride + 3],
			vertices[i * stride + 4],
			vertices[i * stride + 5]
		);

		RET[i].texCoord = glm::vec2(
				vertices[i * stride + 6],
				vertices[i * stride + 7]
		);
	}

	return RET;
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
	:vertices(vertices), indcies(indices), textures(textures) 
{
	setup();
}

void Mesh::Render(Shader shaderProgram) {
	unsigned int diffuseIndex = 0, specularIndex = 0;

	shaderProgram.activate();
	glBindVertexArray(VAO);

	for (unsigned int i = 0; i < textures.size();i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		std::string name;
		switch (textures[i].type) {
		case aiTextureType_DIFFUSE:
			name = "diffuse" + std::to_string(diffuseIndex++);
			break;
		case aiTextureType_SPECULAR:
			name = "specular" + std::to_string(specularIndex++);
			break;
		}
		shaderProgram.setInt(name, i);
		textures[i].bind();
	}

	glDrawElements(GL_TRIANGLES, indcies.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

}

void Mesh::Cleanup() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EABO);
}

void Mesh::setup() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EABO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EABO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indcies.size() * sizeof(unsigned int), &indcies[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoord));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Bitangent));

	glEnableVertexAttribArray(5);
	glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*) offsetof(Vertex, BoneIds));

	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Weights));

	glBindVertexArray(0);

}
