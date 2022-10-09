#ifndef EABO_CLASS_H
#define EABO_CLASS_H

#include <glad/glad.h>

class EABO
{
	public:
		GLuint ID;
		EABO(GLuint* indices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();
};

#endif

