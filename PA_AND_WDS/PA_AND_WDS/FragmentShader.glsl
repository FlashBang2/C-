#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

void main() {
	FragColor = texture2D(diffuse0, texCoord);
}