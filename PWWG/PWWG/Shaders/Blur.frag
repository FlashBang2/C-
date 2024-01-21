#version 460 core

out vec4 FragColor;

in vec2 textureCoordinates;

uniform sampler2D image;

uniform bool horizontal;
uniform float weigths[5] = float[] (0.2270270270f, 0.1945945946f, 0.1216216216f, 0.0540540541f, 0.0162162162f);

void main () 
{
	vec2 texelSize = 1.0f / textureSize(image, 0);
	vec3 result = texture(image, textureCoordinates).rgb * weigths[0];
	if (horizontal) 
	{
		for (int i = 1; i < 5; ++i) 
		{
			result += texture(image, textureCoordinates + vec2(texelSize.x * i, 0.0f)).rgb * weigths[i];
			result += texture(image, textureCoordinates - vec2(texelSize.x * i, 0.0f)).rgb * weigths[i];
		}
	}
	else 
	{
		for (int i = 1; i < 5; ++i) 
		{
			result += texture(image, textureCoordinates + vec2(0.0f, texelSize.y * i)).rgb * weigths[i];
			result += texture(image, textureCoordinates - vec2(0.0f, texelSize.y * i)).rgb * weigths[i];
		}
	}
	FragColor = vec4(result, 1.0f);
}