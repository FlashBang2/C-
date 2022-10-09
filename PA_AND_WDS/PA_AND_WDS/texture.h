#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "shader.h"

class texture
{
	public:
		GLuint ID;
		GLenum type;
		texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

		void texUnit(shader shader, const char* uniform, GLuint unit);
		void Bind();
		void Unbind();
		void Delete();
};

#endif