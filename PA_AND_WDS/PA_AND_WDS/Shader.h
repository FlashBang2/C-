#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	unsigned int ID;

	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void activate();
	void setMat4(const std::string& name, glm::mat4 value);
	void setFloat(const std::string& name, float value);
	void setInt(const std::string& name, int value);
	std::string loadShaderSrc(const char* filepath);
	GLuint compileShader(const char* filepath, GLenum type);
	
protected:

private:

};

#endif