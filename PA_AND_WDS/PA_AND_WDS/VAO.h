#ifndef VAO_CLASS_h
#define	VAO_CLASS_h

#include <glad/glad.h>

#include "VBO.h"

class VAO
{
	public:
		GLuint ID;
		VAO();

		void LinkVBO(VBO VBO, GLuint layout);
		void Bind();
		void Unbind();
		void Delete();
};

#endif

