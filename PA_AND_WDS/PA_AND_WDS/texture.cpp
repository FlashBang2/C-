#include "Texture.h"

Texture::Texture(std::string directory, std::string path, aiTextureType type)
	: directory(directory), path(path), type(type) {
	generate();
}

void Texture::generate() {
	glGenTextures(1, &ID);
}

void Texture::load(bool flip) {
	stbi_set_flip_vertically_on_load(flip);

	int width, height, nChannels;

	unsigned char* data = stbi_load((directory + "/" + path).c_str(), &width, &height, &nChannels, 0);

	GLenum colorMode = GL_RGB;
	switch (nChannels) {
	case 1:
		colorMode = GL_RED;
		break;
	case 4:
		colorMode = GL_RGBA;
		break;
		
	}

	if (data) {
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else {
		printf("Error during image loading:\n%s", (directory + "/" + path).c_str());
	}

	stbi_image_free(data);
}

void Texture::load(unsigned int bufferSize, void* textureData) {
	generate();
	int width, height, nChannels;

	unsigned char* data = stbi_load_from_memory((const stbi_uc*) textureData, bufferSize,&width, &height, &nChannels, 0);

	GLenum colorMode = GL_RGB;
	switch (nChannels) {
		case 1:
			colorMode = GL_RED;
			break;
		case 4:
			colorMode = GL_RGBA;
			break;
	}

	if (data) {
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else {
		printf("Error during image loading:\n%s", (directory + "/" + path).c_str());
	}

	stbi_image_free(data);

}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, ID);
}