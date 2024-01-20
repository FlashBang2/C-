#ifndef  SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<glm/glm.hpp>
#include<fstream>
#include<iostream>

class Shader
{
	public:
		GLuint ID;

		Shader(const char* vertexFile, const char* fragmentFile);

		void Activate();
		void Delete();
		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);
		void SetVec3(const std::string& name, glm::vec3& value);
		void SetVec3(const std::string& name, float v1, float v2, float v3);
		void SetVec2(const std::string& name, glm::vec2& value);
		void SetVec2(const std::string& name, float v1, float v2);
		void SetMat4(const std::string& name, glm::mat4& value);
	private:
		std::string getFileContents(const char* filename);
		void compileErrors(unsigned int shader, const char* type);
};	

#endif