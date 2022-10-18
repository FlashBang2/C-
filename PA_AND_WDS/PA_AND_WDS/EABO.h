#ifndef EABO_CLASS_H
#define EABO_CLASS_H

#include <glad/glad.h>
#include <vector>

class EABO
{
	public:
		GLuint ID;
		EABO(std::vector<GLuint>& indices);

		void Bind();
		void Unbind();
		void Delete();
};

#endif

