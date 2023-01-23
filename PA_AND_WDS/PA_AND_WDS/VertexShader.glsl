#version 330 core
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;

out vec3 currentPosition;
out vec2 texCoord;
out vec3 normal;

uniform mat4 camMatrix;
uniform mat4 model;

void main() {
	currentPosition = vec3(model * vec4(Position, 1.0));
	normal = Normal;
	texCoord = TexCoord;
	gl_Position = camMatrix * vec4(currentPosition, 1.0);
}