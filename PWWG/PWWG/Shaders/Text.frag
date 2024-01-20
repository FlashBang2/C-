#version 460 core

in vec2 TextureCoordinates;

out vec4 FragColor;

uniform sampler2D tex;
uniform vec3 textColor;

void main() 
{
	vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(tex, TextureCoordinates).r);
	FragColor = vec4(textColor, 1.0f) * sampled;
}