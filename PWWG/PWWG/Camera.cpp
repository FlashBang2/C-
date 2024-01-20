#include "Camera.h"

Camera::Camera(glm::vec3 Position)
{
	position = Position;
}

void Camera::Update()
{
	view = glm::lookAt(position, position + front, up);
}

void Camera::HandleMouseMovment(float xOffset, float yOffset)
{
	xOffset *= sensivity;
	yOffset *= sensivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;
}

void Camera::Recalculate()
{
	glm::vec3 Front;
	Front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	Front.y = sin(glm::radians(pitch));
	Front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	front = glm::normalize(Front);
	up = glm::normalize(glm::cross(glm::cross(front, worldUp), front));
}

void Camera::HandleEvents(GLFWwindow* window, float deltaTime)
{
	float movment = speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += movment * front;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
	{
		position -= movment * front;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += glm::normalize(glm::cross(front, up)) * movment;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
	{
		position -= glm::normalize(glm::cross(front, up)) * movment;
	}
}
