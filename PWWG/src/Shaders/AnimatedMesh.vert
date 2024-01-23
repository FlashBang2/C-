#version 460 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 TextureCordinates;
layout (location = 4) in ivec4 boneIds;
layout (location = 5) in vec4 weights;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;

uniform mat4 mvp;
uniform mat4 finalBonesMatrices[MAX_BONES];

out vec2 textureCordinates;

void main() 
{
	vec4 totalPosition = vec4(0.0f);
	for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
	{
		if (boneIds[i] == -1)
			continue;
		if (boneIds[i] >= MAX_BONES)
		{
			totalPosition = vec4(position, 1.0f);
			break;
		}
		vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(position, 1.0f);
		totalPosition += localPosition * weights[i];
		vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * normal;
	}
	gl_Position = mvp * totalPosition;
	textureCordinates = TextureCordinates;
}