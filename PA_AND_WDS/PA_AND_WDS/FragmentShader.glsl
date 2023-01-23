#version 330 core

out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 currentPosition;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec3 cameraPosition;

vec4 directLight() {
	float ambient = 0.20, specularLight = 0.50;

	vec3 Normal = normalize(normal);
	vec3 lightDirection = normalize(vec3(1.0, 1.0, 0.0));
	float diffuse = max(dot(Normal, lightDirection), 0.0);
	vec3 viewDirection = normalize(cameraPosition - currentPosition);
	vec3 reflectionDirection = reflect(-lightDirection, Normal);
	float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 16);
	float specular = specularAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

void main() {
	FragColor = directLight();
}