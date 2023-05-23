#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BloomColor;

in vec3 crntPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec4 lightColor;
uniform vec3 camPos;
uniform float lightAngle1;
uniform float lightAngle2;

vec4 direcLight() {
	float ambient = 2.0f;

	return (texture(diffuse0, texCoord) * (ambient) + texture(specular0, texCoord).r) * lightColor;
}

void main() {
	FragColor = direcLight();

	//Konfiguracja czu³oœci bloom i streak
	float brightness = dot(FragColor.rgb, vec3(0.2126f, 0.7152f, 0.0722f));
    if(brightness > 0.75f)
        BloomColor = vec4(FragColor.rgb, 1.0f);
    else
        BloomColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}