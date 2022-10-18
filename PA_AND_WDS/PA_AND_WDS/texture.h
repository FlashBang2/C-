#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "shader.h"

class texture
{
	public:
		GLuint ID;
		const char* type;
		GLuint unit;
		texture(const char* image, const char* texType, GLuint slot);

		void texUnit(shader& shader, const char* uniform, GLuint unit);
		void Bind();
		void Unbind();
		void Delete();
};

#endif