#include "Button.h"

Button::Button(glm::vec3 Position)
{
	state = UNHOVER;
	position = Position;
	color = glm::vec3(0.5f, 0.5f, 0.5f);
	buttonModel = Model("Models/Button/button.obj");

	maxX = buttonModel.meshes[0].GetMaxPositionX();
	minX = buttonModel.meshes[0].GetMinPositionX();
	maxY = buttonModel.meshes[0].GetMaxPositionY();
	minY = buttonModel.meshes[0].GetMinPositionY();
}

void Button::UpdateState(glm::vec2 normalizeMousePosition)
{
	if (normalizeMousePosition.x >= minX + position.x && normalizeMousePosition.x <= maxX + position.x &&
		-normalizeMousePosition.y >= minY + position.y && -normalizeMousePosition.y <= maxY + position.y)
	{
		state = HOVER;
		return;
	}
	state = UNHOVER;
}

void Button::Render(Shader shader)
{
	glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

	shader.SetMat4("model", model);

	switch (state) 
	{
		case HOVER:
			shader.SetVec3("color", 0.7f, 0.7f, 0.7f);
			break;
		case UNHOVER:
			shader.SetVec3("color", 0.5f, 0.5f, 0.5f);
			break;
	}

	buttonModel.Draw(shader, false);
}