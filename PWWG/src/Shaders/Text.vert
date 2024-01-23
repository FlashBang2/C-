#version 460 core

layout (location = 0) in vec4 vertex;

out vec2 TextureCoordinates;

uniform mat4 projection;

void main () 
{
	gl_Position = projection * vec4(vertex.xy, 0.1f, 1.0f);
	TextureCoordinates = vertex.zw;
}