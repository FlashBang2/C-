#version 460 core

struct Material 
{
	sampler2D diffuse;
};

out vec4 FragColor;

in vec2 textureCordinates;

uniform Material material;

void main() 
{
	FragColor = texture(material.diffuse, textureCordinates);
}