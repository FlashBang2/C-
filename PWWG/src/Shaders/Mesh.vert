#version 460 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 textureCoordinates;

out vec3 FragmentPosition;
out vec3 Normal;
out vec2 TextureCoordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	FragmentPosition = vec3(model * vec4(position, 1.0f));

	Normal = mat3(transpose(inverse(model))) * normal;
	TextureCoordinates = textureCoordinates;

	gl_Position = projection * view * vec4(FragmentPosition, 1.0f);
}