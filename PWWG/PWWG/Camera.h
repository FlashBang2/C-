#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

class Camera
{
	public:
		glm::mat4 view = glm::mat4(1.0f);
		glm::vec3 position;
		glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
		
		Camera(glm::vec3 Position);

		void Update();
		void Recalculate();
		void HandleMouseMovment(float xOffset, float yOffset);
		void HandleEvents(GLFWwindow* window, float deltaTime);

	private:
		float speed = 10.0f;
		float sensivity = 0.1f;
		float yaw = -90.0f;
		float pitch = 0.0f;

		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
};

#endif

