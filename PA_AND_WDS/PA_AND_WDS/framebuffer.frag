#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;
uniform float gamma;
uniform float exposure;

void main() {
    vec3 fragment = texture(screenTexture, texCoords).rgb;

    vec3 toneMapped = vec3(1.0) - exp(-fragment * exposure);
    toneMapped = pow(toneMapped, vec3(1.0 / gamma));

    FragColor = vec4(toneMapped, 1.0);
}