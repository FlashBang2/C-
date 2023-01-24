#version 330 core
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;
layout (location = 3) in ivec4 boneIds;
layout (location = 4) in vec4 weights;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;

out vec3 localNormal;
out vec2 texCoord;
out vec3 normal;

uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 finalBonesMatrices[MAX_BONES];

void main() {

	vec4 totalPosition = vec4(0.0f);
	for (int i = 0; i < MAX_BONE_INFLUENCE; i++) {
		if (boneIds[i] == -1) continue;
		if (boneIds[i] >= MAX_BONES) {
			totalPosition = vec4(Position, 1.0);
			break;
		}
		vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(Position, 1.0);
		totalPosition += localPosition * weights[i];
		localNormal = mat3(finalBonesMatrices[boneIds[i]]) * Normal;
	}

	texCoord = TexCoord;
	gl_Position = camMatrix * vec4(localNormal, 1.0);
}