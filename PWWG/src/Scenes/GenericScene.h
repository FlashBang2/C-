#ifndef GENERIC_SCENE_H
#define GENERIC_SCENE_H

#include"../Button.h"
#include"../Camera.h"
#include"../Animator.h"

struct Flashlight 
{
	glm::vec3 ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 diffuse = glm::vec3(10.0f, 10.0f, 10.0f);
	glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);
	float constant = 1.0f;
	float linear = 0.0014f;
	float quadratic = 0.000007f;
};

struct PointLight 
{
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float constant = 1.0f;
	float linear;
	float quadratic;
};

struct Object
{
	glm::mat4 model;

	float strengthOfRotation;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

class GenericScene
{
	public:
		std::vector<Camera> cameras;
		std::vector<Button> buttons;
		std::vector<PointLight> pointLights;
		Flashlight flashlightObject;
		bool flashlight, gammaCorrection, hdr, bloom;
		int width = 1920, height = 1080;
		double mouseX, mouseY;

		GenericScene() {};
		
		virtual void Render(GLFWwindow* window, float deltaTime) {};
	protected:
		std::vector<Animator> animators;
		std::vector<Shader> shaders;
		std::vector<Model> models;
		glm::mat4 projection;
		GLuint pingpongFBO[2], pingpongColorBuffers[2];
		GLuint HDR, colorBuffers[2], VAO = 0;

		void SetupPostProcessing()
		{
			glGenFramebuffers(1, &HDR);
			glBindFramebuffer(GL_FRAMEBUFFER, HDR);

			glGenTextures(2, colorBuffers);

			for (int i = 0; i < std::end(colorBuffers) - std::begin(colorBuffers); i++)
			{
				glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
			}

			GLuint renderDepthObject;
			glGenRenderbuffers(1, &renderDepthObject);
			glBindRenderbuffer(GL_RENDERBUFFER, renderDepthObject);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderDepthObject);

			GLuint attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };

			glDrawBuffers(2, attachments);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				std::cout << "ERROR::FRAMEBUFFER: Main framebuffer not completed!" << std::endl;
				abort();
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			glGenFramebuffers(2, pingpongFBO);
			glGenTextures(2, pingpongColorBuffers);

			for (int i = 0; i < std::end(pingpongFBO) - std::begin(pingpongFBO); i++)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
				glBindTexture(GL_TEXTURE_2D, pingpongColorBuffers[i]);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorBuffers[i], 0);
				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				{
					std::cout << "ERROR::FRAMEBUFFER: Pingpong framebuffer not completed!" << std::endl;;
				}
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		};

		void RenderQuadFullScreen()
		{
			if (VAO == 0)
			{
				float vertices[] =
				{
					-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
					-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
					 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
					 1.0f, -1.0f, 0.0f, 1.0f, 0.0f
				};

				GLuint VBO;

				glGenVertexArrays(1, &VAO);
				glBindVertexArray(VAO);

				glGenBuffers(1, &VBO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);

				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);

				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
				glEnableVertexAttribArray(1);

				glBindVertexArray(0);
			}
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glBindVertexArray(0);
		};
	private:
};

#endif

