#ifndef MENU_H
#define MENU_H

#include<map>

#include"GenericScene.h"

class Menu:public GenericScene
{
	public:
		Menu();

		void Render(GLFWwindow* window, float deltaTime);
	private:
		struct Character 
		{
			unsigned int textureID;
			glm::ivec2 size;
			glm::ivec2 offsetFromTopLeft;
			GLuint horizontalOffset;
		};

		std::map<GLchar, Character> characters;
		GLuint VAO, VBO;
		float cursorOffsetY;

		void RenderText(Shader& shader, std::string value, glm::vec2 position, float scale, glm::vec3 color);
};

#endif