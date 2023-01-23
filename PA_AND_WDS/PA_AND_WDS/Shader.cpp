#include "Shader.h"
#include "Shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	int success;
	char errorLog[512];

	GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, errorLog);
		printf("Error while linking shaderProgram:\n%s", errorLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::activate() {
	glUseProgram(ID);

}

void Shader::setMat4(const std::string& name, glm::mat4 value) {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, glm::vec3 value) {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void Shader::setVec4(const std::string& name, glm::vec4 value) {
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::setFloat(const std::string& name, float value) {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

std::string Shader::loadShaderSrc(const char* filename) {
	std::ifstream file;
	std::stringstream buffer;
	std::string RET = "";

	file.open(filename);

	if (file.is_open()) {
		buffer << file.rdbuf();
		RET = buffer.str();
	}
	else {
		printf("Didn't found specified shader file: %s \n", filename);
	}

	file.close();

	return RET;
}

GLuint Shader::compileShader(const char* filepath, GLenum type) {
	int success;
	char errorLog[512];

	GLuint RET = glCreateShader(type);
	std::string shaderSrc = loadShaderSrc(filepath);
	const GLchar* shader = shaderSrc.c_str();
	glShaderSource(RET, 1, &shader, NULL);
	glCompileShader(RET);

	glGetShaderiv(RET, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(RET, 512, NULL, errorLog);
		printf("Error while compiling shader:\n%s", errorLog);
	}

	return RET;
}
