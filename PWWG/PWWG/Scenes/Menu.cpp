#include "Menu.h"

#include<ft2build.h>
#include FT_FREETYPE_H

Menu::Menu()
{
	Button buttonExample(glm::vec3(0.0f, 0.2f, 0.0f));
	Button buttonAdvanceExample(glm::vec3(0.0f, 0.0f, 0.0f));
	Button buttonQuit(glm::vec3(0.0f, -0.2f, 0.0f));

	buttons.push_back(buttonExample);
	buttons.push_back(buttonAdvanceExample);
	buttons.push_back(buttonQuit);

	Shader cursorShader("Shaders/Cursor.vert", "Shaders/Cursor.frag");
	Shader buttonShader("Shaders/Button.vert", "Shaders/Button.frag");
	Shader textShader("Shaders/Text.vert", "Shaders/Text.frag");

	Model cursorModel("Models/Cursor/cursor.obj");

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		abort();
	}

	FT_Face face;
	if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		abort();
	}
	
	FT_Set_Pixel_Sizes(face, 0, 48);

	textShader.Activate();

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
	textShader.SetMat4("projection", projection);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (unsigned char c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR:FREETYPE: Failed to load Glyph" << std::endl;
			abort();
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		Character ch =
		{
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			static_cast<GLuint>(face->glyph->advance.x)
		};
		characters.insert(std::pair<char, Character>(c, ch));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 0);
	
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	cursorOffsetY = cursorModel.meshes[0].CalculateCursorOffsetY();

	shaders.push_back(cursorShader);
	shaders.push_back(buttonShader);
	shaders.push_back(textShader);

	models.push_back(cursorModel);
}

void Menu::Render(GLFWwindow* window, float deltaTime)
{
	float normalizeMouseX = mouseX / (double)width;
	float normalizeMouseY = mouseY / (double)height;

	glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

	shaders[0].Activate();
	
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(normalizeMouseX, -(-0.01f + cursorOffsetY + normalizeMouseY), -0.2f));

	shaders[0].SetMat4("model", model);

	models[0].Draw(shaders[0], false);

	shaders[1].Activate();

	for (int i = 0; i < std::end(buttons) - std::begin(buttons); i++)
	{
		buttons[i].UpdateState(glm::vec2(normalizeMouseX, normalizeMouseY));
		buttons[i].Render(shaders[1]);
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	RenderText(shaders[2], "Game Engine", glm::vec2(width / 3 + 50, height / 3 + 500.0f), 2.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	RenderText(shaders[2], "Example", glm::vec2(width / 3 + 250.0f, height / 3 + 275.0f), 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
	RenderText(shaders[2], "AdvanceExample", glm::vec2(width / 3 + 250.0f, height / 3 + 175.0f), 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
	RenderText(shaders[2], "Quit", glm::vec2(width / 3 + 250.0f, height / 3 + 75.0f), 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
}

void Menu::RenderText(Shader& shader, std::string value, glm::vec2 position, float scale, glm::vec3 color)
{
	shader.Activate();

	shader.SetVec3("textColor", color);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	float positionX = 0, positionY = 0;
	float PositionX = position.x, PositionY = position.y;

	std::string::const_iterator c;
	for (c = value.begin(); c != value.end(); c++)
	{
		Character ch = characters[*c];

		positionX = position.x + ch.offsetFromTopLeft.x * scale;
		positionY = position.y - (ch.size.y - ch.offsetFromTopLeft.y) * scale;

		float width = ch.size.x * scale;
		float height = ch.size.y * scale;

		float vertices[6][4] =
		{
			{positionX, positionY + height, 0.0f, 0.0f},
			{positionX, positionY, 0.0f, 1.0f},
			{positionX + width, positionY, 1.0f, 1.0f},
			{positionX, positionY + height, 0.0f, 0.0f},
			{positionX + width, positionY, 1.0f, 1.0f},
			{positionX + width, positionY + height, 1.0f, 0.0f}
		};

		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		position.x += (ch.horizontalOffset >> 6) * scale;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


